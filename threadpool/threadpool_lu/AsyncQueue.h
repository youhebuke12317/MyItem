/********************************************************************
 ** Copyright(c) 2016, luzeya
 ** All rights reserved
 **
 ** 文件名：AsyncQueue.h
 ** 创建人：路泽亚
 ** 创建日期： 2016-10-23
 **
 ** 描  述：链式异步队列
 ** 注  意：
 ********************************************************************/
#ifndef ASYNCQUEUE_H
#define ASYNCQUEUE_H

#include <pthread.h>

typedef struct AQNode {
    struct AQNode *next;

    /* gcc扩展 零长数组 */
    char data[0];
} AQNode;

typedef struct AsyncQueue {
    /* 队列结构体中数据部分的长度 */
    int size;

    /* 队列长度 */
    int     num;
    /* 队列头尾指针 */
    AQNode *head;
    AQNode *tail;

    /* 等待的线程数 */
    int waiting;

    /* 这个锁不仅保护条件变量，同样保护队列 */
    pthread_mutex_t mutex;
    /* 保护队列空的条件变量 */
    pthread_cond_t  cond;
} AsyncQueue;


AsyncQueue *AQNew(int size);
void  AQDestroy(AsyncQueue *q);
int   AQPushUnlocked(AsyncQueue *q, void *data);
int   AQPush(AsyncQueue *q, void *data);
void  AQPopUnlocked(AsyncQueue *q, void *data, int *shutdown);
void  AQPop(AsyncQueue *q, void *data);
void  AQLock(AsyncQueue *q);
void  AQUnlock(AsyncQueue *q);
void  AQBroadcast(AsyncQueue *q);

#endif /* ASYNCQUEUE_H */
