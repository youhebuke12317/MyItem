#include <stdio.h>
#include <pthread.h>
#include <threadpool_nginx.h>

void testfun(void *argv)
{
	int *num = (int*)argv;
	printf("testfun threadid = %u  num = %d\n",pthread_self(),*num);
	//sleep(3);
	return ;
}

int main()
{
	int	i = 0;
	int	array[10000] = {0};
	tp_conf_t	conf = {5, 0, 5};

	tp_threadpool_t *pool = threadpool_init(&conf);	//初始化线程池
	if (pool == NULL) {
		return 0;
	}


	for (; i < 10000; i++){
		array[i] = i;
		if (i == 80){
			threadpool_add_thread(pool); //增加线程
			threadpool_add_thread(pool); //增加线程
		}
		
		if (i == 100){
			threadpool_set_max_tasknum(pool, 0); //改变最大任务数   0为不做上限
		}

		while(1){
			if (threadpool_add_task(pool, testfun, &array[i]) == 0){
				break;
			}
			printf("error in i = %d\n",i);
		
		}
	}
	threadpool_destroy(pool);

	while(1){
		sleep(5);
	}
	return 0;
}
