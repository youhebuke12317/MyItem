/*************************************************************************
    > File Name: deque.cpp
    > Author: zhengli
    > Mail: zldata@aliyun.com 
    > Created Time: 四  4/ 5 11:07:50 2018
    > Brief: 
 ************************************************************************/

#include <iostream>
using namespace std;
#include <deque>
#include <algorithm>

void ptintD(deque<int> d)
{
	for (deque<int>::iterator it = d.begin(); 
			it != d.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
}

void main41()
{
	deque<int> d1;

	d1.push_back(1);
	d1.push_back(3);
	d1.push_back(5);

	d1.push_front(-11);
	d1.push_front(-33);
	d1.push_front(-55);

	ptintD(d1);

	d1.pop_back();
	d1.pop_front();

	ptintD(d1);

	// 查找 -33 在数组下标的值
	deque<int>::iterator it = find(d1.begin(), 
			d1.end(), -33);

	if (it != d1.end()) {
		cout << "-33数组下标是" << 
			distance(d1.begin(), it) << endl;
	} else {
		cout << "没有找到-33的元素" << endl;
	}
}

int main()
{
	main41(); 
	return 0;
}

