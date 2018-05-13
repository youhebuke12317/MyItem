/**
* @file			a.c
* @brief		Sample project head file
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年04月09日 星期一 22时26分56秒
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
	char a[32] = "aabbcc";
	char *b = "aabbcc";

	printf("%s\n", a);
	printf("%s\n", &a);
	printf("%s\n", b);
	printf("%p\n", &b);

	return 0;
}
