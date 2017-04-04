#include<stdlib.h>
#include<stdio.h>
#include<assert.h>

enum
{
	valid = 1,
	invalid = 0
};
int flag = valid;
int my_atoi(const char* str)
{
	assert(str);
	long long ret = 0;
	int symbol = 1;//用于判断符号
	//判断是否为空字符
	if (*str == '\0')
	{
		flag = invalid;
		return 0;
	}
	//去掉空格,制表符
	while (isspace(*str))
	{
		str++;
	}
	//判断符号
	if ((*str == '-'))
	{
		symbol = -1;
		str++;
		if (((*str < '0') || (*str > '9')))
		{
			flag = invalid;
			return 0;
		}
	}
	else if (*str == '+')
	{
		str++;
	}
	else if (((*str < '0') || (*str > '9')))
	{
		flag = invalid;
		return 0;
	}
	//处理完异常，开始转换
	while ((*str != '\0') && (*str >= '0') && (*str <= '9'))
	{
		ret = ret * 10 + *str - '0';
		str++;
	}
	//带上符号
	ret *= symbol;
	//检测结果是否溢出
	//int 0111 1111 1111 1111 1111 1111 1111 1111 正溢出
	//     7     f    f   f     f    f    f    f
	//    1000 0000 0000 0000 0000 0000 0000 0000 负溢出
	//      8    0    0   0     0    0    0    0
	if (((ret > 0x7fffffff) && (symbol == 1)) ||
		(ret < (signed int)0x80000000) && (symbol == -1))
	{
		flag = invalid;
		return 0;
	}
	//ret合法
	flag = valid;
	return ret;
}
//打印输出是否异常
void PrintState()
{
	if (flag)
		printf("正常\n");
	else
		printf("异常\n");
}
void Test()
{
	printf("value=%d ", my_atoi("123456789"));//正常
	PrintState();
	printf("value=%d ", my_atoi("-123456789"));//正常
	PrintState();
	printf("value=%d ", my_atoi("-123456789abc"));//正常,遇到字母终止
	PrintState();
	printf("value=%d ", my_atoi("    -123456789abc"));//正常,前面带空格
	PrintState();

	printf("value=%d ", my_atoi("sassa123456789"));//异常,前面有字母
	PrintState();

	printf("value=%d ", my_atoi("123.456789"));//正常 输出123
	PrintState();
	printf("value=%d ", my_atoi("+123.456789"));//正常 输出123
	PrintState();
	printf("\n\n\n");
	printf("value=%d ", my_atoi(""), flag);//异常:空字符串
	PrintState();
	printf("value=%d ", my_atoi("123456789123456789"));//异常:正溢出
	PrintState();
	printf("value=%d ", my_atoi("-123456789123456789"));//异常:负溢出
	PrintState();
	printf("value=%d ", my_atoi("abcd"));//异常:无法转换
	PrintState();
}
int main()
{
	Test();
	system("pause");
	return 0;
}