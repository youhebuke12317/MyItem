/********************************************************************
 ** Copyright(c) 2016,哈尔滨工程大学信息安全研究中心
 ** All rights reserved
 **
 ** 文件名：AC.c
 ** 创建人：路泽亚
 ** 描  述：ac自动机的实现(trie树+状态转移)
 **        此处不显式构造失败指针，或者说失败指针只在构造时出现，并在此处转换为状态转移数组了
 **        匹配时直接匹配，失败时走状态转移
 **        构造状态转移的过程:
 **        1.入队时，构造子节点失败指针
 **        2.出队时，(构建当前节点的)根据失败指针构建状态转移数组next
 **
 **        构造失败指针的过程：(dfa是字符为边)
 **        1.第一层节点的失败指针为根节点
 **        2.之后节点需要判断其父节点的失败指针指向的节点的next数组中对应当前字符项是否为空
 **          为空 指向root
 **          不为空 指向父节点的失败指针指向的节点的next数组中当前字符项指向的值
 **
 ** 注  意：1.如果更改字符集个数
 **          需要在匹配时(AC_Search)，添加时(AC_Build)进行修改
 **
 **	
 ** 以往版本： v1.0  // luzheya AC自动机实现
 ** 当前版本： v1.1  // TODO zl add 为基于sni查找证书做匹配
 ** 作    者：路泽亚
 ** 完成日期： 2016-07-20
 ********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "AC.h"
#include "SList.h"

#define MALLOC(size)    (malloc(size))
#define RALLOC(p, size) (realloc((p), (size)))
#define FREE(p)         (free(p))

typedef struct NODE {
    SLIST_LINK item;
    int        v;               /* 当前节点 */
    int        f;               /* 失败指针 */
} NODE;

inline int QUEUE_Enq(SLIST *queue, int v, int f);
inline int QUEUE_Deq(SLIST *queue, int *f);
inline int AC_Build_Fail(AC *ac);

/**
 * AC_AddWord
 * 添加一个单词
 * @param ac
 * @param word 模式单词
 * @param len  模式单词的长度
 * @param info  TODO zl add	附带信息, 便于查找之后信息获取
 * @return 0成功， -1失败
 */
int AC_AddWord(AC *ac, char *word, int len, void *info, size_t info_len)
{
    ac->count++;
    if (ac->count > ac->N) {	/* TODO 暂时干嘛的还不知道 */
        int    i;
        AC_WORD *temp = MALLOC(sizeof(AC_WORD) * ac->count * 2);
        /* 如果内存分配失败不应该继续向下运行 */
        if (!temp) return -1;

        for (i = 0; i < ac->N; i++)
            temp[i] = ac->words[i];

        FREE(ac->words);
        ac->words = temp;
        ac->N     = ac->count * 2;
    }

    /* 保存单词及其长度 */
    ac->words[ac->count - 1].word = MALLOC(sizeof(char) * len);
    if (!ac->words[ac->count - 1].word) return -1;

    memcpy(ac->words[ac->count - 1].word, word, len);
    ac->words[ac->count - 1].size = len;

	/* TODO zl add */
	if (info && info_len > 0) {
		void *ptr = MALLOC(info_len); 
		if (!ptr) 	ac->words[ac->count - 1].info = NULL;	// 当失败时忽略

		memset(ptr, 0, info_len);
		memcpy(ptr, info, info_len);
		ac->words[ac->count - 1].info = ptr;	
	}
	/* END zl add */

    ac->total += len;
    return 0;
}

/**
 * AC_Free
 * 释放空间
 * @param ac
 */
void AC_Free(AC *ac)
{
    int i;
    for (i = 0; i < ac->count; i++)
        FREE(ac->words[i].word);
    FREE(ac->words);
    FREE(ac->trie);
}

/**
 * AC_Build
 * 构造失败指针
 * @param ac
 * @return 0成功，-1失败
 */
int AC_Build(AC *ac)
{
    int i, j;
    int k;     /* cur为当前节点的指针, k为分配trie节点的指针,0作为根节点使用 */
    int total;      /* trie总大小 */

    /* 1.分配空间trie[total][MAX_CHARS]，添加单词 */
    /* 节点是状态，边是字符，外加一个根节点 */
    total = sizeof(int) * (ac->total + 1) * (AC_MAX_CHAR + 1);

    ac->trie = MALLOC(total);
    if (!ac->trie) return -1;
    memset(ac->trie, 0, total);

    /* 添加单词 */
    k = 1;
    for (i = 0; i < ac->count; i++) {
        int cur = 0;
        for (j = 0; j < ac->words[i].size; j++) {
            int c = ac->words[i].word[j];

            /* 当当前输入有值时，不必再次创建节点 */
            if (ac->trie[cur][c] != 0) {
                cur = ac->trie[cur][c];
            } else {
                ac->trie[cur][c] = k;
                cur = k;
                k++;
            }
        }
        ac->trie[cur][AC_MAX_CHAR] = i + 1;
    }
    for (i = 0; i < AC_MAX_CHAR; i++) {
        if (0 == ac->trie[0][i]) continue;
    }
    return AC_Build_Fail(ac);
}

