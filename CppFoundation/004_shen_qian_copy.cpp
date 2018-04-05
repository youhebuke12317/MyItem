/*************************************************************************
    > File Name: shen_qian_copy.cpp
    > Author: reus
    > Mail: dmarcoreus@gmail.com 
    > Created Time: 日  1/ 7 09:08:04 2018
 ************************************************************************/

#include <iostream>
#include <string.h>

using namespace std;

/*
 * 浅拷贝与深拷贝
 *		默认构造函数实现浅拷贝
 *		等号操作实现浅拷贝
 * */

class Name {
	public:
		Name(const char *myp)
		{
			int len = strlen(myp);
			p = (char *)malloc(len + 1);
			strcpy(p ,myp);
		}

		// Name obj2 = obj1;
		// 解决方案: 手工编写拷贝构造函数
		Name(const Name &obj)
		{
			int len = obj.len;
			p = (char *)malloc(len + 1);
			strcpy(p, obj.p);
		}

		~Name()
		{
			if (p) {
				free(p);
				p = NULL;
			}
			len = 0;
		}
	private:
		char *p;
		int len;

	protected:
};

// 如果没有手工的编写拷贝构造函数，对象析构的时候，会出现段错误
void objplaymain()
{
	Name obj1("abcde");

	Name obj2 = obj1;	// 默认拷贝构造函数(浅拷贝)

	Name obj3("obj3");

	// 解决方案：需要实现等号操作符重载
	//obj3 = obj1;	// 等号操作(浅拷贝)	// 见012_*.cpp

	return ;
}

int main()
{
	objplaymain();

	return 0;
}
