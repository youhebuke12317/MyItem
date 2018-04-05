/*************************************************************************
    > File Name: MyString.h
    > Author: reus
    > Mail: dmarcoreus@gmail.com 
    > Created Time: Thu Mar  1 21:03:11 2018
    > Brief: 
 ************************************************************************/

#include <iostream>
using namespace std;

//#define TEST_COMAND
extern int global_id;

// C中没有字符串 字符串类
class MyString
{
	// 为什么使用友元函数 ??????
	friend ostream & operator<<(ostream &out, MyString &obj);
	friend istream & operator>>(istream &in, MyString &obj);

	public:		// 构造函数与析构函数
#if TEST_COMAND
		MyString();
#else
		MyString(int len = 0);
#endif
		MyString(const char *ptr);
		MyString(const MyString &obj);
		~MyString();

	public:		// 运算符重载
		MyString & operator=(const char *p);
		MyString & operator=(const MyString &obj);
		char & operator[](int index);
		bool operator==(const char *p) const; // 后面加const标识this指针指向的空间不能被改变
		bool operator==(const MyString &obj) const;
		bool operator!=(const char *p) const;
		bool operator!=(const MyString &obj) const;
		bool operator< (const char *p) const;
		bool operator< (const MyString &obj) const;
		bool operator> (const char *p) const;
		bool operator> (const MyString &obj) const;

	public:
		// 把类的指针漏出来
		char *c_str() {
			return m_ptr;
		}

		int length() {
			return m_len;
		}

	public:
		void Debug();

	private:
		int		m_id;
		int		m_len;
		char	*m_ptr;
};
