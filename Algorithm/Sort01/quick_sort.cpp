/**
* @file			quick_sort.cpp
* @brief		Sample project head file
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年08月06日 星期一 10时36分40秒
*/

#include <iostream>
#include <ctime>
#include <cstdio>
#include <cstdlib>
using namespace std;

#define THREE_MIN(x, y, z) 				\
	std::min((std::min(x, y)), y)

/* 有问题 -- 死循环了 */
void quick_sort1(int *num, int l, int r, int k) {
	if (r - l < 1) return;
	int x = l, y = r, z = THREE_MIN(num[l], num[r], num[(l + r) >> 1]);
	do {
		while (x < z) ++x;
		while (y > z) --y;
		if (x <= y) {
			std::swap(num[x], num[y]);
			++x, --y;
		}
	} while (x <= y);

	quick_sort1(num, l, y, k);
	quick_sort1(num, x, r, k);

	return ;
}

/*
 * @detail 插入排序实现 - 快速排序中当数据较少时 可以使用插入排序
 * @param  num	待排序数组
 * @param  n	待排序数组长度
 * */
int insert_sort(int *num, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j >= 1; j--) {
			if (num[j] < num[j - 1]) std::swap(num[j], num[j - 1]);
			else break;
		}
	}

	return 0;
}


/*
 * @detail 堆排序 - 快速排序中当递归深度过高时 可以使用堆排序
 * @param  num	待排序数组
 * @param  n	待排序数组长度
 * */
int heap_sort(int *num, int n) {
	num -= 1;	/* 保证从1开始计数 */
	int ind = n >> 1;
	for (int i = ind; i >= 1; --i) {
		int swap_ind = ind;
		do {
			if (num[swap_ind] < num[ind << 1])	swap_ind = ind << 1;
			if (((ind << 1) | 1) <= n && num[(ind << 1 | 1)] > num[swap_ind]) swap_ind = ind << 1 | 1;
			if (swap_ind == ind) break;
			std::swap(num[ind], num[swap_ind]);
			ind = swap_ind;
		} while ((ind << 1) <= n);
	}
	for (int i = 0; i < n - 1; i++) {
		std::swap(num[i], num[n - i]);
		int ind = 1, swap_ind = 1;
		do {
			if (num[swap_ind] < num[ind << 1])  swap_ind = ind << 1;
			if (((ind << 1) | 1) <= n -i - 1 && num[(ind << 1 | 1)] > num[swap_ind]) swap_ind = ind << 1 | 1;  
			if (swap_ind == ind) break;
			std::swap(num[ind], num[swap_ind]);
			ind = swap_ind;
		} while ((ind << 1) <= n - i - 1);
	}
	return 0;
}

/*
 * @tails 快排实现 - 实际情况下是多种场景不同排序算法的组合
 * @param num 待快排数组
 * @param l   待快排数组开始位置
 * @param r   待快排数组结束位置
 * @param k   递归深度上限, 每一次递归调用减1
 * 		当切割数据小时，使用插入排序
 * 		当递归深度过高，直接使用堆排序
 * */
void quick_sort(int *num, int l, int r, int k) {
	k || heap_sort(num + l, r - l + 1);
	while (r - l >= 15) {
		int x = l, y = r, z = THREE_MIN(num[l], num[r], num[(l + r) >> 1]);
		do {
			while (num[x] < z) ++x;
			while (num[y] > z) --y;
			if (x <= y) {
				std::swap(num[x], num[y]);
				++x, --y;
			}
		} while (x <= y);

		quick_sort(num, l, y, k - 1);
		l = x;
	}
	l || insert_sort(num + l, r - l + 1);
	// l && ungarded_insert_sort(num + l, r -l + 1);
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
	quick_sort(num, 0, MAX_NUM_LEN - 1, 50);
	test_output(num, MAX_NUM_LEN);
}
