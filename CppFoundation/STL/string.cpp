/**
* @file			string.cpp
* @brief		Sample project head file
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年04月03日 星期二 19时28分29秒
*/

#include <iostream>
using namespace std;

#include "string"

// sting类的初始化
void main21()
{
	string s1 = "1111";
	string s2("2222");
	string s3 = s2;
	string s4(10, '4');

	cout << "s1: " << s1 << endl;
	cout << "s2: " << s2 << endl;
	cout << "s3: " << s3 << endl;
	cout << "s4: " << s4 << endl;
}

// sting的遍历
void main22()
{
	string s1 = "abcdefg";

	// 数组方式
	for (int i = 0; i < s1.length(); i++) {
		cout << s1[i] << " ";
	}
	cout << endl;

	// 迭代器方式
	for (string::iterator it = s1.begin(); it != s1.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;


	// at() 可以抛出异常
	try {
		for (int j = 0; j < s1.length() + 3; j++) {
			cout << s1.at(j) << " ";		// 抛出异常
		}
		cout << endl;
	}
	catch ( ... ) {
		cout << "\n发生异常" << endl;
	}
}

// 字符指针和string指针
void main23()
{
	string s1 = "111";

	// s1 ====> char *
	cout << s1.c_str() << endl;

	// char * =====> string
	
	// s1内容 copy buf中
	char buf1[128];
	s1.copy(buf1, 3, 0);	// 只给拷贝3个字符 不加'/0'
	cout << "buf1: " << buf1 << endl;
}

// 字符串的连接
void main24()
{
	string s1 = "111";
	string s2 = "222";
	s1 = s1 + s2;
	cout << "s1: " << s1 << endl;

	string s3 = "333";
	string s4 = "444";
	s3.append(s4);
	cout << "s3: " << s3 << endl;
}

// 字符串的查找和替换
void main25()
{
	string s1 = "wbm hello wbm 111 wbm 222 wbm 333";

	int index = s1.find("wbm", 0);
	cout << "index = " << index << endl;
}



int main()
{
	// main21();
	// main22();
	// main23();
	// main24();
	main25();
	return 0;	
}
