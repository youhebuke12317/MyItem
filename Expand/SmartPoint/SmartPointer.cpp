/**
* @file			SmartPointer.cpp
* @brief		Sample project head file
* @detils		基于引用计数的智能指针的实现，需要实现构造，
* 				析构，拷贝构造，=操作符重载，重载*-和>操作符
* @auther		Auther
* @version		1.0.0.1
* @date			2018年07月27日 星期五 20时02分02秒
* @ref			https://blog.csdn.net/worldwindjp/article/details/18843087#comments
*/


#include <iostream>
using namespace std;

template <typename T>
class SmartPointer {
	public:
		//构造函数
		SmartPointer(T* p = 0): _ptr(p), _reference_count(new size_t){
			cout << "构造函数" << endl;
			if(p)
				*_reference_count = 1; 
			else
				*_reference_count = 0; 
		}

		//拷贝构造函数
		SmartPointer(const SmartPointer& src) {
			cout << "拷贝构造函数" << endl;
			if(this != &src) {
				_ptr = src._ptr;
				_reference_count = src._reference_count;
				(*_reference_count)++;
			}
		}

		//重载赋值操作符
		SmartPointer& operator=(const SmartPointer& src) {
			cout << "重载赋值操作符" << endl;
			if(_ptr == src._ptr) {
				return *this;
			}

			// 这里如果ptr不为NULL 并且引用计数不为0
			releaseCount();

			_ptr = src._ptr;
			_reference_count = src._reference_count;
			(*_reference_count)++;

			return *this;
		}

		//重载操作符
		T& operator*() {
			cout << "重载操作符 * " << endl;
			if(_ptr != NULL) {
				return *_ptr;
			}
			//throw exception
		}

		//重载操作符
		T* operator->() {
			cout << "重载操作符 -> " << endl;
			if(_ptr) {
				return _ptr;
			}
			//throw exception
		}

		//析构函数
		~SmartPointer() {
			cout << "析构函数" << endl;
			if (--(*_reference_count) == 0) {
				delete _ptr;
				delete _reference_count;
			}
		}

	private:
		T *_ptr;
		size_t *_reference_count;

		void releaseCount() {
			if(_ptr != NULL) {
				(*_reference_count)--;
				if((*_reference_count) == 0) {
					delete _ptr;
					delete _reference_count;
				}
			}
		}
};

int main() 
{
	SmartPointer<char> cp1(new char('a'));
	SmartPointer<char> cp2(cp1);
	SmartPointer<char> cp3;
	cp3 = cp2;
	cp3 = cp1;
	cp3 = cp3;
	SmartPointer<char> cp4(new char('b'));
	cp3 = cp4;
}

