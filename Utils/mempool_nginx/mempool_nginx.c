/*************************************************************************
    > File Name: mempool_nginx.c
    > Author: zhengli
    > Mail: zldata@aliyun.com 
    > Created Time: 二  9/18 08:25:21 2018
    > Brief: 内存池 - 基于nginx内存池实现, 去除内存对齐与相关结构,
			保留内存池完整结构
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include "mempool_nginx.h"


static void * mem_palloc_block(mem_pool_t *pool, size_t size);
static void * mem_palloc_large(mem_pool_t *pool, size_t size);
static inline void *mem_palloc_small(mem_pool_t *pool, size_t size);

void * mem_malloc(size_t size, void *log) {
    void  *p; 
	p = malloc(size);
    if (p == NULL) {
        mem_printf("malloc(%luz) failed\n", (unsigned long)size);
    }   
    return p;
}



/**
 * @brief 创建一个内存池
 *
 * @param size	动态申请内存大小，单位字节
 * @param log	日志结构, 暂时未定义
 *
 * @return	成功返回申请内存首地址, 失败返回NULL
 */
mem_pool_t *mem_create_pool(size_t size, void *log) {

    mem_pool_t  *p;

    p = mem_malloc(size, log);
    if (p == NULL) return NULL;

    p->d.last = (unsigned char *) p + sizeof(mem_pool_t);
    p->d.end = (unsigned char *) p + size;
    p->d.next = NULL;
    p->d.failed = 0;

    size = size - sizeof(mem_pool_t);
    p->max = (size < MEM_MAX_ALLOC_FROM_POOL) ? size : MEM_MAX_ALLOC_FROM_POOL;

    p->current = p; 
    p->large = NULL;
    p->cleanup = NULL;
    p->log = log;

    return p;
}

/**
 * @brief 销毁内存池
 *
 * @param pool 内存池结构, mem_create_pool有效返回值
 */
void mem_destroy_pool(mem_pool_t *pool) {
	mem_pool_t			*p, *n;
	mem_pool_large_t	*l;
	mem_pool_cleanup_t	*c;

	for (c = pool->cleanup; c; c = c->next) {
		if (c->handler) {
			mem_printf("run cleanup: %p\n", c);
			c->handler(c->data);
		}
	}

	for (l = pool->large; l; l = l->next) {
		if (l->alloc) {
			mem_free(l->alloc);
		}
	}

	for (p = pool, n = pool->d.next; /* void */; p = n, n = n->d.next) {
		mem_free(p);

		if (n == NULL) {
			break;
		}
	}
}

/**
 * @brief 重置内存池
 *
 * @param pool 内存池结构, mem_create_pool有效返回值
 */
void mem_reset_pool(mem_pool_t *pool) {
	mem_pool_t			*p;
	mem_pool_large_t	*l;

	for (l = pool->large; l; l = l->next) {
		if (l->alloc) {
			mem_free(l->alloc);
		}
	}

	for (p = pool; p; p = p->d.next) {
		p->d.last = (unsigned char *) p + sizeof(mem_pool_t);
		p->d.failed = 0;
	}

	pool->current = pool;
	pool->large = NULL;
}

void * mem_palloc(mem_pool_t *pool, size_t size) {
	if (size <= pool->max) {
		mem_printf("entry mem_palloc_small function\n");
		return mem_palloc_small(pool, size);
	}
	mem_printf("entry mem_palloc_large function\n");
	return mem_palloc_large(pool, size);
}

void *mem_pcalloc(mem_pool_t *pool, size_t size) {
	void *p;

	p = mem_palloc(pool, size);
	if (p) {
		mem_memzero(p, size);
	}
	return p;
}

/**
 * @brief 申请小内存, 不够用则新创建内存链节点
 *
 * @param pool	内存池结构, mem_create_pool有效返回值
 * @param size  申请内存大小
 *
 * @return 成功返回申请内存首地址, 失败返回NULL
 */
