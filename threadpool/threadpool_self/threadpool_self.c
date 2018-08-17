/*************************************************************************
    > File Name: threadpool.c
    > Author: zhengli
    > Mail: zldata@aliyun.com 
    > Created Time: 三  7/18 16:12:42 2018
    > Brief: 
 ************************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include "threadpool_self.h"


typedef struct{
	void *(*function)(void *);  //函数指针
	void *arg;
}threadpool_task_t;

struct threadpool_s{
	pthread_mutex_t		lock;				// 互斥锁 - 其余
	pthread_mutex_t		thread_counter;		// 互斥锁 - 线程数
	pthread_cond_t		queue_not_full;		// 条件变量	- 队满
	pthread_cond_t		queue_not_empty;	// 条件变量 - 队空

	pthread_t			adjust_tid;		// 管理线程ID
	pthread_t			*threads;		// 工作线程池ID
	threadpool_task_t	*task_queue;	// 任务队列

	int		min_thr_num;		// 最小线程数
	int		max_thr_num;		// 最大线程数
	int 	live_thr_num;		// 当前存活线程数
	int 	busy_thr_num;		// 当前正在执行任务线程数
	int 	wait_exit_thr_num;	// 当前线程销毁数

	int 	queue_front;		// 当前队头下标
	int		queue_rear;			// 当前队尾下标
	int 	queue_size;			// 当前任务数
	int		queue_max_size;		// 任务队列最大值

	int		shutdown;
};


static void *adjust_thread(void *);
static void *threadpool_thread(void *);
static int pthreadpool_free(threadpool_t *);


/*========================================================== 
 * @function: 	threadpool_create()
 * @brief:		创建一个线程池
 * @param:		min_thr_num 线程池中最小线程个数
 * 				max_thr_num 线程池中最大线程个数
 * 				queue_max_size 线程池中最大任务数
 * @return:		成功返回线程池，失败返回NULL
 *==========================================================*/
threadpool_t *threadpool_create(threadpool_conf_t thr_conf)
{
	int i = 0, index = 0;
	threadpool_t *pool = NULL;

	do{
		pool = (threadpool_t *)malloc(sizeof(threadpool_t));
		if(pool == NULL) {
			printf("[threadpool_create] malloc threadpool fail %d times!\n", ++index);
			break;
		}
		
		pool->min_thr_num    = thr_conf.min_thr_num;
		pool->max_thr_num    = thr_conf.max_thr_num;
		pool->queue_max_size = thr_conf.queue_max_size;
		pool->busy_thr_num   = 0;
		pool->live_thr_num   = 0;
		pool->queue_size     = 0;
		pool->queue_front    = 0;
		pool->queue_rear     = 0;
		pool->shutdown       = false;

		//初始化存储线程ID的空间
		pool->threads = (pthread_t *)malloc(sizeof(pthread_t) * pool->max_thr_num);
		if(pool->threads == NULL) {
			printf("[threadpool_create] malloc threads fail %d times\n", ++index);
			break;
		}
		memset(pool->threads, 0, sizeof(pool->threads));

		//初始化任务队列
		pool->task_queue = (threadpool_task_t *)malloc(sizeof(threadpool_task_t) * pool->queue_max_size);
		if(pool->task_queue == NULL) {
			printf("[threadpool_create] malloc task_queue fail %d times!\n", ++index);
			break;
		}
		memset(pool->task_queue, 0, sizeof(pool->task_queue));

		//初始化互斥锁和条件变量
		if((pthread_mutex_init(&(pool->lock), NULL) != 0) || 
				(pthread_mutex_init(&(pool->thread_counter), NULL) != 0) || 
				(pthread_cond_init(&(pool->queue_not_empty), NULL) != 0) || 
				(pthread_cond_init(&(pool->queue_not_full), NULL) != 0)    )
		{
			printf("[threadpool_create] init the lock or cond fail %d times!\n", ++index);
			break;
		}
		
		//创建工作线程
		pthread_mutex_lock(&(pool->lock));
		for(i = 0; i < pool->min_thr_num; i++) {
			pthread_create(&(pool->threads[i]), NULL, threadpool_thread, (void *)pool);
			pool->live_thr_num++;
		}
		pthread_mutex_unlock(&(pool->lock));

		//创建管理线程
		pthread_create(&(pool->adjust_tid), NULL, adjust_thread, (void *)pool);
		return pool;
	} while(0);

	printf("[threadpool_create] thread init fail !!!\n");
	pthreadpool_free(pool);
	return NULL;
}

