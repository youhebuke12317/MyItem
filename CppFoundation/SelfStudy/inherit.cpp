/*************************************************************************
    > File Name: inherit.cpp
    > Author: zhengli
    > Mail: zldata@aliyun.com 
    > Created Time: 六  4/21 20:32:08 2018
    > Brief: 
 ************************************************************************/

#include <iostream>
using namespace std;


//子类对象如何初始化父类成员
//继承中的构造和析构
//继承和组合混搭情况下，构造函数、析构函数调用顺序研究

class Object
{
public:
	Object(const char* s) {
		cout<<"Object()"<<" "<<s<<endl;
	}

	~Object() {
		cout<<"~Object()"<<endl;
	}
};

class Parent : public Object
{
public:
	Parent(const char* s) : Object(s) {
		cout<<"Parent()"<<" "<<s<<endl;
	}

	~Parent() {
		cout<<"~Parent()"<<endl;
	}
};

class Child : public Parent
{
protected:
	Object o1;
	Object o2;
public:
	Child() : o2("o2"), o1("o1"), Parent("Parameter from Child!") {
		cout<<"Child()"<<endl;
	}

	~Child() {
		cout<<"~Child()"<<endl;
	}
};

void run05()
{
	Child child;
}

int main(int argc, char *argv[])
{
	cout<<"demo05_extend_construct_destory.cpp"<<endl;

	run05();

	return 0;
}

