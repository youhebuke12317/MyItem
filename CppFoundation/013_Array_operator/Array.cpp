/*************************************************************************
    > File Name: array.cpp
    > Author: reus
    > Mail: dmarcoreus@gmail.com 
    > Created Time: 日  1/14 10:37:04 2018
 ************************************************************************/

#include <iostream>
using namespace std;

#include "Array.h"

Array::Array(int length)
{
	if (length < 0) {
		length = 0;
	}

	m_length = length;
	m_space  = new char[m_length];
}

Array::Array(const Array& obj)
{
	this->m_length = obj.m_length;
	this->m_space  = new char[this->m_length]; //分配内存空间

	for (int i = 0; i < m_length; i++) {	//数据元素复制
		this->m_space[i] = obj.m_space[i];
	}
}

Array::~Array()
{
	cout << "我是析构函数" << endl;
}

void Array::setData(int index, int value)
{
	m_space[index] = value;
	return ;
}

int  Array::getData(int index)
{
	return m_space[index];
}

int  Array::length()
{
	return m_length;
}


char Array::operator[](int index)
{
	if (index < 0 || index > m_length) {
		return m_space[m_length];
	}

	return m_space[index];
}

int Array::operator==(Array &ary)
{
	if (m_length != ary.m_length )	return -1;
	else {
		for (int i = 0; i < m_length; i++) {
			if (m_space[i] != ary.m_space[i])
				return -1;
		}
	}
	return 0;
}

int Array::operator!=(Array &ary)
{
	if (m_length != ary.m_length )	return 0;
	else {
		for (int i = 0; i < m_length; i++) {
			if (m_space[i] != ary.m_space[i])
				return 0;
		}
	}
	return -1;
	
}