/*========================================================== 
 * @function: 	adjust_thread()
 * @brief:		管理线程的回调函数,用来管理线程池的动态增减
 * @param:		threadpool 线程池
 * @return:		无	
 *==========================================================*/
void *adjust_thread(void *threadpool)
{
	int i;
	int queue_size;
	int live_thr_num;
	int busy_thr_num;
	threadpool_t *pool = (threadpool_t *)threadpool;

	while(!pool->shutdown)
	{
		usleep(1000);
		pthread_mutex_lock(&(pool->lock));
		queue_size   = pool->queue_size;		// 任务数
		live_thr_num = pool->live_thr_num;		// 存活线程数
		pthread_mutex_unlock(&(pool->lock)); 

		pthread_mutex_lock(&(pool->thread_counter));
		busy_thr_num = pool->busy_thr_num;		// 忙线程个数
		pthread_mutex_unlock(&(pool->thread_counter));
		

		//创建线程 即任务数多于活着的线程个数 并且 活着的线程数不超过最大线程数	
		if((queue_size >= live_thr_num) && (live_thr_num < pool->max_thr_num))
		{
			pthread_mutex_lock(&(pool->lock));
			
			int add = 0;
			//一次性创建DEFAULT_THREAD_VARY（10）个线程
			for(i = 0; (i < pool->max_thr_num) && (add < DEFAULT_THREAD_VARY); i++)
			{
				if(pool->threads[i] == 0) {
					pthread_create(&(pool->threads[i]), NULL, threadpool_thread, (void *)pool);
					add++;
					pool->live_thr_num++;
				}
			}
			pthread_mutex_unlock(&(pool->lock));
		}

		//销毁线程
		//忙线程个数的2倍 < 存活线程个数 && 存活线程个数 > 最小线程个数
		if(((2 * busy_thr_num) < live_thr_num) && (live_thr_num > pool->min_thr_num))
		{
			pthread_mutex_lock(&(pool->lock));
			pool->wait_exit_thr_num += DEFAULT_THREAD_VARY;
			pthread_mutex_unlock(&(pool->lock));

			for(i = 0; i < DEFAULT_THREAD_VARY; i++) {
				pthread_cond_signal(&(pool->queue_not_empty));	
			}
		}
	}
	return 0; 
}

/*========================================================== 
 * @function: 	threadpool_thread()
 * @brief:		工作线程的回调函数
 * @param:		threadpool 线程池
 * @return:		无	
 *==========================================================*/
