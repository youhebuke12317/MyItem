/**
* @file			test.c
* @brief		Sample project head file
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年03月08日 星期四 09时52分51秒
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <proxyd/AcSni.h>
#include <proxyd/SList.h>

struct Test {
	int  id;
	char ip[128];
	char *ptr;
};

int main()
{
    AC ac;
    AC_STREAM stream = {0};
    AC_WORD keyword = {0, 0};
    int res;
    int i = 0;

	struct Test node[3];
	for (i = 0; i < 3; i++) {
		node[i].id = i;
		strcpy(node[i].ip, "192.168.102.2");
	}

    memset(&ac, 0, sizeof(ac));
    AC_AddWord(&ac, "se3", 3, (void *)&node[0], sizeof(struct Test)); /* TODO zl add */ 
    AC_AddWord(&ac, "sh" , 2, (void *)&node[1], sizeof(struct Test)); /* TODO zl add */ 
    AC_AddWord(&ac, "he" , 2, (void *)&node[2], sizeof(struct Test)); /* TODO zl add */
    AC_Build(&ac);


    char *str = "234se3";
    res = AC_Search(&ac, NULL, str, strlen(str), &keyword);
    printf("res: %d\n", res);
    res = AC_Search(&ac, &stream, "1h456h", 7, &keyword);
    printf("res: %d", res);

    printf("\n");
    for (i = 0; i < keyword.size; i++)
        printf("%c", keyword.word[i]);
    printf("\n");
	printf("keyword.word[i].info->id: %s\n", ((struct Test*)keyword.info)->id); /* TODO zl add */

    res = AC_Search(&ac, /* &stream */ NULL, "e456", 4, &keyword);
    printf("res: %d", res);

    printf("\n");
    for (i = 0; i < keyword.size; i++)
        printf("%c", keyword.word[i]);
	//printf("keyword.word[i].info: %s\n", (char *)keyword.info); /* TODO zl add */
    printf("\n");

    AC_Free(&ac);
    return 0;

}

