/*************************************************************************
    > File Name: threadpool.h
    > Author: zhengli
    > Mail: zldata@aliyun.com 
    > Created Time: 三  7/18 16:11:29 2018
    > Brief: 
 ************************************************************************/

#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#define		DEFAULT_THREAD_VARY	10
#define		true	1
#define		false	0

typedef struct threadpool_s threadpool_t;

typedef struct threadpool_conf_s {
	int min_thr_num;		// 线程池中最小线程个数
	int max_thr_num;		// 线程池中最大线程个数
	int queue_max_size;		// 线程池中最大任务数
}threadpool_conf_t;

threadpool_t *threadpool_create(threadpool_conf_t thr_conf);

int threadpool_add(threadpool_t *pool, void *(*function)(void *arg), void *arg);

int threadpool_destroy(threadpool_t *pool);

#endif
