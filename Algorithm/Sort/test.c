/**
* @file			test.c
* @brief		Sample project head file
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年05月02日 星期三 20时05分06秒
*/

#include <stdio.h>
#include <stdlib.h>

#include "Common.h"

int main()
{
	int ret;
	int data[] = {40, 20, 30, 10, 50, 70};
	int length = sizeof(data) / sizeof(*data);
	printf("length = %d\n", length);

	ret = Offer_Partition(data, length, 0, 5);

	printf("ret = %d\n", ret);
	
	return 0;
}
