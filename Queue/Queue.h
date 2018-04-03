/*************************************************************************
    > File Name: Queue.h
    > Author: zhengli
    > Mail: zldata@aliyun.com 
    > Created Time: 二  4/ 3 23:10:54 2018
    > Brief: 
 ************************************************************************/


#ifndef __QUQUQ_H__
#define __QUQUQ_H__


// #define QUEUE_SIZE 1024

struct LOG_QUEUE;

/**
 * @brief 初始化环形队列
 *
 * @param queue	队列首地址
 * @param size	队列中元素的大小
 * @param qnum	环形队列容纳元素个数
 *
 * @return	成功返回0 失败返回-1
 */
int init_log_queue(LOG_QUEUE *queue, int size, size_t qnum);


/**
 * @brief 入队
 *
 * @param queue	队列的管理结构指针
 * @param err	返回节点为空的出错次数
 *
 * @return 成功返回队列节点指针 失败返回NULL
 */
void *EnQueue(LOG_QUEUE *queue, int err);

/**
 * @brief 出队
 *
 * @param queue 队列的管理结构指针
 * @param err   返回节点为空的出错次数
 *
 * @return  成功返回队列节点指 失败返回NULL
 */
void *DeQueue(LOG_QUEUE *queue, int err);



#endif
