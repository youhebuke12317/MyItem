/*************************************************************************
    > File Name: namespace.cpp
    > Author: zhengli
    > Mail: zldata@aliyun.com 
    > Created Time: 六  4/14 21:06:04 2018
    > Brief: 
 ************************************************************************/

#include <iostream>
using namespace std;

namespace NameSpaceA
{
	int a = 0;
}

namespace NameSpaceB
{
	int a = 1;

	namespace NameSpaceC
	{
		struct Teacher
		{
			char name[10];
			int age;
		};
	}
}

int main()
{
	using namespace NameSpaceA;
	using NameSpaceB::NameSpaceC::Teacher;

	printf("a = %d\n", a);
	printf("a = %d\n", NameSpaceB::a);

    NameSpaceB::NameSpaceC::Teacher t2;
	Teacher t1 = {"aaa", 3};

	printf("t1.name = %s\n", t1.name);
	printf("t1.age = %d\n", t1.age);

	system("pause");
	return 0;
}
