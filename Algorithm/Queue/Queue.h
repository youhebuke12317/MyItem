/*************************************************************************
    > File Name: Queue.h
    > Author: zhengli
    > Mail: zldata@aliyun.com 
    > Created Time: 二  4/ 3 23:10:54 2018
    > Brief: 
 ************************************************************************/


#ifndef __QUQUQ_H__
#define __QUQUQ_H__

typedef struct LOG_QUEUE_S		LOG_QUEUE;
typedef struct QUEUE_HEAD_S		QUEUE_HEAD;

struct QUEUE_HEAD_S {
	LOG_QUEUE queue;
}


/* 队列容纳元素个数 */ 
#define QUEUE_SIZE 1024

// size: 队列元素大小
int init_log_queue(LOG_QUEUE *queue, int size);

void inc_read_ptr(LOG_QUEUE *queue);

void inc_write_ptr(LOG_QUEUE *queue);

void *get_uint_for_read(LOG_QUEUE *queue);

void *get_uint_for_write(LOG_QUEUE *queue);




#endif
