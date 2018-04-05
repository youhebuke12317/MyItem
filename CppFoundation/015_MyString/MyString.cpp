/*************************************************************************
    > File Name: MyString.cpp
    > Author: reus
    > Mail: dmarcoreus@gmail.com 
    > Created Time: Thu Mar  1 21:07:00 2018
    > Brief: 
 ************************************************************************/

#include <iostream>
using namespace std;

#include "MyString.h"

int global_id;

#ifdef TEST_COMAND
MyString::MyString()
{
	m_len = 0;
	m_id  = ++global_id;
	m_ptr = new char[m_len + 1];

	strcpy(m_ptr, "");	

	m_id  = ++global_id;

	cout << "构造函数 --- m_id = " << m_id << endl;

	return ;
}
#else

MyString::MyString(int len)
{
	if (len == 0)  {
		m_len = 0;
		m_id  = ++global_id;
		m_ptr = new char[m_len + 1];

		strcpy(m_ptr, "");	
	} else {

		m_len = len;
		m_ptr = new char[m_len + 1];

		bzero(m_ptr, 0);	
	}

	m_id  = ++global_id;

	cout << "构造函数 --- m_id = " << m_id << endl;

	return ;
}
#endif

MyString::MyString(const char *ptr)
{
	if (ptr == NULL) {
		m_len = 0;
		m_id  = ++global_id;
		m_ptr = new char[m_len + 1];
		strcpy(m_ptr, "");	
	} else {
		m_len = strlen(ptr);
		m_id  = ++global_id;
		m_ptr = new char[m_len + 1];
		strcpy(m_ptr, ptr);	
	}
	cout << "构造函数 --- m_id = " << m_id << endl;

	return ;
}

// 拷贝构造函数
MyString::MyString(const MyString &obj)
{
	m_len = obj.m_len;
	m_id  = ++global_id;
	m_ptr = new char[m_len + 1];

	strcpy(m_ptr, obj.m_ptr);

	cout << "构造函数 --- m_id = " << m_id << endl;

	return ;
}

MyString::~MyString()
{
	cout << "析构函数 --- m_id = " << m_id << endl;

	if (m_ptr != NULL) {
		delete [] m_ptr;
		m_ptr = NULL;
		m_len = 0;
	}
	return ;
}

//// s4 = s2;
MyString & MyString::operator=(const char *p)
{
	if (m_ptr != NULL) {
		delete [] m_ptr;
		m_len = 0;
	}

	if (p == NULL) {
		m_len = 0;
		m_ptr = new char[m_len + 1];
		strcpy(m_ptr, "");
	} else {
		m_len = strlen(p);
		m_ptr = new char[m_len + 1];
		strcpy(m_ptr, p);
	}

	return *this;
}

MyString & MyString::operator=(const MyString &obj)
{
	if (m_ptr != NULL) {
		delete [] m_ptr;
		m_len = 0;
	}

	m_len = obj.m_len;
	m_ptr = new char[m_len + 1];
	strcpy(m_ptr, obj.m_ptr);

	return *this;
}

char & MyString::operator[](int index)
{
	if (index < 0) {
		return m_ptr[0];	
	}

	if (index > m_len) {
		return m_ptr[m_len - 1];	
	}

	return m_ptr[index];
}

ostream & operator<<(ostream &out, MyString &obj)
{
	out << obj.m_ptr;

	return out;
}

istream & operator>>(istream &in, MyString &obj)
{
	cin >> obj.m_ptr;

	return in;
}

bool MyString::operator==(const char *p) const 
{
	if (p == NULL) {
		if (m_len == 0) return true;
		else			return false; 
	}

	if (m_len == strlen(p)) {
		return !strcmp(m_ptr, p);
	}

	return false;
}

bool MyString::operator==(const MyString &obj) const 
{
	if (obj.m_len == m_len) {
		return !strcmp(m_ptr, obj.m_ptr);
	} 

	return false;
}

bool MyString::operator!=(const char *p) const
{
	return !(*this == p);
}

bool MyString::operator!=(const MyString &obj) const 
{
	return !(*this == obj);
	return true;
}

bool MyString::operator<(const char *p) const
{
	if (!p) return false;

	if (strcmp(m_ptr, p) < 0)	return true;

	return false;
}

bool MyString::operator<(const MyString &obj) const
{
	if (strcmp(m_ptr, obj.m_ptr) < 0)	return true;

	return false;
}

bool MyString::operator>(const char *p) const
{
	if (!p) return true;

	if (strcmp(m_ptr, p) > 0)	return true;

	return false;
}

bool MyString::operator>(const MyString &obj) const
{
	if (strcmp(m_ptr, obj.m_ptr) > 0)	return true;

	return false;
}

void MyString::Debug()
{
	cout << "[ " << m_id << " ] " << "m_ptr: " << m_ptr << endl;

	return ;
}
