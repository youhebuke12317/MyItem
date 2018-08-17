/********************************************************************
 ** Copyright(c) 2016, luzeya
 ** All rights reserved
 **
 ** 文件名：FixedThreadPool.c
 ** 创建人：路泽亚
 ** 创建日期： 2016-10-23
 **
 ** 描  述：固定线程个数的线程池
 ** 注  意：1.
 ********************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>

#include "FixedThreadPool.h"

typedef struct Work {
    void (*func)(void *arg);
    void *arg;
} Work;

static void* process(void *useless);

FixedThreadPool *FTPoolNew(int num)
{
    int i = 0;
    FixedThreadPool *pool;

    pool = malloc(sizeof(FixedThreadPool));
    if (!pool)
        return NULL;

    pool->threads_pid = calloc(num, sizeof(pthread_t));
    if (!pool->threads_pid) {
        free(pool);
        return NULL;
    }

    pool->queue = AQNew(sizeof(Work));
    if (!pool->queue) {
        free(pool->threads_pid);
        free(pool);
        return NULL;
    }

    pool->num_threads = num;
    pool->shutdown    = 0;
    pool->immediate   = 1;
    pool->num_idle    = num;

    AQLock(pool->queue);
    /* 初始化线程 */
    for (i = 0; i < num; i++) {
        /* TODO: 当有线程创建失败时，之前创建好的线程还要取消 */
        int flag = pthread_create(&(pool->threads_pid[i]),
                                  NULL,
                                  process,
                                  pool);
        if (flag != 0) {
            printf("FTPoolNew Thread Create Fail!(%s)", strerror(flag));
            AQUnlock(pool->queue);
            AQDestroy(pool->queue);
            free(pool->threads_pid);
            free(pool);
            return NULL;
        }
    }
    AQUnlock(pool->queue);

    return pool;
}

void FTPoolDestroy(FixedThreadPool *pool)
{
    int i = 0;

    assert(pool);

    /* 停止所有线程 */
    pool->shutdown = 1;
    AQBroadcast(pool->queue);
    for (i = 0; i < pool->num_threads; i++) {
        int flag = 0;
        if ((flag = pthread_join(pool->threads_pid[i], NULL))) {
            /* 发生错误 */
            printf("Thread Join Error!(%s)\n", strerror(flag));
            return;
        }
    }

    /* 释放资源: 队列，pid数组，pool本身 */
    if (pool->queue)
        AQDestroy(pool->queue);
    if (pool->threads_pid)
        free(pool->threads_pid);

    free(pool);
}

/**
 * FTPoolPush
 * 如果入队的时候内存分配失败，就直接什么也不做
 * @param pool
 * @param func
 */
void FTPoolPush(FixedThreadPool *pool, void (*func)(void *arg), void *arg)
{
    Work work;

    assert(pool);
    assert(func);

    work.func = func;
    work.arg  = arg;

    AQPush(pool->queue, &work);
}

static
void* process(void *data)
{
    Work work;
    FixedThreadPool *pool = data;

    while (1) {
        AQLock(pool->queue);

        AQPopUnlocked(pool->queue, &work, &pool->shutdown);
        if (pool->shutdown == 1)
            break;

        pool->num_idle--;
        AQUnlock(pool->queue);

        work.func(work.arg);
        pool->num_idle++;
    }
    AQUnlock(pool->queue);
    pthread_exit(NULL);
}

