/*************************************************************************
    > File Name: stack.cpp
    > Author: zhengli
    > Mail: zldata@aliyun.com 
    > Created Time: 四  4/ 5 11:28:55 2018
    > Brief: 
 ************************************************************************/

#include <iostream>
using namespace std;
#include <stack>


void main51()
{
	stack<int>	s;

	// 入栈
	for (size_t i = 0; i < 10; i++) {
			s.push(i+1);
	}
	cout << "栈大小 = " << s.size() << endl;

	// 出栈
	while (!s.empty()) {
		int tmp = s.top();		// 获取栈顶元素
		cout << tmp << " ";
		s.pop();  // 弹出栈顶元素
	}
	cout << endl;


}

int main()
{
	main51();
	return 0;
}
