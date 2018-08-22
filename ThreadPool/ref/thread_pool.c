/*************************************************************************
    > File Name: thread_pool.c
    > Author: zhengli
    > Mail: zldata@aliyun.com 
    > Created Time: 五  4/ 6 13:16:12 2018
    > Brief: 
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "thread_pool.h"


/**
 * @brief	数组中的每个成员在thread_pool_init中初始化，数组成员结构式thread_pool_t
 *			创建空间在thread_pool_create_conf
 * @brief	pools	所有的thread_pool name配置信息thread_pool_t存放在该数组中，见thread_pool_add
 */
typedef struct {
    array_t               pools; 
} thread_pool_conf_t;



/**
 * 线程池队列  初始化在thread_pool_queue_init
 *
 * thread_pool_t->queue.last = task;  新添加的任务通过last连接在一起
 * thread_pool_t->queue.last = &task->next;  下次在添加新任务就让task->next指向新任务了
 */
typedef struct {			//见thread_pool_done
	thread_task_t        *first;
	thread_task_t		 **last;
} thread_pool_queue_t; 


#define thread_pool_queue_init(q)												\
	(q)->first = NULL;															\
	(q)->last = &(q)->first



/**
 * 一个该结构对应一个threads_pool配置
 * 该结构式存放在thread_pool_conf_t->pool数组中的，见thread_pool_init_worker
 *
 * @brief	mtx			线程锁  thread_pool_init中初始化
 * @brief	queue		thread_pool_init  thread_pool_queue_init中初始化
 *						thread_task_post中添加的任务被添加到该队列中
 * @brief	waiting		等待的任务数   thread_task_post加1   thread_pool_cycle减1
 *						在该线程池poll中每添加一个线程，waiting子减，当线程全部正在执行任务后，waiting会恢复到0
 *						如果所有线程都已经在执行任务(也就是waiting>-0)，又来了任务，那么任务就只能等待。
 *						所以waiting表示等待被执行的任务数
 * @brief	cond		条件变量  thread_pool_init中初始化
 * @brief	log			thread_pool_init中初始化
 * @brief	name		thread_pool name threads=number [max_queue=number];中的name  thread_pool
 * @brief	threads		thread_pool name threads=number [max_queue=number];中的number  thread_pool
 *						如果没有配置，在thread_pool_init_conf默认赋值为32
 * @brief	max_queue	thread_pool name threads=number [max_queue=number];中的max_queue  thread_pool
 *						如果没有配置，在thread_pool_init_conf默认赋值为65535  
 *						指的是线程已经全部用完的情况下，还可以添加多少个任务到等待队列
 * @brief	file		配置文件名
 * @brief	line		thread_pool配置在配置文件中的行号
 */
struct thread_pool_s {
	thread_mutex_t			mtx; 
	thread_pool_queue_t		queue;
	int						waiting;
	thread_cond_t			cond;
	log_t					*log;
	str_t					name;
	unsigned int			threads;
	int						max_queue;
	char					*file;
	unsigned int            line;
};


static int thread_pool_init(thread_pool_t *tp, log_t *log,
		pool_t *pool);
static void thread_pool_destroy(thread_pool_t *tp);
static void thread_pool_exit_handler(void *data, log_t *log);

static void *thread_pool_cycle(void *data);
static void thread_pool_handler(event_t *ev);

static char *thread_pool(conf_t *cf, command_t *cmd, void *conf);

static void *thread_pool_create_conf(cycle_t *cycle);
static char *thread_pool_init_conf(cycle_t *cycle, void *conf);

static int thread_pool_init_worker(cycle_t *cycle);
static void thread_pool_exit_worker(cycle_t *cycle);


/*
 * Syntax: thread_pool name threads=number [max_queue=number];
 * Default: thread_pool default threads=32 max_queue=65536; threads参数为该pool中线程个数，max_queue表示等待被线程调度的任务数
 *
 * Defines named thread pools used for multi-threaded reading and sending of files without blocking worker processes.
 * The threads parameter defines the number of threads in the pool. 
 * In the event that all threads in the pool are busy, a new task will wait in the queue. The max_queue parameter limits the 
 * number of tasks allowed to be waiting in the queue. By default, up to 65536 tasks can wait in the queue. When the queue 
 * overflows, the task is completed with an error. 
 * */
static command_t  thread_pool_commands[] = {
	{ string("thread_pool"),
		MAIN_CONF|DIRECT_CONF|CONF_TAKE23,
		thread_pool,
		0,
		0,
		NULL },

	null_command
};


static core_module_t  thread_pool_module_ctx = {
	string("thread_pool"),
	thread_pool_create_conf,
	thread_pool_init_conf
};


module_t  thread_pool_module = {
	MODULE_V1,
	&thread_pool_module_ctx,           /* module context */
	thread_pool_commands,              /* module directives */
	CORE_MODULE,                       /* module type */
	NULL,                                  /* init master */
	NULL,                                  /* init module */
	thread_pool_init_worker,           /* init process */
	NULL,                                  /* init thread */
	NULL,                                  /* exit thread */
	thread_pool_exit_worker,           /* exit process */
	NULL,                                  /* exit master */
	MODULE_V1_PADDING
};


static str_t  thread_pool_default = string("default");

static unsigned int					thread_pool_task_id;
static atomic_t						thread_pool_done_lock;//为0，可以获取锁，不为0，则不能获取到该锁
static thread_pool_queue_t			thread_pool_done; //所有的

