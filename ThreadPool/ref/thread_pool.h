/*************************************************************************
    > File Name: thread_pool.h
    > Author: zhengli
    > Mail: zldata@aliyun.com 
    > Created Time: 五  4/ 6 11:52:23 2018
    > Brief: 
 ************************************************************************/


#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

// 一个该结构对应一个threads_pool线程池配置
typedef struct thread_pool_s	thread_pool_t;
typedef struct thread_task_s	thread_task_t;

// typedef void	(*TaskHandler)(void *data, log_t *log);

/**
 * @brief	next	指向下一个提交的任务
 * @brief	id		任务id  每添加一个任务就自增加，见thread_pool_task_id 
 * @brief	ctx		执行回调函数的参数
 * @brief	handler	回调函数 执行完handler后会通过notify执行event->handler 
 * @brief	event	一个任务和一个事件对应  事件在通过notify在thread_pool_handler中执行
 */
struct thread_task_s {
    thread_task_t		*next;	
    unsigned int		id;		
    void                *ctx;
    void				(*handler)(void *data, log_t *log); 	//thread_pool_cycle中执行
    event_t				event;	
    // TaskHandler		handler;								
};


thread_pool_t *thread_pool_add(conf_t *cf, str_t *name);

thread_pool_t *thread_pool_get(cycle_t *cycle, str_t *name);

thread_task_t *thread_task_alloc(pool_t *pool, size_t size);

int thread_task_post(thread_pool_t *tp, thread_task_t *task);


#endif
