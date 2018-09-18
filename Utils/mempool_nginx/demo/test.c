/*************************************************************************
    > File Name: test.c
    > Author: zhengli
    > Mail: zldata@aliyun.com 
    > Created Time: 二  9/18 16:10:37 2018
    > Brief: 
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "../mempool_nginx.h"

int main() {
	mem_pool_t *pool;
	pool = mem_create_pool(1024, NULL);
	if (pool == NULL) {
		mem_printf("mem_create_pool error\n");
		return -1;
	}

	char *p1 = (char *)mem_palloc(pool, 1024);
	if (p1 == NULL) {
		mem_printf("mem_palloc error\n");
		return -1;
	}

	char *p2 = (char *)mem_palloc(pool, 128);
	if (p2 == NULL) {
		mem_printf("mem_palloc error\n");
		return -1;
	}

	mem_destroy_pool(pool);

	return 0;
}
