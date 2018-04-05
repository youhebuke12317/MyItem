/*************************************************************************
    > File Name: 014_kuohao_operator.cpp
    > Author: reus
    > Mail: dmarcoreus@gmail.com 
    > Created Time: 三  2/28 22:30:49 2018
    > Brief: 
 ************************************************************************/

#include <iostream>
using namespace std;

class F
{
	public:
		int operator() (int a, int b)
		{
			return (a * a + b * b);
		}
	private:
};

class F2
{
	public:
		int MemFunc(int a, int b)
		{
			return (a * a + b * b);
		}
	private:
};

int main()
{
	F f;
	f(2, 4);

	F2 f2;
	f2.MemFunc(2, 4);

	return 0;
}
