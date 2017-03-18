#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string.h>
using namespace std;

// ��ָoffer
// ��ֵ���������

class String
{
public:
	// ���캯��
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

	// �������캯��
	String(const String& s)
		:_str(NULL)
	{
		String tmp(s._str);
		swap(_str, tmp._str);
	}

	//���������
		String& operator=(const String& s)
	{
		if (this != &s)
		{
			String tmp(s);
			swap(_str, tmp._str);
		}
		return*this;
	}
	//��������
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