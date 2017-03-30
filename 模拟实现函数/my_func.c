#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

char* my_strcpy(char* dst, const char* src)
{
	assert(dst);
	assert(src);
	char* ret = dst;
	while (*dst++ == *src++)
	{
	}
	return ret;
}

char* my_strncpy(char* dst, const char* src,int n)
{
	assert(dst);
	assert(src);
	char* ret = dst;
	while (n)
	{
		*dst++ = *src++;
		--n;
	}
	*dst = '\0';
	return ret;
}

char* my_strcat(char* dst, const char* src)
{
	assert(dst);
	assert(src);
	char* ret = dst;
	//找到dst末尾的'\0'
	while (*dst)
	{
		dst++;
	}
	//把src连接到dst后面
	while (*src)
	{
		*dst++ = *src++;
	}
	
	return ret;
}

char* my_strncat(char* dst, const char* src, int n)
{
	assert(dst);
	assert(src);
	char* ret = dst;
	while (*dst)
	{
		dst++;
	}
	
	while (n--)
	{
		*dst++ = *src++;
		
	}
	return ret;
}

//模拟实现strcmp
//str1>str2,返回正数；
//str1<str2,返回负数；
//str1=str2,返回0；
//逐个字符比较ASCII值
int my_strcmp(const char* str1, const char* str2)
{
	assert(str1);
	assert(str2);
	while (*(str1) == *(str2))
	{
		if (*str1 == '\0')
			return 0;
		str1++;
		str2++;
	}
	if (*str1 > *str2)
		return 1;
	else
		return -1;
}

int my_strncmp(const char* str1, const char* str2,int n)
{
	assert(str1);
	assert(str2);
	while (n)
	{
		if (*str1 == *str2)
		{
			str1++;
			str2++;
		}
		else
		{
			return *str1 - *str2;
		}
		n--;
	}
	return 0;
}
void Test()
{
	char s[30] = "abkd";
	char s1[] = "abgh";
	printf("%d\n", my_strncmp(s, s1,6));
}
int  main()
{
	Test();
	system("pause");
	return 0;
}