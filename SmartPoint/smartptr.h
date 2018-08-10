/**
* @file			智能指针.cpp
* @brief		Sample project head file
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年07月27日 星期五 19时17分35秒
*/

/*********************************************************
 * 因此，我们使用智能指针的原因至少有以下三点：
 * 　1）智能指针能够帮助我们处理资源泄露问题；
 * 　2）它也能够帮我们处理空悬指针的问题；
 * 　3）它还能够帮我们处理比较隐晦的由异常造成的资源泄露。
 * *******************************************************/
#include <iostream>
#include <cstdlib>
using namespace std;

template<class T>
class SmartPtr
{
	public:
		SmartPtr(T *p);		/* 有参构造函数 */
		~SmartPtr();		/* 析构函数 */
		SmartPtr(const SmartPtr<T> &orig);                 /* 拷贝构造函数 - 浅拷贝 */
		SmartPtr<T>& operator=(const SmartPtr<T> &rhs);    /* = 运算符重载 - 浅拷贝 */
	private:
		T *ptr;
		int *use_count;	/* 将use_count声明成指针是为了方便对其的递增或递减操作 */
};

template<class T>
SmartPtr<T>::SmartPtr(T *p) : ptr(p)
{
	try {
		use_count = new int(1);
	}

	catch (...) {
		delete ptr;
		ptr = NULL;
		use_count = NULL;
		cout << "[有参构造函数] Allocate memory for use_count fails." << endl;
		exit(1);
	}

	cout << "[有参构造函数] Constructor is called!" << endl;
}

template<class T>
SmartPtr<T>::~SmartPtr()
{
	// 只在最后一个对象引用ptr时才释放内存
	if (--(*use_count) == 0) {
		delete ptr;
		delete use_count;
		ptr = NULL;
		use_count = NULL;
		cout << "[析构函数] Destructor is called!" << endl;
	}
}

template<class T>
SmartPtr<T>::SmartPtr(const SmartPtr<T> &orig)
{
	ptr = orig.ptr;
	use_count = orig.use_count;
	++(*use_count);
	cout << "[拷贝构造函数 - 浅拷贝] Copy constructor is called!" << endl;
}

/*
 * 重载等号函数不同于复制构造函数，即等号左边的对象可能已经指向某块内存。
 * 这样，我们就得先判断左边对象指向的内存已经被引用的次数。如果次数为1，
 * 表明我们可以释放这块内存；反之则不释放，由其他对象来释放。
 * */
template<class T>
SmartPtr<T>& SmartPtr<T>::operator=(const SmartPtr<T> &rhs)
{
	// 《C++ primer》：“这个赋值操作符在减少左操作数的使用计数之前使rhs的使用计数加1，
	// 从而防止自身赋值”而导致的提早释放内存
	++(*rhs.use_count);

	// 将左操作数对象的使用计数减1，若该对象的使用计数减至0，则删除该对象
	if (--(*use_count) == 0) {
		delete ptr;
		delete use_count;
		cout << "[= 运算符重载 - 浅拷贝] Left side object is deleted!" << endl;
	}

	ptr = rhs.ptr;
	use_count = rhs.use_count;

	cout << "[= 运算符重载 - 浅拷贝] Assignment operator overloaded is called!" << endl;
	return *this;
}
