/********************************************************************
 ** Copyright(c) 2016,哈尔滨工程大学信息安全研究中心
 ** All rights reserved
 **
 ** 文件名：AC.h
 ** 创建人：路泽亚
 ** 描  述：ac自动机的实现
 ** 注  意：1.如果更改字符集个数
 **          需要在匹配时(AC_Search)，添加时(AC_Build)进行修改
 **
 ** 当前版本： v1.0
 ** 作    者：路泽亚
 ** 完成日期： 2016-07-20
 ********************************************************************/
#ifndef AC_H
#define AC_H

/* 0-255 */
#define AC_MAX_CHAR (256)

typedef struct AC_WORD {
    char *word;
    int   size;
	void  *info;
} AC_WORD;

typedef struct AC {
    int      N;                    /* 单词缓冲的长度 */
    AC_WORD *words;
    int      count;                /* 单词个数 */
    int      total;                /* 所有单词总长度，也是trie树分配节点个数 */
    /* 这里不能定义为**,因为后来使用trie时 trie[][]会当做两次求[],而不是二维数组 */
    int      (*trie)[AC_MAX_CHAR + 1]; /* trie树指针(此处使用数组表示),
                                          用+1表示叶子节点 */
} AC;

typedef struct AC_STREAM {
    int     k;                  /* 保存当前节点 */
} AC_STREAM;

/* TODO zl add @param index */
int  AC_AddWord (AC *ac, char *word, int len, void *info, size_t info_len);
int  AC_Build   (AC *ac);
int  AC_Search  (AC *ac, AC_STREAM  *stream, char *str, int len, AC_WORD *word);
void AC_Free    (AC *ac);

#endif /* AC_H */
