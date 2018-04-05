/*************************************************************************
    > File Name: TestArray.cpp
    > Author: reus
    > Mail: dmarcoreus@gmail.com 
    > Created Time: 日  1/14 10:46:18 2018
 ************************************************************************/

#include <iostream>
using namespace std;

#include "Array.h"

int main()
{
	Array a1(10);

	for (int i = 0; i < a1.length(); i++) {
		//a1.setData(i, i);
		a1[i] = i;
	}

	cout << "======= array for a2 info =======" << endl;
	for (int i = 0; i < a1.length(); i++) {
		cout << a1.getData(i) << " ";
		// cout << a1[i] << " ";
	}
	cout << endl;

	Array a2 = a1;
	cout << "======= array for a2 info =======" << endl;
	for (int i = 0; i < a2.length(); i++) {
		cout << a2.getData(i) << " ";
	}
	cout << endl;

	return 0;
}
