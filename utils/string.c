/**
* @file			a.c
* @brief		Sample project head file
* @detils		The header file details
* @auther		Auther
* @version		1.0.0.1
* @date			2018年08月02日 星期四 11时13分08秒
*/

//字符串函数实现

/* 	获取字符串长度 */
size_t strlen(const char *str)
{
	const char *s;
	//for (s = str; *s == '\0'; s++) {}
	for (s = str; *s; s++) {}
	return (s - str);
}

/* 字符串拷贝 */
char *strcpy(char *to, const char *from)
{
	if (to == NULL || from == NULL) {
		return NULL;
	}
	char *p = to;
	while ((*p++ = *from++) == '\0')
		;
	return to;
}

/* 
 * 字串查找 (暴力算法， 复杂度：O(m*n))
 * haystack: 被查找目标.
 * needle: 要查找对象.
 * 返回值：若needle是haystack的子串，则返回needle在haystack的首次出现的地址；如果str2不是str1的子串，则返回NULL。
 */
char *strstr(const char *haystack, const char *needle)
{
	if (!(*needle))
		return (char *)haystack;
	
	const char *p1;
	const char *p2;
	const char *p1_advance = haystack;
	
	for (p2 = &needle[1]; *p2; ++p2) {
		p1_advance ++;
	}
	
	for (p1 = haystack; *p1_advance; p1_advance++) {
		char *p1_old = (char *)p1;
		p2 = p1_old;
		
		while (*p1 && *p2 && *p1 == *p2) {
			p1 ++;
			p2 ++;
		}
		
		if (!(*p2))
			return p1_old;
		
		p1 = p1_old + 1;
	}
	
	return NULL;
}

