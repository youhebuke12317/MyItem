/********************************************************************
 ** Copyright(c) 2016, luzeya
 ** All rights reserved
 **
 ** 文件名：AsyncQueue.c
 ** 创建人：路泽亚
 ** 创建日期： 2016-10-23
 **
 ** 描  述：异步队列（阻塞队列），队列本身采用链式队列
 ** 注  意：1.
 ********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "AsyncQueue.h"

AsyncQueue *AQNew(int size)
{
    AsyncQueue *q;

    q = malloc(sizeof(AsyncQueue));
    if (!q)
        return NULL;

    q->num  = 0;
    q->head = NULL;
    q->tail = NULL;
    q->size = size;

    q->waiting   = 0;

    /**
     * 这两个函数从不会返回错误码
     * man 3 pthread_cond_init (ERRORS)
     * man 3 pthread_mutex_init (RETURN VALUE)
     */
    pthread_mutex_init(&(q->mutex), NULL);
    pthread_cond_init(&(q->cond), NULL);

    return q;
}

/* TODO: 这里还有问题，如果释放时有锁，怎么办? */
void AQDestroy(AsyncQueue *q)
{
    assert(q);

    /* 释放时锁上不能有线程阻塞 */
    pthread_cond_destroy(&(q->cond));
    /* 摧毁时必须是无锁的 */
    pthread_mutex_destroy(&(q->mutex));
    /* 释放链表 */
    {
        AQNode *temp = q->head;
        while (temp != NULL) {
            q->head = q->head->next;
            free(temp);
            temp = q->head;
        }
    }
    /* 释放内存 */
    free(q);
}

/**
 * AQPushUnlocked
 * 没有加锁的入队操作，唯一可能会失败的是内存分配失败
 * @param q
 * @param data
 * @return -1 失败 0 成功
 */
int AQPushUnlocked(AsyncQueue *q, void *data)
{
    AQNode *temp;

    temp = malloc(sizeof(AQNode) + q->size);
    if (!temp) return -1;

    temp->next = NULL;
    memcpy(temp->data, data, q->size);

    /* 入队操作 */
    if (q->tail) q->tail->next = temp;
    q->tail = temp;
    if (!q->head) q->head = temp;
    q->num++;

    /* 如果有等待的线程则唤醒一个 */
    if (q->waiting > 0)
        pthread_cond_signal(&q->cond);
    return 0;
}

/**
 * AQPush
 * 加锁的入队操作，唯一可能导致失败的是内存分配失败
 * @param q
 * @param data
 * @return -1 失败 0 成功
 */
int AQPush(AsyncQueue *q, void *data)
{
    int flag;

    assert(q);
    assert(data);

    pthread_mutex_lock(&(q->mutex));
    flag = AQPushUnlocked(q, data);
    pthread_mutex_unlock(&(q->mutex));
    return flag;
}

/**
 * AQPopUnlocked
 *
 * @param q
 * @param data
 * @param shutdown
 */
void AQPopUnlocked(AsyncQueue *q, void *data, int *shutdown)
{
    AQNode *temp;

    /* 如果队列为空 */
    if (!q->tail) {
        /* 说明出队的线程要被阻塞 */
        q->waiting++;
        /* 对队列为空的条件进行阻塞（还有shutdown为1时，这个给线程池用的） */
        while (!q->tail && !(*shutdown)) {
            pthread_cond_wait(&(q->cond), &(q->mutex));
        }
        q->waiting--;
    }

    if (*shutdown) {
        return;
    }

    assert(q->tail);
    assert(!(*shutdown));

    /* 出队操作 */
    temp = q->head;
    q->head = q->head->next;
    if (!q->head) q->tail = NULL;
    q->num--;

    /* 释放AQNode内存 */
    memcpy(data, temp->data, q->size);
    free(temp);
	temp = NULL;
}

void AQPop(AsyncQueue *q, void *data)
{
    int flag = 1;
    assert(q);

    pthread_mutex_lock(&(q->mutex));
    AQPopUnlocked(q, data, &flag);
    pthread_mutex_unlock(&(q->mutex));
}

void AQLock(AsyncQueue *q)
{
    pthread_mutex_lock(&(q->mutex));
}

void AQUnlock(AsyncQueue *q)
{
    pthread_mutex_unlock(&(q->mutex));
}

void AQBroadcast(AsyncQueue *q)
{
    assert(q);
    pthread_cond_broadcast(&(q->cond));
}
