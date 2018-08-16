/**
* @file			shared_ptr.cpp
* @brief		Sample project head file
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年08月10日 星期五 21时00分49秒
*/

#include <iostream>
#include <memory>
using namespace std;

int main() {
	int a = 10;
	shared_ptr<int> ptra = make_shared<int>(a);
	shared_ptr<int> ptra2(ptra);	// copy
	cout << ptra.use_count() << endl;

	int b = 20;
	int *pb = &a;
	// shared_ptr<int> ptrb = pb;  //error
	shared_ptr<int> ptrb = make_shared<int>(b);
	ptra2 = ptrb; 		//assign
	pb = ptrb.get(); 	//获取原始指针

	cout << ptra.use_count() << endl;
	cout << ptrb.use_count() << endl;
}
