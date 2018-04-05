/*************************************************************************
    > File Name: MyString.cpp
    > Author: reus
    > Mail: dmarcoreus@gmail.com 
    > Created Time: Thu Mar  1 21:04:29 2018
    > Brief: 
 ************************************************************************/

#include <iostream>
using namespace std;

#include "MyString.h"

int main()
{
	MyString s1;
	MyString s2("s2");
#ifndef TEST_COMAND
	//MyString s2_2 = NULL;
#endif
	MyString s3 = s2;
	MyString s4 = "s44444444444";

	s2.Debug();
	s3.Debug();
	s4.Debug();

	// 测试运算符重载= 和 重载[]
	// MyString & operator=(const char *p);
	// MyString & operator=(const MyString &obj);
	s4 = s2;
	s4.Debug();

	s4 = "s222222";
	s4.Debug();
	
	// char & operator[](int index);
	s4[0] = 'A';
	s4.Debug();

	// 重载左移操作符
	// ostream & operator<<(ostream &out, MyString &obj);
	cout << "重载左移操作符后: s4 = " << s4 << endl;

	// 重载 == 
	// bool operator==(const char *p);
	// bool operator==(const MyString &obj);
	if (s2 == "s22222") {
		cout << "相等!" << endl;
	} else {
		cout << "不相等!" << endl;
	}

	if (s2 == s3) {
		cout << "相等!" << endl;
	} else {
		cout << "不相等!" << endl;
	}
	
	if (s2 != "s22222") {
		cout << "不相等!" << endl;
	} else {
		cout << "相等!" << endl;
	}

	// 重载 !=
	// bool operator!=(const char *p);
	// bool operator!=(const MyString &obj);
	if (s2 != s3) {
		cout << "不相等!" << endl;
	} else {
		cout << "相等!" << endl;
	}

	MyString s5 = "aaaa";
	MyString s6 = "ccccccc";
	// 重载 < >
	// bool operator<(const char *p);
	// bool operator<(const MyString &obj);
	if (s5 < "bbbbbb") {
		cout << "s5 < \"bbbbbb\"" << endl;	
	} else {
		cout << "s5 > \"bbbbbb\"" << endl;	
	}

	if (s5 < s6) {
		cout << "s5 < s6" << endl;	
	} else {
		cout << "s5 > s6" << endl;	
	}

	// bool operator>(const char *p);
	// bool operator>(const MyString &obj);
	if (s5 > "bbbbbb") {
		cout << "s5 > \"bbbbbb\"" << endl;	
	} else {
		cout << "s5 > \"bbbbbb\"" << endl;	
	}

	if (s5 > s6) {
		cout << "s5 > s6" << endl;	
	} else {
		cout << "s5 < s6" << endl;	
	}

	// 其他技巧
	MyString s7("aaaaaa");
	// strcpy(s7, "bbbbb");
	strcpy(s7.c_str(), "bbbbb");
	s7.Debug();
	
	// 重载>>
	MyString s8(128);
	strcpy(s8.c_str(), "bbbbb");
	s8.Debug();
	
	//istream & operator>>(istream &in, MyString &s)
	MyString s9(128);
	cin >> s9;
	s9.Debug();
	

	return 0;
}
