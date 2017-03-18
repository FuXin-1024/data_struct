#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string.h>
using namespace std;

// 剑指offer
// 赋值运算符函数

class String
{
public:
	// 构造函数
	String(const char* str=NULL)
	{
		if (str != NULL)
		{
			_str = new char[strlen(str) + 1];
			strcpy(_str, str);
		}
		else
		{
			_str = new char[1];
			*_str = '\0';
		}
	}

	// 拷贝构造函数
	String(const String& s)
		:_str(NULL)
	{
		String tmp(s._str);
		swap(_str, tmp._str);
	}

	//运算符重载
		String& operator=(const String& s)
	{
		if (this != &s)
		{
			String tmp(s);
			swap(_str, tmp._str);
		}
		return*this;
	}
	//析构函数
	~String()
	{
		if (_str!=NULL)
		{
			delete[] _str;
			_str = NULL;
		}
	}
private:
	char* _str;
};

void Test()
{
	String s1("123");
	String s2(s1);
	String s3(NULL);
	s3 = s2 = s1;
}
int main()
{
	Test();
	system("pasue");
	return 0;
}