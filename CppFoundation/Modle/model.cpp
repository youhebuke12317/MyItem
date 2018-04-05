/*************************************************************************
    > File Name: a.cpp
    > Author: reus
    > Mail: dmarcoreus@gmail.com 
    > Created Time: 日  3/18 17:57:18 2018
    > Brief: 
 ************************************************************************/

#include <iostream>
using namespace std;

template <typename	T >
int add (T &a, T &b)
{
	T c;
	c = a;
	a = b;
	b = c;
	cout << "hello ... template" << endl;

	return 0;
}

int main()
{
	{
		int a = 10;
		int b = 20;
		cout << "a = " << a << ", b = " << b << endl;
		add(a, b);
		cout << "a = " << a << ", b = " << b << endl;
	}

	{
		char a = 'a';
		char b = 'b';
		cout << "a = " << a << ", b = " << b << endl;
		add(a, b);
		cout << "a = " << a << ", b = " << b << endl;
	}

	return 0;
}
