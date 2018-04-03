/*************************************************************************
    > File Name: Queue.c
    > Author: zhengli
    > Mail: zldata@aliyun.com 
    > Created Time: 二  4/ 3 23:04:33 2018
    > Brief: 
 ************************************************************************/

#include <string.h>
#include <stdlib.h>
#include <syslog.h>

#include "queue.h"


#define QUEUE_MASK											\
	(QUEUE_SIZE - 1)

#define QUEUE_FULL(queue)									\
	((((queue) -> tail + 1) & QUEUE_MASK) == (queue) -> head)

#define QUEUE_EMPTY(queue)									\
	((queue) -> head == (queue) -> tail)

#define INC_HEAD(queue)										\
	(queue) -> head = ((queue) -> head + 1) & QUEUE_MASK

#define INC_TAIL(queue)										\
	(queue) -> tail = ((queue) -> tail + 1) & QUEUE_MASK

#define QUEUE_INTERVAL(queue)								\
	((queue)->tail - (queue)->head)

#define QUEUE_ITEM_NUM(queue)								\
	((queue)->tail>=(queue)->head)? QUEUE_INTERVAL(queue):(QUEUE_SIZE+QUEUE_INTERVAL(queue))  


typedef struct LOG_QUEUE {
	int				head;
	int				tail;
	void			*data[QUEUE_SIZE];
	int				count;		/* 循环队列中元素个数 */
	pthread_mutex_t	mutex;		/* 队列锁 */
}LOG_QUEUE; 


static void inc_read_ptr(LOG_QUEUE *queue);
static void inc_write_ptr(LOG_QUEUE *queue);
static void *get_uint_for_read(LOG_QUEUE *queue);
static void *get_uint_for_write(LOG_QUEUE *queue);

/**
 * @brief 初始化环形队列
 *
 * @param queue	队列首地址
 * @param size	队列中元素的大小
 *
 * @return 
 */
int init_log_queue(LOG_QUEUE *queue, int size)
{
	void *ptr; 
	int i;

    ptr = malloc(size * QUEUE_SIZE);
	if(ptr == NULL) {
		return -1;
	}
    memset(ptr, 0, size * QUEUE_SIZE);
	
	for(i = 0; i < QUEUE_SIZE; ++i) {
		queue -> data[i] = ptr + (i * size);
	}
	
	queue -> head  = 0;
	queue -> tail  = 0;
	queue -> count = 0;
	
	int ret = pthread_mutex_init(&(queue -> mutex), NULL);
	if (ret != 0) {
		printf("init queue: queue mutex init error\n"); 
		return -1;
	}  
	
	return 0;
}


/**
 * @brief 入队
 *
 * @param queue	队列的管理结构指针
 * @param err	返回节点为空的出错次数
 *
 * @return 成功返回队列节点指针 失败返回NULL
 */
void *EnQueue(LOG_QUEUE *queue, int err)
{
	pthread_mutex_lock(&queue -> mutex);

	int 	index = 0;
	void 	**ptr;

	for (/* NULL */; index < err; index++) {
		ptr = get_uint_for_write(queue);
		if (ptr != NULL || *ptr != NULL) {
			inc_write_ptr(queue);
			break;
		}
	}

	pthread_mutex_unlock(&queue -> mutex);

	return ptr;
}


/**
 * @brief 出队
 *
 * @param queue 队列的管理结构指针
 * @param err   返回节点为空的出错次数
 *
 * @return  成功返回队列节点指 失败返回NULL
 */
void *DeQueue(LOG_QUEUE *queue, int err)
{
	pthread_mutex_lock(&queue -> mutex);

	int 	index = 0;
	void 	*ptr;

	for (/* NULL */; index < err; index++) {
		ptr = get_uint_for_read(queue);
		if (ptr != NULL) {
			inc_read_ptr(queue);
			break;
		}
	}

	pthread_mutex_unlock(&queue -> mutex);

	return ptr;
}



/**
 *	获取读单元地址
 */
static void *get_uint_for_read(LOG_QUEUE *queue)
{
	if (queue == NULL) 	return NULL;

	if(QUEUE_EMPTY(queue))
		return NULL;
	
	return queue -> data[queue -> head];
}

/**
 *	获取写单元地址
 */
static void *get_uint_for_write(LOG_QUEUE *queue)
{
	if (queue == NULL) 	return NULL;

	if(QUEUE_FULL(queue)) {
        printf("QUEUE_FULL\n");
		return NULL;
    }

	return (queue -> data[queue -> tail]);
}

/**
 *	后移写指针
 */
static void inc_write_ptr(LOG_QUEUE *queue)
{
	if (queue == NULL) 	return ;

	INC_TAIL(queue);

	(queue -> count)++;	

	return ;
}

/**
 *	后移读指针
 */
static void inc_read_ptr(LOG_QUEUE *queue)
{
	if (queue == NULL) 	return;

	INC_HEAD(queue);

	(queue -> count)--;	

	return ;
}


