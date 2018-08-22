/*************************************************************************
    > File Name: threadpool_nginx.c
    > Author: zhengli
    > Mail: zldata@aliyun.com 
    > Note: 线程池 使用线程库中的 mutex cond key thread_stacksize  
    > Created Time: 2018年07月18日 星期三 08时18分05秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "threadpool_nginx.h"

#define MAX_TASK_SIZE 10000000

typedef struct tp_task_s		tp_task_t;

// 任务结构体
struct tp_task_s {
	void		*argv;
	CB_FUN		handler;
	tp_task_t	*next;		// 任务链指针 
};

// 任务队列 
typedef struct tp_task_queue_s {
	tp_task_t		*head;		// 队列头
	tp_task_t		**tail;		// 队列尾
	unsigned int	maxtasknum; // 最大任务限制
	unsigned int	curtasknum; // 当前任务数
}tp_task_queue_t;

// 线程池
struct tp_threadpool_s {
	pthread_mutex_t		mutex;  // 互斥锁
	pthread_cond_t		cond;	// 条件锁
	tp_task_queue_t     tasks;	// 任务队列

	unsigned int		threadnum;			// 线程数限制
	unsigned int		thread_stack_size;	// 线程堆栈大小
};

static 	pthread_key_t  key;

inline void z_task_queue_init(tp_task_queue_t* task_queue);
inline void z_thread_mutex_destroy(pthread_mutex_t *mutex);
inline int  z_thread_cond_create(pthread_cond_t *cond);
inline void z_thread_cond_destroy(pthread_cond_t *cond);
inline int  z_thread_key_create();
inline void z_thread_key_destroy();
inline void z_change_maxtask_num(tp_threadpool_t *pool, unsigned int num);

static int  z_conf_check(tp_conf_t *conf);
static int  z_thread_mutex_create(pthread_mutex_t *mutex);
static int  z_threadpool_create(tp_threadpool_t *pool);
static void z_threadpool_cycle(void* argv);
static int  z_thread_add(tp_threadpool_t *pool);
static void z_threadpool_exit_cb(void* argv);


//初始化一个线程池  conf为配置参数
tp_threadpool_t* threadpool_init(tp_conf_t *conf)
{
	pthread_attr_t		attr;
	int	error_flag_mutex = 0;
	int	error_flag_cond  = 0;
	tp_threadpool_t	*pool = NULL;
	
	do {
		// 检查参数是否合法
		if (z_conf_check(conf) == -1) { 
			break;
		}

		// 申请线程池句柄
		pool = (tp_threadpool_t *)malloc(sizeof(tp_threadpool_t));
		if (pool == NULL){
			break;
		}

		//初始化线程池基本参数
		pool->threadnum			= conf->threadnum;
		pool->thread_stack_size = conf->thread_stack_size;
		pool->tasks.maxtasknum	= conf->maxtasknum;
		pool->tasks.curtasknum	= 0;

		z_task_queue_init(&pool->tasks);
	
		// 创建一个pthread_key_t，用以访问线程全局变量。
		if (z_thread_key_create() != 0){
			free(pool);
			break;
		}

		if (z_thread_mutex_create(&pool->mutex) != 0){ //初始化互斥锁
			z_thread_key_destroy();
			free(pool);
			break;
		}

		if (z_thread_cond_create(&pool->cond) != 0){  //初始化条件锁
			z_thread_key_destroy();
			z_thread_mutex_destroy(&pool->mutex);
			free(pool);
			break;
		}

		if (z_threadpool_create(pool) != 0){       //创建线程池
			z_thread_key_destroy();
			z_thread_mutex_destroy(&pool->mutex);
			z_thread_cond_destroy(&pool->cond);
			free(pool);
			break;
		}

		return pool;

	} while(0);

	return NULL;
}

// 向线程池中添加一个任务。handler为回调函数，argv为参数
int threadpool_add_task(tp_threadpool_t *pool, CB_FUN handler, void* argv)
{
	tp_task_t *task = NULL;
	task = (tp_task_t *)malloc(sizeof(tp_task_t));
	if (task == NULL)		return -1;

	task->handler = handler;
	task->argv = argv;
	task->next = NULL;
	
	if (pthread_mutex_lock(&pool->mutex) != 0) {
		free(task);
		return -1;
	}

	do {
		// 判断工作队列中的任务数是否达到限制
		if (pool->tasks.curtasknum >= pool->tasks.maxtasknum) {
			break;
		}

		// 将任务节点尾插到任务队列
		*(pool->tasks.tail) = task;
		pool->tasks.tail = &task->next;
		pool->tasks.curtasknum ++;

		//通知阻塞的线程
		if (pthread_cond_signal(&pool->cond) != 0){
			break;
		}

		//解锁
		pthread_mutex_unlock(&pool->mutex);

		return 0;

	} while(0);

	pthread_mutex_unlock(&pool->mutex);
	free(task);

	return -1;
}


//销毁线程池。
void threadpool_destroy(tp_threadpool_t *pool)
{
	unsigned int n = 0;
	volatile unsigned int  lock;

	//z_threadpool_exit_cb函数会使对应线程退出
	for (; n < pool->threadnum; n++){
		lock = 1;

		if (threadpool_add_task(pool, 
					(void *)z_threadpool_exit_cb,
					(void *)&lock) != 0)
		{
			return;
		}

		while (lock){
			usleep(1);
		}
	}

	z_thread_mutex_destroy(&pool->mutex);
	z_thread_cond_destroy(&pool->cond);
	z_thread_key_destroy();
	free(pool);
}

//给线程池中增加一个工作线程
int threadpool_add_thread(tp_threadpool_t *pool)
{
	int ret = 0;
	
	if (pthread_mutex_lock(&pool->mutex) != 0){
		return -1;
	}

	ret = z_thread_add(pool);
	
	pthread_mutex_unlock(&pool->mutex);
	
	return ret;
}

//设置新的最大任务限制   0为不限制
int threadpool_set_max_tasknum(tp_threadpool_t *pool,unsigned int num)
{
	if (pthread_mutex_lock(&pool->mutex) != 0){
		return -1;
	}

	z_change_maxtask_num(pool, num);  //改变最大任务限制

	pthread_mutex_unlock(&pool->mutex);

	return 0;
}









//检测线程池配置参数是否合法
int z_conf_check(tp_conf_t *conf)
{
	if (conf == NULL){
		return -1;
	}

	if (conf->threadnum < 1){
		return -1;
	}

	if (conf->maxtasknum < 1){
		conf->maxtasknum = MAX_TASK_SIZE;
	}
	return 0;
}

/* queue init */
inline void z_task_queue_init(tp_task_queue_t* task_queue)
{
	task_queue->head = NULL;
	task_queue->tail = &task_queue->head;
}