inline
int QUEUE_Enq(SLIST *queue, int v, int f)
{
    NODE *node = MALLOC(sizeof(NODE));
    if (!node) return -1;

    node->v = v;
    node->f = f;
    SLIST_Attach(queue, queue->tail, node);
    return 0;
}

inline
int QUEUE_Deq(SLIST *queue, int *f)
{
    int   temp;
    NODE *node;

    node = SLIST_LOCATION(queue, queue->head);
    SLIST_Pop(queue);

    temp = node->v;
    if (f) *f = node->f;
    FREE(node);
    return temp;
}

inline
int AC_Build_Fail(AC *ac)
{
    SLIST queue;

    SLIST_Init(&queue, 0);

    /* 2.构造失败指针, bfs方式 */
    /**
     * 父节点失败指针指向的节点的next数组中有当前字符
     * 那么子节点失败指针指向父节点失败指针指向的节点，
     * 否则子节点失败指针指向0 (root)
     */
    /* 这里不采取显示的失败指针，直接利用对应的字符指针 */
    /* 1.入队时，构造子节点失败指针 */
    /* 2.出队时，(构建当前节点的)根据失败指针构建状态转移数组next */
    if (-1 == QUEUE_Enq(&queue, 0, 0)) return -1;

    while (queue.len != 0) {
        /* v 当前节点，f 当前节点的失败指针 */
        int   i, j, v, f;

        v = QUEUE_Deq(&queue, &f);

        for (i = 0; i < AC_MAX_CHAR; i++) {
            int fail;
            int curr = ac->trie[v][i];
            if (curr == 0) continue;

            /* 计算子节点的失败指针，并将子节点入队 */
            /* 第一层失败指针为0 */
            if (v == 0)
                fail = 0;
            else if (ac->trie[f][i] != 0)
                fail = ac->trie[f][i];
            else
                fail = 0;
            if (-1 == QUEUE_Enq(&queue, curr, fail)) return -1;
        }
        /* 父节点不填写状态转移 */
        if (v == 0) continue;

        /* 利用失败指针填写状态转移数组 */
        for (j = 0; j < AC_MAX_CHAR; j++) {
            if (ac->trie[f][j] == 0) continue;
            if (0 == ac->trie[v][j]) ac->trie[v][j] = ac->trie[f][j];
        }
    }
    return 0;
}

/**
 * AC_Search
 * 自动机匹配，匹配上一次便返回
 * @param ac
 * @param stream 流状态信息，保存下来可以流式匹配，可以传空（非流式匹配）
 * @param str    要匹配的文本字符串
 * @param len    匹配到的长度
 * @param word   匹配到的单词（该空间有ac管理，不要释放、修改）
 * @return 大于0 匹配到,并返回匹配到字符串的下一个
 *         0    没有匹配到
 */
int AC_Search(AC         *ac,
              AC_STREAM  *stream,
              char       *str,
              int         len,
              AC_WORD    *word)
{
    int i;
    int k = stream == NULL ? 0 : stream->k;

    for (i = 0; i < len; i++) {
        int l;
        unsigned char c = str[i];

        //printf("c: %c, k: %d, next k: %d\n", c, k, ac->trie[k][c]);
        k = ac->trie[k][c];
        l = ac->trie[k][AC_MAX_CHAR];
        if (l != 0) {
            if (word) *word = ac->words[l - 1];
            return i + 1;
        }
    }
    if (stream) stream->k = k;
    return 0;
}

#if 0
int main(void)
{
    AC ac;
    AC_STREAM stream = {0};
    AC_WORD keyword = {0, 0};
    int res;
    int i;

    memset(&ac, 0, sizeof(ac));
    AC_AddWord(&ac, "se3", 3, (void *)"111", 3); /* TODO zl add */ 
    AC_AddWord(&ac, "sh", 2,  (void *)"222", 3); /* TODO zl add */ 
    AC_AddWord(&ac, "he", 2,  (void *)"333", 3); /* TODO zl add */
    AC_Build(&ac);
    char *str = "234se3";
    res = AC_Search(&ac, NULL, str, strlen(str), &keyword);
    printf("res: %d\n", res);
    res = AC_Search(&ac, &stream, "1h456h", 7, &keyword);
    printf("res: %d", res);

    printf("\n");
    for (i = 0; i < keyword.size; i++)
        printf("%c", keyword.word[i]);
	printf("keyword.word[i].info: %s\n", (char *)keyword.info); /* TODO zl add */
    printf("\n");

    res = AC_Search(&ac, /* &stream */ NULL, "e456", 4, &keyword);
    printf("res: %d", res);

    printf("\n");
    for (i = 0; i < keyword.size; i++)
        printf("%c", keyword.word[i]);
	printf("keyword.word[i].info: %s\n", (char *)keyword.info); /* TODO zl add */
    printf("\n");

    AC_Free(&ac);
    return 0;
}
#endif
