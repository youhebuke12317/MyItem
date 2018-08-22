/**
* @file			a.c
* @brief		Sample project head file
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年08月02日 星期四 11时13分08秒
*/

/* 将一个字符串转化为整数 */

#define INT_MAX  0x7FFFFFFF
#define INT_MIN  0x80000000

int atoi(const char *str) 
{
	int num = 0;
	int sign = 1;
	const int len = strlen(str);
	int i = 0;
	
	while (str[i] == ' ' && i < len) 
		i++;
	
	if (str[i] == '+') 
		i++;

	if (str[i] == '-') {
		sign = -1;
		i++;
	}
		
	for (; i < len; i++) {
		if (str[i] < '0' || str[i] > '9')
			break;
	
		if (num > INT_MAX / 10 || (num == INT_MAX / 10 && (str[i] - '0') > INT_MAX % 10)) {
			return sign == -1 ? INT_MIN : INT_MAX;
		}
	
		num = num * 10 + str[i] - '0';
	}
	
	return num * sign;
}