/* mutex init */
int z_thread_mutex_create(pthread_mutex_t *mutex)
{
	int	ret = 0;
	pthread_mutexattr_t attr;

	if (pthread_mutexattr_init(&attr) != 0) {
		return -1;
	}

	// 检错锁
	// 如果同一个线程请求同一个锁，则返回EDEADLK
	// 这样就保证当不允许多次加锁时不会出现最简单情况下的死锁。
	if (pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK) != 0){
		pthread_mutexattr_destroy(&attr);
		return -1;
	}

	ret = pthread_mutex_init(mutex, &attr);

	pthread_mutexattr_destroy(&attr);

	return ret;
}

/* mutex destory */
inline void z_thread_mutex_destroy(pthread_mutex_t *mutex)
{
	pthread_mutex_destroy(mutex);
}

/* cond init */
inline int z_thread_cond_create(pthread_cond_t *cond)
{
	return pthread_cond_init(cond, NULL);
}

/* cond destory */
inline void z_thread_cond_destroy(pthread_cond_t *cond)
{
	pthread_cond_destroy(cond);
}

/* key init */
inline int z_thread_key_create()
{
	return pthread_key_create(&key, NULL);
}

/* key destory */
inline void z_thread_key_destroy()
{
	pthread_key_delete(key);
}

