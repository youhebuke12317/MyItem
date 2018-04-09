/*************************************************************************
    > File Name: list.cpp
    > Author: zhengli
    > Mail: zldata@aliyun.com 
    > Created Time: 四  4/ 5 14:37:17 2018
    > Brief: 
 ************************************************************************/

#include <iostream>
using namespace std;
#include <list>

/*
 * 双向链表容器
 * list<typename>	l;
 *
 * l.push_back(typename element)	尾插法
 *
 * l.size()				链表元素个数
 *
 * list<typename>::iterator	it = l.begin();		迭代器 开始
 * list<typename>::iterator	it = l.end();		迭代器 尾部
 *
 * list不能随机访问
 * it = l.begin();
 * it ++;
 * it ++;
 * // it = it + 5		// 错误
 *
 *
 * l.insert(it, 100);		链表插入将100插入到it指向位置前  
 *
 * list<typename>::iterator	it1 = l.begin();		迭代器 开始
 * list<typename>::iterator	it2 = l.begin();		迭代器 开始
 * it2++;
 * it2++;
 * l.erase(it1, it2)	左闭右开的删除
 * l.remove(100);		删除元素为100的元素节点
 * */
