/**
* @file			Bit.c
* @brief		Sample project head file
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年05月10日 星期四 22时36分59秒
*/

#include <stdio.h>
#include <stdlib.h>

/*
 * 递归 -- 通过位运算实现两个整数之间的加法
 * */
int AddByBit_Recursive(int num1, int num2)                                      
{
	// printf("start: num1 = %d, num2 = %d\n", num1, num2);         

	if (num2 == 0)  return num1;                                 

	int sumTemp = (num1 ^ num2);                                 
	int carry = (num1 & num2) << 1;                              

	// printf("end: sumTemp = %d, carry = %d\n", sumTemp, carry);                                                                                                                  

	return AddByBit_Recursive(sumTemp, carry);                                  
}


/*
 * 非递归 -- 通过位运算实现两个整数之间的加法
 * */
int AddByBit(int num1, int num2)
{
	int SUM = 0;
	int XOR = 0;
	int AND = 0;

	int index = 0;

	while ((num1 & num2) > 0) {

		printf("[%d] num1 = %d, num2 = %d\n", ++index, num1, num2);

		XOR  = num1 ^ num2;
		AND  = num1 & num2;
		num1 = XOR;
		num2 = AND << 1;
	}

	SUM = num1 ^ num2;

	return SUM;
}

/*
 * 位运算实现除法运算
 * 有点似懂非懂!!!!!!
 * */
int DivBit(const int x, const int y)
{
	int left_num = x;
	int result = 0;

	while (left_num >= y) {
		int multi = 1;
		while (y * multi <= (left_num >> 1)) {
			multi = multi + 1;
		}
		result   += multi;
		left_num -= y * multi;
	}
	return result;
}

#if 0
int main()
{
	printf("%d\n", AddByBit(7, 2));

	return 0;
}
#endif
