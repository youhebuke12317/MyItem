/**
* @file			vector.cpp
* @brief		Sample project head file
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年08月12日 星期日 11时00分16秒
*/

#include <iostream>
using namespace std;
#include <vector>



// vector分配空间大小: 1 2 4 8 16 32 64 128 256 521 1024 ...
void objtest01() {
	vector<int>	vec;
	for (int i = 0; i < 1000; i++) {
		vec.push_back(i);
		cout << "vec.capacity(): " << vec.capacity() << endl;
		cout << "vec.size(): " << vec.size() << endl;
	}
}

// vector成倍增长
void objtest02() {
	vector<int> vec(1000, 0);
	vec.push_back(1);
	cout << "vec.capacity(): " << vec.capacity() << endl;	// 2000
	cout << "vec.size(): " << vec.size() << endl;			// 1001
}

void objtest03() {
	vector<int> vec;
	vec.resize(1000);
	cout << "vec.capacity(): " << vec.capacity() << endl;	// 1000
	cout << "vec.size(): " << vec.size() << endl;			// 1000

	vector<int> vec01;
	vec01.push_back(1);
	cout << "vec.capacity(): " << vec01.capacity() << endl;	// 1
	cout << "vec.size(): " << vec01.size() << endl;			// 1
	vec01.resize(500, 2);
	cout << "vec.capacity(): " << vec01.capacity() << endl;	// 500
	cout << "vec.size(): " << vec01.size() << endl;			// 500
	cout << vec01[0] << " " << vec01[1] << endl;			// 1 2
}

void objtest04() {
	vector<int> vec(1000, 2);
	vec.push_back(1);
	cout << "vec.capacity(): " << vec.capacity() << endl;	// 2000
	cout << "vec.size(): " << vec.size() << endl;			// 1001

	vec.pop_back();
	cout << "vec.capacity(): " << vec.capacity() << endl;	// 2000
	cout << "vec.size(): " << vec.size() << endl;			// 1001

	vector<int>::iterator ite = vec.begin();
	vec.erase(ite);
	cout << "vec.capacity(): " << vec.capacity() << endl;	// 2000
	cout << "vec.size(): " << vec.size() << endl;			// 1001

	vec.erase(ite, ite + 10);
	cout << "vec.capacity(): " << vec.capacity() << endl;	// 2000
	cout << "vec.size(): " << vec.size() << endl;			// 1001
}

int main()  {
	// objtest01();
	// objtest02();
	// objtest03();
	objtest04();
}
