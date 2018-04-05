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
