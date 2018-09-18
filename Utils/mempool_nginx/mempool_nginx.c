/*************************************************************************
    > File Name: mempool_nginx.c
    > Author: zhengli
    > Mail: zldata@aliyun.com 
    > Created Time: 二  9/18 08:25:21 2018
    > Brief: 内存池 - 基于nginx内存池实现
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "mempool_nginx.h"

#define MEM_PAGESIZE             getpagesize()
#define MEM_POOL_ALIGNMENT       16
#define NGX_MAX_ALLOC_FROM_POOL  (MEM_PAGESIZE - 1)

inline void *mem_memalign(size_t alignment, size_t size, void *log) {
    void  *p; 

    p = memalign(alignment, size);
    if (p == NULL) {
        printf("memalign(%uz, %uz) failed", alignment, size);
    }   

    return p;
}

mem_pool_t *mem_create_pool(size_t size, void *log) {

    mem_pool_t  *p; /* 执行内存池头部 */

    /* 分配大小为 size 的内存 */
    p = mem_memalign(MEM_POOL_ALIGNMENT, size, log);
    if (p == NULL) return NULL;

    /* 以下是初始化 mem_pool_t 结构信息 */
    p->d.last = (u_char *) p + sizeof(mem_pool_t);
    p->d.end = (u_char *) p + size;
    p->d.next = NULL;
    p->d.failed = 0;

    size = size - sizeof(mem_pool_t);   /* 可供分配的空间大小 */
    /* 不能超过最大的限定值 4096B */
    p->max = (size < NGX_MAX_ALLOC_FROM_POOL) ? size : NGX_MAX_ALLOC_FROM_POOL;

    p->current = p; /* 指向当前的内存池 */
    p->large = NULL;
    p->cleanup = NULL;
    p->log = log;

    return p;
}
