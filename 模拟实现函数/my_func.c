#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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

char* my_strncpy(char* dst, const char* src, int n)
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

int my_strncmp(const char* str1, const char* str2, int n)
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
void* my_memmove(void* dest, const void* src, size_t n)
{
	assert(dest);
	assert(src);
	char* pdest = (char*)dest;
	const char*psrc = ( const char*)src;
	
	//正常情况下，从前往后拷贝
	if (pdest <= psrc&& pdest >= psrc + n)
	{
		while (n--)
		{
			*pdest++ = *psrc;
		}
	}
	//内存有重叠时，从后往前拷贝
	else
	{
		while (n--)
		{
			*(pdest +n) = *(psrc+n);
		}
	}
	return dest;

}

void* my_memcpy(void* dest, const void* src, size_t n)
{
	assert(dest);
	assert(src);
	char* pdest = (char*)dest;
	const char* psrc = (const char*)src;
	while (n--)
	{
		*pdest++ = *psrc++;
	}
	return dest;
}
void Test_Memmove()
{
	char arr[10] = "abcdefg";
	char arr0[10] = "abcdefg";
	char arr1[10] = { 0 };
	my_memmove(arr + 2, arr, 4);
	my_memmove(arr1, arr0, 4);
	printf("内存覆盖情况：%s\n", arr + 2);
	printf("正常情况：%s\n", arr1);
}
void Test_Memcpy()
{
	char arr[10] = "abcdefg";
	char arr0[10] = "abcdefg";
	char arr1[10] = { 0 };
	my_memcpy(arr + 2, arr, 4);
	my_memcpy(arr1, arr0, 4);
	printf("内存覆盖情况：%s\n", arr+2);
	printf("正常情况：%s\n", arr1);
}
void Test()
{
	char s[30] = "abkd";
	char s1[] = "abgh";
	printf("%d\n", my_strncmp(s, s1, 6));
}
int  main()
{
	//Test();
	Test_Memcpy();
	system("pause");
	return 0;
}