/* change maxtask */
inline void z_change_maxtask_num(tp_threadpool_t *pool, unsigned int num)
{
	pool->tasks.maxtasknum = num;
	if (pool->tasks.maxtasknum < 1) {
		pool->tasks.maxtasknum = MAX_TASK_SIZE;
	}
}


int z_threadpool_create(tp_threadpool_t *pool)
{
	int i = 0;
	pthread_t  pid;
	pthread_attr_t attr;

	if (pthread_attr_init(&attr) != 0){
		return -1;
	}

	// 设置线程堆栈大小
	if (pool->thread_stack_size != 0) {
		if (pthread_attr_setstacksize(&attr, 
					pool->thread_stack_size) != 0)
		{
			pthread_attr_destroy(&attr);
			return -1;
		}
	}

	//创建线程池
	for (; i < pool->threadnum; ++i) {
		pthread_create(&pid, &attr, (void *)z_threadpool_cycle, (void *)pool);
	}	

	pthread_attr_destroy(&attr);

	return 0;
}




//工作线程
void z_threadpool_cycle(void* argv)
{
	sigset_t set;
	tp_task_t *ptask = NULL;
	unsigned int exit_flag = 0;
	tp_threadpool_t *pool = (tp_threadpool_t*)argv;

	//只注册以下致命信号，其他全部屏蔽
	sigfillset(&set);
	sigdelset(&set, SIGILL);
	sigdelset(&set, SIGFPE);
	sigdelset(&set, SIGSEGV);
	sigdelset(&set, SIGBUS);
	
	// 设置exit_flag = 0
	// 为指定线程特定数据键设置线程特定绑定
	if (pthread_setspecific(key,(void*)&exit_flag) != 0) {
		return;
	}

	if (pthread_sigmask(SIG_BLOCK, &set, NULL) != 0) {
		return;
	}

	// exit_flag为1时线程退出
	while(!exit_flag) {     

		if (pthread_mutex_lock(&pool->mutex) != 0) {  
			return;
		}

		while(pool->tasks.head == NULL) {
			if (pthread_cond_wait(&pool->cond, &pool->mutex) != 0) {
				pthread_mutex_unlock(&pool->mutex);
				return;
			}
		}
		
		// 从任务队列中获取一个任务任务节点
		ptask = pool->tasks.head;     
		pool->tasks.head = ptask->next;

		pool->tasks.curtasknum--;   

		if (pool->tasks.head == NULL){
			pool->tasks.tail = &pool->tasks.head;
		}

		if (pthread_mutex_unlock(&pool->mutex) != 0){ 
			return;
		}

		ptask->handler(ptask->argv);  //执行任务。

		free(ptask);

		ptask = NULL;
	}

	pthread_exit(0);
}


/* 调用该函数接口时 需要对参数pool加锁 */
int z_thread_add(tp_threadpool_t *pool)
{
	int ret = 0;
	pthread_t  pid;
	pthread_attr_t attr;

	if (pthread_attr_init(&attr) != 0) {
		return -1;
	}

	if (pool->thread_stack_size != 0) {
		if (pthread_attr_setstacksize(&attr, pool->thread_stack_size) != 0){
			pthread_attr_destroy(&attr);
			return -1;
		}
	}

	ret = pthread_create(&pid, &attr, (void *)z_threadpool_cycle, (void *)pool);
	if (ret == 0) {
		pool->threadnum++;		
	}

	pthread_attr_destroy(&attr);
	
	return ret;
}


//线程池退出函数  
void z_threadpool_exit_cb(void* argv)
{
	unsigned int *lock = argv;
	unsigned int *pexit_flag = NULL;
	pexit_flag = (int *)pthread_getspecific(key);

	*pexit_flag = 1;    // 将exit_flag置1
	pthread_setspecific(key, (void*)pexit_flag);

	*lock = 0;
}

