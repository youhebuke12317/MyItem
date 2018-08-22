/*************************************************************************
    > File Name: test.c
    > Author: zhengli
    > Mail: zldata@aliyun.com 
    > Created Time: 三  7/18 21:51:03 2018
    > Brief: 
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <pthread.h>
#include <errno.h>
#include <threadpool_self.h>

#define MAX_THREAD_NUM		10000
#define MAX_TASK_NUM		MAX_THREAD_NUM

void *process(void *arg)
{
	printf("线程 0x%x 正在处理任务%d......\n", (unsigned int)pthread_self(), *(int *)arg);
//	usleep(20);
	printf("线程 0x%x 任务处理完成\n", (unsigned int)pthread_self());
	return NULL;
}

int main(void)
{
	threadpool_conf_t conf;
	conf.min_thr_num = 10;
	conf.max_thr_num = MAX_THREAD_NUM;
	conf.queue_max_size = MAX_TASK_NUM;
	threadpool_t *thp = threadpool_create(conf);  
	printf("pool inited\n");

	int  *num = (int *)malloc(sizeof(int) * MAX_TASK_NUM);
	int i;
	for(i = 0; i < MAX_TASK_NUM - 2; i++) {
		num[i] = i;
		threadpool_add(thp, process, (void *)&num[i]);
		printf("add task %d\n", i);
	}
	
	//睡眠5秒后再加入任务
	sleep(2);
	num[i] = i;
	threadpool_add(thp, process, (void *)&num[i]);

	sleep(1);
	threadpool_destroy(thp);
	return 0;
}

