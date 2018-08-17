/*************************************************************************
    > File Name: threadpool_nginx.h
    > Author: zhengli
    > Mail: zldata@aliyun.com 
    > Note:  
    > Created Time: 2018年07月18日 星期三 07时53分58秒
 ************************************************************************/

#ifndef __THREADPOOL_NGINX__
#define __THREADPOOL_NGINX__

#include <pthread.h>

typedef void	(*CB_FUN)(void *);
typedef struct tp_threadpool_s	tp_threadpool_t;


// 配置参数
typedef struct tp_conf_s {
	unsigned int threadnum;			// 线程数
	unsigned int thread_stack_size;	// 线程堆栈大小
	unsigned int maxtasknum;		// 最大任务限制
}tp_conf_t;


tp_threadpool_t* threadpool_init(tp_conf_t *conf);

int threadpool_add_task(tp_threadpool_t *pool, CB_FUN handler, void* argv);

void threadpool_destroy(tp_threadpool_t *pool);

int threadpool_add_thread(tp_threadpool_t *pool);

int threadpool_set_max_tasknum(tp_threadpool_t *pool,unsigned int num);
#endif
