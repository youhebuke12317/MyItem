/*************************************************************************
    > File Name: this.cpp
    > Author: reus
    > Mail: dmarcoreus@gmail.com 
    > Created Time: 三  1/10 00:30:06 2018
 ************************************************************************/

#include <iostream>
using namespace std;

class Test {
	public:
		Test(int a, int b)
		{
			this->a = a;
			this->b = b;
		}

		void printT()
		{
			cout << "a = " << a << endl;
			cout << "b = " << b << endl;
		}

		// 1 const写在什么位置 没有关系
		// 2 const修饰的是谁
		//		const修饰的是形参a 不是
		//		const修饰的是属性this->a, this->b
		//		const修饰的是this指针所指向的内存空间，修饰的this指针
		// void Opvar(int a, int b) //==> void Opvar(Test const *this, int a, int b)
		void Opvar(int a, int b) const //==>void Opvar(const Test const *this, int a, int b)
		 {
			a = 100;
			//this->a = 200;
			//this->b = 200;
			cout << "a: "<< this->a << endl;
			cout << "b: "<< this->a << endl;
		 }

	private:
		int a;
		int b;
};

void objplaymain_01()
{
	Test t1(1, 2);

	t1.printT();

	t1.Opvar(11, 22);

	return ;
}

int main()
{
	objplaymain_01();

	return 0;
}
