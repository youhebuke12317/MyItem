/*************************************************************************
    > File Name: priority_queue.cpp
    > Author: zhengli
    > Mail: zldata@aliyun.com 
    > Created Time: 四  4/ 5 17:06:15 2018
    > Brief: 优先级队列 最大优先级队列  最小优先级队列
 ************************************************************************/

#include <iostream>
using namespace std;
#include <queue>
	
/*
 * priority_queue<int>	p1;		// 默认是最大优先级队列
 * priority_queue< int, vector<int>, less<int> >	p2;	 //提前定义好预定义函数 
 * priority_queue< int, vector<int>, greater<int> >	p3;  //最小优先级队列
 * 
 * p1.push(33);			// 入队
 * p1.push(11);
 * p1.push(55);
 * p1.push(22);
 *
 * p1.top();			// 获取对头元素
 * p1.pop();			// 出队
 * p1.size();			// 获取队列大小
 * */



