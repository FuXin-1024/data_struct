#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<assert.h>

using namespace std;

 //请实现一个函数，把字符串中的每个空格替换成%20.例如
//输入"We are happy." 输出"we are%20are%20happy."。
char* ReplaceBlank(char* str)
{
	assert(str);
	int count = 0;  // 统计空格的个数
	char* front_ptr = str;
	while (*front_ptr != '\0')
	{
		if (*front_ptr == ' ')
		{
			++count;
		}
		++front_ptr;// front_ptr指向原数组的末尾->'\0'
	}

	//替换后数组的尾指针
	char* back_ptr = front_ptr + count*(3 - 1);   // 一个空格增加了两个字符
	//开始进行从后往前复制
	while (back_ptr > front_ptr)
	{
		//遇到空格替换成%20.   front_ptr往前走一步，back_ptr往前走三步
		if (*front_ptr == ' ')
		{
			*back_ptr-- = '0'; 
			*back_ptr-- = '2';
			*back_ptr-- = '%';
			--front_ptr;
		}
		else
		{
			//没遇到空格，依次复制
			*back_ptr-- = *front_ptr--;
		}
	}
	return str;
}

void Test()
{
	char str1[50]="We are happy.";
	cout << ReplaceBlank(str1) << endl;
	char str2[50] = " We are happy.";
	cout << ReplaceBlank(str2) << endl;
	char str3[50] = " We are happy. ";
	cout << ReplaceBlank(str3) << endl;
	char str4[50] = "We  are happy.";
	cout << ReplaceBlank(str4) << endl;
	char str5[50] = "      ";
	cout << ReplaceBlank(str5) << endl;
	char str6[50] = "Wearehappy.";
	cout << ReplaceBlank(str6) << endl;
	char* str7 = NULL;
	cout << ReplaceBlank(str7) << endl;
}
int main()
{
	Test();
	system("pause");
	return 0;	
}