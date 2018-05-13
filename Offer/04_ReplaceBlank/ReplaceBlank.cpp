/**
* @file			ReplaceBlank.cpp
* @brief		Sample project head file
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年04月09日 星期一 19时36分29秒
*/

#include <iostream>
using namespace std;

/*
 * @brief  剑指offer -- 面试题4
 * @detail 将字符串中的每个空格替换成 "%20" 
 * @param string	字符串数组
 * @param length	字符串数组string的总容量	
 * @return 成功返回0
 * 		   数组长度不够返回-1
 * 		   其余错误返回-2
 * */
int ReplaceBlank(char *string, int length) 
{
	if (string == NULL || length <= 0) 	return -2;

	int i		  = 0;
	int	real_len  = 0;
	int	blank_num = 0;

	// 遍历数组 得到数组真实长度 以及 空格数
	for (/* void */; string[i] != '\0'; i++) {
		++ real_len;
		if (string[i] == ' ') {
			++ blank_num;
		}
	}

	int	new_len = real_len + 2 * blank_num;
	if (new_len > length) 	return -1;

	// index_real index_new 关键之处
	int index_real = real_len;
	int index_new  = new_len;
	while (real_len > 0 && index_new > index_real) {
		if (string[index_real] == ' ') {
			string[index_new --] = '0';
			string[index_new --] = '2';
			string[index_new --] = '%';
		} 
		else {
			string[index_new --] = string[index_real];
		}

		-- index_real;
	}

	return 0;
}

// TODO 测试用例 
int main()
{
	int 	err;
	char 	array[128] = "We are happy.";

	err = ReplaceBlank(array, 15);
	if (err != 0) {
		cout << "ReplaceBlank error and return " << err << endl;
		return -1;
	}

	cout << "array: " << array << endl;

	return 0;
}
