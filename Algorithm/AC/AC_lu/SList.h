/********************************************************************
 ** Copyright(c) 2016,哈尔滨工程大学信息安全研究中心
 ** All rights reserved
 **
 ** 文件名：SList.h
 ** 创建人：路泽亚
 ** 描  述：单链表
 ** 注  意：
 **
 ** 当前版本： v1.0
 ** 作    者：路泽亚
 ** 完成日期： 2016-07-12
 **
 ** 用　　法:1.队列 SLIST_Pop SLIST_Attach(&list, list.tail, node)
 **         2.堆栈 SLIST_Pop SLIST_Attach(&list, NULL, node)
 **         3.遍历
 **           SLIST_LINK *temp;
 **           for (temp = list.head; temp != NULL; temp = temp->next) {
 **               struct node *n = SLIST_LOCATION(&list, temp);
 **               printf("n: %s\n", n->str);
 **           }
 ********************************************************************/
#ifndef SLIST_H
#define SLIST_H

#ifndef NULL
#define NULL (0)
#endif

/* 计算指定成员在结构体内的偏移, type结构体类型，member成员名称 */
#define SLIST_OFFSET_OF(type, member) ((unsigned long)(&(((type*)0)->member)))

/**
 * SLIST_LOCATION
 * 计算真正的结构体位置(指针)，与SLIST_Location同样用法
 * @param list 传入的list地址
 * @param item SLIST_LINK的地址
 * @return
 */
#define SLIST_LOCATION(list, item) ((void*)((char*)(item) - (list)->seek))

typedef struct SLIST_LINK {
    struct SLIST_LINK *next;
} SLIST_LINK;

typedef struct SLIST {
    unsigned long len;
    unsigned long seek;
    SLIST_LINK   *head;
    SLIST_LINK   *tail;
} SLIST;

inline static
void  SLIST_Init    (SLIST *list, unsigned long seek)
    __attribute__((always_inline));

inline static
void  SLIST_Attach  (SLIST *list, SLIST_LINK *item, void *data)
    __attribute__((always_inline));

inline static
void  SLIST_Pop     (SLIST *list)
    __attribute__((always_inline));

inline static
void *SLIST_Location(SLIST *list, SLIST_LINK *item)
    __attribute__((always_inline));

inline static
void SLIST_Free(SLIST *list, void (*free)(void *p))
    __attribute__((always_inline));

/**
 * SLIST_Init
 * 初始化SLIST结构体
 * @param list
 * @param seek seek是SLIST_LINK在结构体中的偏移，一般填0
 *             或者使用SLIST_OFFSET_OF宏
 */
inline static
void SLIST_Init(SLIST *list, unsigned long seek)
{
    list->len  = 0;
    list->seek = seek;
    list->head = NULL;
    list->tail = NULL;
}

/**
 * SLIST_Attach
 * 将节点挂到指定节点之后（NULL为挂到第一个）
 * @param list 传递的链表
 * @param item 在该节点之后挂接，传入NULL时，挂到第一个元素位置
 * @param node 要挂接的节点
 */
inline static
void SLIST_Attach(SLIST *list, SLIST_LINK *item, void *data)
{
    SLIST_LINK *temp = (SLIST_LINK*)((char*)data + list->seek);

    temp->next = (item == NULL) ? list->head : item->next;

    if (item == NULL) list->head = temp;
    else              item->next = temp;

    /* 维护的tail指针，不需要可以去掉 */
    if (temp->next == NULL) list->tail = temp;

    list->len++;
}

/**
 * SLIST_Pop
 * 从头部弹出，注意应在外层循环判断是否为空
 * @param list
 */
inline static
void  SLIST_Pop(SLIST *list)
{
    /* if (!list->head) return; */

    list->head = list->head->next;

    if (list->head == NULL) list->tail = NULL;

    list->len--;
}

/**
 * SLIST_Location
 * 找到item所属的结构体
 * @param list 传递的链表
 * @param item 要查找的结构体
 * @return 返回item所属结构体的地址
 */
inline static
void *SLIST_Location(SLIST *list, SLIST_LINK *item)
{
    /* if (!list || !item) return NULL; */
    return ((char*)item - list->seek);
}

/**
 * SLIST_Free
 * 统一释放资源，可以自行定制释放方法
 * @param list
 * @param free
 */
inline static
void SLIST_Free(SLIST *list, void (*free)(void *p))
{
    SLIST_LINK *temp, *next;

    if (!list || !free || !list->head) return;

    temp = list->head;
    for (next = temp->next; next != NULL; next = next->next) {
        free(SLIST_Location(list, temp));
        temp = next;
    }
    free(SLIST_Location(list, temp));
}

#endif /* SLIST_H */
