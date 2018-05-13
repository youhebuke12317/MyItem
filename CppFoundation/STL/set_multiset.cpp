/*************************************************************************
    > File Name: set_muliset.cpp
    > Author: zhengli
    > Mail: zldata@aliyun.com 
    > Created Time: 四  4/ 5 17:28:47 2018
    > Brief: 
 ************************************************************************/

#include <iostream>
using namespace std;
#include <set>

/*
 * set 集合 元素唯一  自动排序 不能按照[]方式插入数据
 *		内部实现是红黑树形式
 * set 集合 元素可以不唯一  自动排序 不能按照[]方式插入数据
 *		内部实现是红黑树形式
 *		当需要修改时需先删除在添加
 *
 * set<int>					set1;		// 默认是从小到大排序
 * set<int, less<int>>		set2;
 * set<int, greater<int>>	set3;		// 从大到小排序
 *
 * 对于复杂的数据类型 该怎么排序（比较）？？？
 *	
 *
 * set1.insert(tmp);		
 *
 * set<int>::iterator it1 = set1.brgin();
 * set<int>::iterator it2 = set1.end();
 *
 * set1.empty();			// 判空
 *
 *
 *
 * 对自定义函数的比较：--- 仿函数 函数对象
 * // 仿函数
 * struct FunStudent
 * {
 *		bool operator()(const Student &left, const Student &rigth) 
 *		{
 *			if (left.age < rigth.age) { // 如果左边的小 就返回真 从小到大按年龄
 *				return true;
 *			} else {
 *				return false;
 *		}
 * }
 *
 * set<Student, FunStudent>		set1;
 * Student	s1("s1", 31);
 * Student	s2("s2", 32);
 *
 * set1.insert(s1);
 * set1.insert(s2);
 * // 这时候会根据年龄从小到大排序 
 * // 当出现年龄相同时  只出现一个
 * 
 *
 *
 * 因此判断返回值很重要 返回值（对组）pair<iterator, bool>
 * pair<set<Student, FunStudent>::iterator, bool>	pair1 = set1.insert(s1);
 * if (pair1.second == true) {
 *		cout << "插入成功" << endl; 
 * } else {
 *		cout << "插入失败" << endl;
 * }
 *
 *		
 *	set 的查找
 *	set.find(elem);			查找元素是elem的迭代器
 *	set.count(elem);		查找元素为elem的个数
 *	set.lower_bound(elem);	查找大于等于5的元素的迭代器位置
 *	set.upper_bound(elem);	查找大于    5的元素的迭代器位置
 *
 *	set.equal_range(elem);	查找 ...
 *			返回对组pair<iterator, iterator>
 *			pair<set<int>::iterator, set<int>::iterator>	mypair;
 *			mypair = set.equal_range(5);
 *			mypair.first
 *			mypair.second
 *
 *
 *
 * */
