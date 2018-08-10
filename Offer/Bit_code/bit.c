/**
* @file			bit.c
* @brief		Sample project head file
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年08月05日 星期日 15时26分47秒
*/
/*
 * 1. 如果一个数n为2的幂，则任取一个数x，能使得(x % n = x & (x - 1))
 * 		那么如何判断一个数是2的幂呢, 则判断(n & (n - 1) = 0)即可
 *
 * 2. x & (x - 1)	表示去掉x中二进制数中的一个1
 * 3. x & -x = x & (~x + 1)		表示取x中二进制中的最后一个1
 * 4. x ^ (x & -x) 				表示去掉x中二进制中的最后一个1
 * */

#include <stdio.h>
#include <stdlib.h>

int main()
{
	int i = 0;
	int index[2] = {7, 8};

	for (; i < 2; i++) {
		if ((index[i] & (index[i] - 1))) {
			printf("%d 不是2的幂\n", index[i]);
		}		
		else {
			printf("%d 是2的幂\n", index[i]);
		}
	}

	unsigned int a = 0x7FFFFFFA;
	a = a + 10;

	printf("%d\n", a);
}
