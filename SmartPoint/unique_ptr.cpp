/**
* @file			unique_ptr.cpp
* @brief		Sample project head file
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年08月10日 星期五 21时14分46秒
*/

#include <iostream>
using namespace std;

#include <iostream>
#include <memory>

int main() {
	{
		unique_ptr<int> uptr(new int(10));  //绑定动态对象
		//unique_ptr<int> uptr2 = uptr;  	//不能赋值
		//unique_ptr<int> uptr2(uptr);  	//不能拷贝
		unique_ptr<int> uptr2 = move(uptr); //替换所有权
		uptr2.release(); //释放所有权
	}
	//超过uptr的作用域，內存释放
}
