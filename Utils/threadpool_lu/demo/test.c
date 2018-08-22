/*************************************************************************
    > File Name: test.c
    > Author: zhengli
    > Mail: zldata@aliyun.com 
    > Note:  
    > Created Time: 2018年07月20日 星期五 03时35分43秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <FixedThreadPool.h>

void work(void *useless)
{
    (void)useless;

    printf("thread %lu aaaa.\n", pthread_self());
}

int main(void)
{
    int i = 0;
    FixedThreadPool *pool = FTPoolNew(1000);

    for (i = 0; i < 10; i++) {
        FTPoolPush(pool, work, NULL);
    }

    sleep(1);
    FTPoolDestroy(pool);
    return 0;
}
