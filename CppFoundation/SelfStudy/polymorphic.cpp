/*************************************************************************
    > File Name: polymorphic.cpp
    > Author: zhengli
    > Mail: zldata@aliyun.com 
    > Created Time: 日  4/22 12:13:29 2018
    > Brief: 
 ************************************************************************/

#include <iostream>
using namespace std;

class Parent
{
public:
	void print() {
		cout<<"Parent:print() do..."<<endl;
	}
};

class Child : public Parent
{
public:
	 void print() {
		cout<<"Child:print() do..."<<endl;
	}
};

int main()
{
	
	Child child;
	Parent *p = NULL;
	p = &child;
	
	child.print();
	
	child.Parent::print();

	return 0;
}

