#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include"HuffmanTree.h"

using namespace std;

typedef long long LongType;
struct CharInfo
{
	char _ch;//�ַ�
	LongType _count;//�ַ����ֵĴ���
	string _code;// h

	CharInfo(LongType count = 0)
		:_count(count)
		, _ch(0)
	{}

	bool operator!=(const CharInfo& info)const
	{
		return _count != info._count;
	}

	CharInfo operator+ (const CharInfo& info)
	{
		return _count + info._count;
	}

	bool operator<(const CharInfo& info)const
	{
		return _count < info._count;
	}
};

class FileCompress
{
public:
	void Compress(const char* filename)
	{

	}
protected:
	CharInfo _infos[256]; //�����ַ�����Ϣ��
};