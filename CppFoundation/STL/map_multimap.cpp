/*************************************************************************
    > File Name: map_multimap.cpp
    > Author: zhengli
    > Mail: zldata@aliyun.com 
    > Created Time: 六  4/ 7 12:26:30 2018
    > Brief: 
 ************************************************************************/

#include <iostream>
using namespace std;
#include "map"
#include "string"


/*
 * multimap<key, value>
 * multimap 案例
 * */
class Person 
{
public:
	string	name;
	int		age;
	string	tel;
	double	saly;
};

void main1201()
{
	// string为键值 Person为实值
	multimap<string, Person>	map2;
	Person	p1, p2, p3, p4, p5;

	p1.name = "王1";
	p1.age  = 31; 

	p2.name = "王2";
	p2.age  = 32; 

	p3.name = "王3";
	p3.age  = 33; 

	p4.name = "王4";
	p4.age  = 34; 

	p5.name = "王5";
	p5.age  = 35; 


	// sale部门
	map2.insert(make_pair("sale", p1));
	map2.insert(make_pair("sale", p2));

	// devalopment部门
	map2.insert(make_pair("devalopment", p3));
	map2.insert(make_pair("devalopment", p4));

	// Finanacial部门
	map2.insert(make_pair("Finanacial", p5));

	for (multimap<string, Person>::iterator it = map2.begin(); 
			it != map2.end(); it++) {
		cout << it->first << "\t" << it->second.name << endl;
	}

	int num2 = map2.count("devalopment");
	cout << "devalopment 部门人数: " << num2 << endl;

	cout << "devalopment 员工信息：" << endl;
	int tag = 0;
	multimap<string, Person>::iterator it2 = map2.find("devalopment");
	while (it2 != map2.end() && tag < num2) {
		cout << it2->first << "\t" << it2->second.name << endl;
		it2++;
		tag++;
	}


	cout << "按照条件 检索数据 修改员工信息" << endl;
	for (multimap<string, Person>::iterator it3 = map2.begin(); 
			it3 != map2.end(); it3++) {
		if (it3 -> second.age == 32) {
			it3 -> second.name = "name32";
		}
	}

	for (multimap<string, Person>::iterator it4 = map2.begin();
			it4 != map2.end(); it4++) {
		cout << it4 -> first << "\t" << it4 -> second.name << endl;
	}

	
}


int main()
{
	main1201();

	return 0;
}