static inline void *
mem_palloc_small(mem_pool_t *pool, size_t size) {
	unsigned char	*m;
	mem_pool_t		*p;

	p = pool-> current;

	do {
		m = p->d.last;
		
		if ((size_t) (p->d.end - m) >= size) {
			p->d.last = m + size;
			return m;
		}
		
		p = p->d.next;

	} while (p);

	return mem_palloc_block(pool, size);
}


/**
 * @brief	当申请内存为小内存并且现有内存池不够分配, 则创建新的内存池节点
 *
 * @param pool	内存池结构, mem_create_pool有效返回值
 * @param size	申请内存大小
 *
 * @return	成功返回申请内存首地址, 失败返回NULL
 */
static void * mem_palloc_block(mem_pool_t *pool, size_t size) {
	unsigned char	*m;
	size_t			psize;
	mem_pool_t		*p, *new;

	mem_printf("entry mem_palloc_block function\n");

	psize = (size_t) (pool->d.end - (unsigned char *) pool);

	m = mem_malloc(psize, pool->log);
	if (m == NULL)	return NULL;

	new = (mem_pool_t *) m;

	new->d.end = m + psize;
	new->d.next = NULL;
	new->d.failed = 0;

	m += sizeof(mem_pool_data_t);
	new->d.last = m + size;
	
	for (p = pool->current; p->d.next; p = p->d.next) {
		/* 更新current指针: 失败4次以上移动current指针 */
		if (p->d.failed++ > 4) {
			pool->current = p->d.next;
		}
	}

	p->d.next = new;

	return m;
}


/**
 * @brief 申请大内存
 *
 * @param pool 内存池结构, mem_create_pool有效返回值
 * @param size 申请内存大小
 *
 * @return	成功返回申请内存首地址, 失败返回NULL
 */
static void *
mem_palloc_large(mem_pool_t *pool, size_t size) {
	void				*p;
	unsigned int		n;
	mem_pool_large_t	*large;

	p = mem_malloc(size, pool->log);
	if (p == NULL) return NULL;

	n = 0;

	/* 若在该pool之前已经分配了large字段 */
	for (large = pool->large; large; large = large->next) {
		if (large->alloc == NULL) {
			large->alloc = p;
			return p;
		}

		// 只找前三个大的内存节点
		if (n++ > 3) break;
	}

	/* 若在该pool之前并未分配large字段: large内存也从内存池中拿 */
	large = mem_palloc_small(pool, sizeof(mem_pool_large_t));
	if (large == NULL) {
		mem_free(p);
		return NULL;
	}

	large->alloc = p;
	large->next = pool->large;
	pool->large = large;
	
	return p;
}

/**
 * @brief 释放大内存中某块内存
 *
 * @param pool	内存池结构, mem_create_pool有效返回值
 * @param p		需要释放的内存首地址
 *
 * @return 成功返回0，失败返回-1
 */
int mem_free_large(mem_pool_t *pool, void *p) {
	mem_pool_large_t	*l;

	for (l = pool->large; l; l = l->next) {
		if (p == l->alloc) {
			mem_printf("free: %p\n", l->alloc);
			mem_free(l->alloc);
			l->alloc = NULL;
			return 0;
		}
	}

	return -1;
}

/**
 * @brief 
 *
 * @param p
 * @param size
 *
 * @return 
 */
mem_pool_cleanup_t *
mem_pool_cleanup_add(mem_pool_t *p, size_t size) {

	mem_pool_cleanup_t	*c;

	c = mem_palloc(p, sizeof(mem_pool_cleanup_t));
	if (c == NULL) return NULL;

	if (size) {
		c->data = mem_palloc(p, size);
		if (c->data == NULL) return NULL;
	}
	else {
		c->data = NULL;
	}

	c->handler = NULL;
	c->next = p->cleanup;
	p->cleanup = c;

	return c;
}
