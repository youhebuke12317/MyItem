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
#include "Queue.h"

struct LOG_QUEUE_S {
	int				head;
	int				tail;
	void			*data[QUEUE_SIZE];
}; 

// 需要保证QUEUE_SIZE是2的次幂
#define QUEUE_MASK					(QUEUE_SIZE - 1)

#define QUEUE_FULL(queue)			((((queue) -> tail + 1) & QUEUE_MASK) == (queue) -> head)

#define QUEUE_EMPTY(queue)			((queue) -> head == (queue) -> tail)

#define INC_HEAD(queue)				(queue) -> head = ((queue) -> head + 1) & QUEUE_MASK

#define INC_TAIL(queue)				(queue) -> tail = ((queue) -> tail + 1) & QUEUE_MASK

#define QUEUE_INTERVAL(queue)		((queue)->tail - (queue)->head)

#define QUEUE_ITEM_NUM(queue)		((queue)->tail>=(queue)->head)? QUEUE_INTERVAL(queue):(QUEUE_SIZE+QUEUE_INTERVAL(queue))  

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
	if(ptr == NULL) return -1;
    memset(ptr, 0, size * QUEUE_SIZE);
	
	for(i = 0; i < QUEUE_SIZE; ++i) {
		queue -> data[i] = ptr + (i * size);
	}
	
	queue -> head  = 0;
	queue -> tail  = 0;
	
	return 0;
}



/**
 *	获取读单元地址
 */
void *get_uint_for_read(LOG_QUEUE *queue)
{
	if(QUEUE_EMPTY(queue))
		return NULL;
	
	return queue -> data[queue -> head];
}

/**
 *	获取写单元地址
 */
void *get_uint_for_write(LOG_QUEUE *queue)
{
	if(QUEUE_FULL(queue)) 
		return NULL;

	return (queue -> data[queue -> tail]);
}

/**
 *	后移写指针
 */
void inc_write_ptr(LOG_QUEUE *queue)
{
	INC_TAIL(queue);

	return ;
}

/**
 *	后移读指针
 */
void inc_read_ptr(LOG_QUEUE *queue) 
{
	INC_HEAD(queue);

	return ;
}


#if 1

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int N;
pthread_t cid;
static LOG_QUEUE queue;

void output(int a) {
	printf("%d\n", a);
}


void *consumer() {
	while (1) {
		int *tmp = (int *)get_uint_for_read(&queue);
		if (tmp == NULL) { 
			usleep(10); 
			continue;
		}
		inc_read_ptr(&queue);
		output(*tmp);
	}	
}

void *producer() {
	for (int i = 0; i < N; i++) {
		int *tmp = NULL;
		while ((tmp = (int *)get_uint_for_write(&queue)) == NULL) /* void */;
		*tmp = i;
		inc_write_ptr(&queue);
	}
}

int main() {
	printf("please input queue element num: ");
	scanf("%d", &N);

	init_log_queue(&queue, sizeof(int));

	pthread_create(&cid, NULL, consumer, NULL);

	producer();

	while (1) sleep(0x7FFFFFFF);

	return 0;
}


#endif
