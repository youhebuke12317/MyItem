/*************************************************************************
    > File Name: offer_QuitSort.c
    > Author: zhengli
    > Mail: zldata@aliyun.com 
    > Created Time: 日  5/ 6 20:20:00 2018
    > Brief: 
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

void printdata(char *str, int *data, int length);

int RandomInRange(int min, int max)
{
    int random = rand() % (max - min + 1) + min;
    return random;
}

void MySwap(int *num1, int *num2)
{
	int temp = *num1;
	*num1    = *num2;
	*num2    = temp;
}

int Offer_Partition(int *data, int length, int start, int end)
{
	if (data == NULL || length <= 0 || start < 0 || end >= length)
		return -1;

	printdata("[start] ", data, length);

	int index = RandomInRange(start, end);
	MySwap(&data[index], &data[end]);

	printdata("[ swap] ", data, length);

	int small = start - 1;
	for (index = start; index < end; ++ index) {
		if (data[index] < data[end]) {
			++small;
			if (small != index) 
				MySwap(&data[index], &data[small]);
		}

		printdata("[ loop] ", data, length);
	}

	++ small;
	MySwap(&data[small], &data[end]);

	printdata("[  end] ", data, length);

	return small;
}

void printdata(char *str, int *data, int length)
{
	printf("%s", str);

	int i = 0;
	for (i = 0; i < length; i++) {
		printf("%d ", data[i]);
	}
	printf("\n");
}