void *threadpool_thread(void *threadpool)
{
	int i = 0;
	threadpool_t *pool = (threadpool_t *)threadpool;
	threadpool_task_t task;

	while(true)
	{
		pthread_mutex_lock(&(pool->lock));
	
		//如果任务队列里没有任务时
		//阻塞在条件变量queue_not_empty,
		while(pool->queue_size  == 0 &&(!pool->shutdown))
		{
			pthread_cond_wait(&(pool->queue_not_empty), &(pool->lock));

			if(pool->wait_exit_thr_num > 0)
			{
				//存活线程个数 > 最小线程个数
				if(pool->live_thr_num > pool->min_thr_num)
				{
					-- (pool->wait_exit_thr_num);
					-- (pool->live_thr_num);

					int tid = pthread_self();
					for(i = 0; i < pool->max_thr_num; i++) {
						if(tid == pool->threads[i]) {
							pool->threads[i] = 0;
							break;
						}
					}

					pthread_mutex_unlock(&(pool->lock));

					pthread_exit(NULL);
				}
			}
		}

		if(pool->shutdown) {
			pthread_mutex_unlock(&(pool->lock));
			pthread_exit(NULL);
		}
		
		//任务的添加在pthreadpool_add实现
		task.function = pool->task_queue[pool->queue_front].function;
		task.arg = pool->task_queue[pool->queue_front].arg;
		
		//出队
		pool->queue_front = (pool->queue_front + 1)%(pool->queue_max_size);
		pool->queue_size--;

		pthread_cond_broadcast(&(pool->queue_not_full));
		pthread_mutex_unlock(&(pool->lock));

		pthread_mutex_lock(&(pool->thread_counter));
		pool->busy_thr_num++;
		pthread_mutex_unlock(&(pool->thread_counter));

		(*(task.function))(task.arg);
		//printf("线程 0x%x 完成了任务\n", (unsigned int)pthread_self());

		pthread_mutex_lock(&(pool->thread_counter));
		pool->busy_thr_num--;
		pthread_mutex_unlock(&(pool->thread_counter));
	}
	pthread_exit(NULL);
}

/*========================================================== 
 * @function: 	threadpool_add()
 * @brief:		将任务加入到线程池中并执行
 * @param:		pool 线程池
 * 				*(function)(void *arg) 线程回调函数
 * 				*arg 回调函数参数
 * @return:		成功返回0，失败返回-1
 *==========================================================*/
int threadpool_add(threadpool_t *pool, void *(*function)(void *arg), void *arg)
{
	pthread_mutex_lock(&(pool->lock));

	//（队满）任务队列中的任务数 == 任务队列中最大任务数 && 开启线程池参数
	while((pool->queue_size == pool->queue_max_size) && (!pool->shutdown)) {
		pthread_cond_wait(&(pool->queue_not_full), &(pool->lock));
	}

	if(pool->shutdown) {
		pthread_mutex_unlock(&(pool->lock));
	}

	/* add a task to queue */
	pool->task_queue[pool->queue_rear].function = function;
	pool->task_queue[pool->queue_rear].arg= arg;

	// 入队
	pool->queue_rear = (pool->queue_rear +1) % pool->queue_max_size;
	pool->queue_size++;

	/* queue not empty, 唤醒通知等待处理任务的线程 */
	pthread_cond_signal(&(pool->queue_not_empty));

	pthread_mutex_unlock(&(pool->lock));

	return 0;
}

/*========================================================== 
 * @function: 	threadpool_free()
 * @brief:		释放线程池
 * @param:		pool 线程池
 * @return:		成功返回0，失败返回-1
 *==========================================================*/
int pthreadpool_free(threadpool_t *pool)
{
	if(pool == NULL)	return -1;

	if(pool->task_queue)
		free(pool->task_queue);

	if(pool->threads) {
		free(pool->threads);

		pthread_mutex_lock(&(pool->lock));
		pthread_mutex_destroy(&(pool->lock));
		pthread_mutex_lock(&(pool->thread_counter));
		
		pthread_mutex_destroy(&(pool->thread_counter));
		pthread_cond_destroy(&(pool->queue_not_empty));
		pthread_cond_destroy(&(pool->queue_not_full));
	}

	free(pool);
	return 0;
}

/*========================================================== 
 * @function: 	threadpool_destory()
 * @brief:		销毁线程池
 * @param:		pool 线程池
 * @return:		成功返回0，失败返回-1
 *==========================================================*/
int threadpool_destroy(threadpool_t *pool)
{
	int i = 0;
	if(pool == NULL) return -1;

	pool->shutdown = true;
	
	pthread_join(pool->adjust_tid, NULL);

	for(i = 0; i < pool->live_thr_num; i++) {
		pthread_cond_broadcast(&(pool->queue_not_empty));
		if(pool->threads[i] != 0) {
			pthread_join(pool->threads[i], NULL);
		}
	}
	pthreadpool_free(pool);
	return 0;
}
