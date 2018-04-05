/*************************************************************************
    > File Name: array.h
    > Author: reus
    > Mail: dmarcoreus@gmail.com 
    > Created Time: 日  1/14 10:37:10 2018
 ************************************************************************/

//#ifndef __ARRAY_H__
//#define __ARRAY_H__
//
//#endif

#pragma once

class Array {
	public:
		Array(int length);
		Array(const Array& obj);
		~Array();

	public:
		void setData(int index, int value);
		int  getData(int index);
		int  length();
		char operator[](int index);
		int  operator==(Array &ary);
		int  operator!=(Array &ary);

	private:
		int m_length;
		char *m_space;
};

// 要求重载一下操作符
// []   ==   !=
