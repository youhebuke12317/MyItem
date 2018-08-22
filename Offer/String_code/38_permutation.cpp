/**
* @file			38_permutation.cpp
* @brief		Sample project head file
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年08月22日 星期三 10时26分56秒
*/

#include <iostream>
#include <cstdio>
using namespace std;

#define STRING_END	'\0'
#define PLOG(p)		printf("%s\n", p)

void permutationCore(char *ptr, char *pBegin) {
	if (*pBegin == STRING_END) 
		PLOG(ptr);
	else {
		for (char *pCh = pBegin; *pCh != STRING_END; ++ pCh) {
			swap(*pCh, *pBegin);
			permutationCore(ptr, pBegin + 1);
			swap(*pCh, *pBegin);
		}
	}
}

void permutation(char *ptr) {
	if (!ptr) return; 
	permutationCore(ptr, ptr);
}

int main() {
	return 0;
}
