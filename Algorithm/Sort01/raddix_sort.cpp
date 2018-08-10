/**
* @file			raddix_sort.cpp
* @brief		Sample project head file
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年08月06日 星期一 14时29分02秒
*/
// leedcode 217题

#include <iostream>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

/*
 * @detail 基数排序实现
 * @param  num	待排序数组
 * @param  n	待排序数组长度
 * */
void raddix_sort(int *num, int n) {
	int *temp = (int *)malloc(sizeof(int) * n);
	int cnt[65536] = {0};

	// 对低16位排序
	for (int i = 0; i < n; i++) cnt[num[i] & 0xffff] += 1;  
	for (int i = 1; i < 65536; i++) cnt[i] += cnt[i - 1]; 
	for (int i = n - 1; i >= 0; i--) temp[--cnt[num[i] & 0xffff]] = num[i]; 

	memset(cnt, 0, sizeof(cnt));

	for (int i = 0; i < n; i++) cnt[(temp[i] >> 16) & 0xffff] += 1;
	for (int i = 1; i < 65536; i++) cnt[i] += cnt[i - 1];
	for (int i = n - 1; i >= 0; i--) num[--cnt[(temp[i] >> 16) & 0xffff]] = temp[i];

	free(temp);
	return ;
}

int output(int *num, int n) {
	int flags = 1;
	printf("[");
	for (int i = 1; i < n; i++) {
		if (i) flags = (num[i] < num[i - 1]);
		printf("%d ", num[i]);
	}
	printf("]\n");
	return flags;
}

void test_output(int *num, int n) {
	if (output(num, n)) {
		printf("\033[31m FAIL \033[0m\n");
	} else {
		printf("\033[32m OK \033[0m\n");
	}
}

#define MAX_NUM_LEN		5000
int main() {
	srand(time(0));
	int num[MAX_NUM_LEN];
	for (int i = 0; i < MAX_NUM_LEN; i++) {
		num[i] = rand();
	}

	output(num, MAX_NUM_LEN);
	raddix_sort(num, MAX_NUM_LEN);
	test_output(num, MAX_NUM_LEN);
}
