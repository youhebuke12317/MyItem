/********************************************************************
 ** Copyright(c) 2016, luzeya
 ** All rights reserved
 **
 ** 文件名：FixedThreadPool.h
 ** 创建人：路泽亚
 ** 创建日期： 2016-10-23
 **
 ** 描  述：固定线程个数的线程池
 ** 注  意：1.
 ********************************************************************/
#ifndef FIXEDTHREADPOOL_H
#define FIXEDTHREADPOOL_H

#include "AsyncQueue.h"

typedef struct FixedThreadPool {
    /* 池中线程个数 */
    int num_threads;
    int num_idle;

    /* 线程池中线程的pid数组 */
    pthread_t *threads_pid;

    /* 信号通知 */
    int shutdown;
    int immediate;

    /* 线程池使用的异步队列 */
    AsyncQueue *queue;
} FixedThreadPool;

FixedThreadPool *FTPoolNew(int num);

void FTPoolPush(FixedThreadPool *pool, void (*func)(void *arg), void *arg);

void FTPoolDestroy(FixedThreadPool *pool);

#endif /* FIXEDTHREADPOOL_H */
