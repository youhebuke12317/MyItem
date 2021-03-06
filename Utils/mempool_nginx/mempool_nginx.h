/*************************************************************************
    > File Name: mempool_nginx.h
    > Author: zhengli
    > Mail: zldata@aliyun.com 
    > Created Time: 二  9/18 08:25:42 2018
    > Brief: 
 ************************************************************************/

#ifndef __MEMPOOL_NGINX_H__
#define __MEMPOOL_NGINX_H__

typedef struct mem_pool_s           mem_pool_t;
typedef struct mem_chain_s          mem_chain_t;
typedef struct mem_pool_large_s     mem_pool_large_t;  
typedef struct mem_pool_cleanup_s   mem_pool_cleanup_t;  

#define MEM_POOL_ALIGNMENT      16

#define mem_printf			    printf
#define mem_free(p)				free(p)
#define mem_realloc(p, n)		realloc(p, n)
#define mem_calloc(count, n)	calloc(count, n)
#define mem_memset(buf, c, n)	(void) memset(buf, c, n)
#define mem_memzero(buf, n)		(void) memset(buf, 0, n)

#define MEM_PAGESIZE             getpagesize()
#define MEM_MAX_ALLOC_FROM_POOL  (MEM_PAGESIZE - 1)

typedef void (*mem_pool_cleanup_pt)(void *data);    /* cleanup的callback类型 */

struct mem_pool_cleanup_s{  
	mem_pool_cleanup_pt handler;    
	void    *data;                      /* 指向要清除的数据 */
	mem_pool_cleanup_t *next;           /* 下一个cleanup callback */  
};  

struct mem_pool_large_s{  
	mem_pool_large_t  *next;            /* 指向下一块大块内存 */
	void    *alloc;                     /* 指向分配的大块内存 */  
}; 

typedef struct {
	unsigned char        *last;         /* 当前内存分配的结束位置，即下一段可分配内存的起始位置 */
	unsigned char        *end;          /* 内存池的结束位置 */
	mem_pool_t           *next;         /* 指向下一个内存池 */
	unsigned int         failed;        /* 记录内存池内存分配失败的次数 */
} mem_pool_data_t;  

struct mem_pool_s {
	mem_pool_data_t       d;            /* 内存池的数据块 */
	size_t                max;          /* 内存池数据块的最大值 */
	mem_pool_t           *current;      /* 指向当前内存池 */
	mem_pool_large_t     *large;        /* 大块内存链表，即分配空间超过 max 的内存 */
	mem_pool_cleanup_t   *cleanup;      /* 析构函数，释放内存池 */
	void                 *log;          /* 内存分配相关的日志信息 */
};

mem_pool_t * mem_create_pool(size_t size, void *log);
void mem_destroy_pool(mem_pool_t *pool);
void mem_reset_pool(mem_pool_t *pool);
void * mem_palloc(mem_pool_t *pool, size_t size);
void * mem_pcalloc(mem_pool_t *pool, size_t size);
int mem_free_large(mem_pool_t *pool, void *p);
mem_pool_cleanup_t * mem_pool_cleanup_add(mem_pool_t *p, size_t size);

#endif

