#pragma once
#include<iostream>
#include<string>
using namespace std;

const long long MAX = 0x7fffffffffffffff;
const long long MIN = 0x8000000000000000;

class BigData
{
public:
	BigData(long long value)
	:_value(value)
	{}

	BigData(const string& strData)
		:_value(0)
		, _strData("+0")
	{
		//空字符串
		if (strData.empty())
			return;

		//             123456789
		char* data = (char*)strData.c_str();
		while (isspace(*data))
			++data;
		if (*data == '\0')
			return;
		// +12345678
		char symbol = *data; //先把符号位保存下来
		if (isdigit(*data))
			symbol = '+';
		else if (*data == '+' || *data == '-')
			++data;
		else
			return;
		
		//000000000000123456789
		while ('0' == *data)
			++data;
		//直接转换
		_strData.resize(strlen(data) + 1);
		_strData[0] = symbol;
		size_t count = 1;
		while (isdigit(*data))
		{
			_value = _value * 10 + (*data - '0');
			_strData[count++] = *data;
			++ data;
		}
		if ('-' == symbol)
			_value = 0 - _value;
		_strData.resize(count);		
	}
	string GetStrData()
	{
		return _strData;
	}

	BigData operator+(const BigData& b)
	{
		//先判断是否超出范围，若没有则直接用四则运算来做，超出用字符转来运算
		if (IsINT64OverFlow() || b.IsINT64OverFlow())
		{
			//同号处理
			if (_strData[0] == b._strData[0])
				return BigData(StrAdd(_strData, b._strData));
			else //异号
				return BigData(StrSub(_strData, b._strData));
		}
	}

	friend ostream& operator<<(ostream& _cout, const BigData& b)
	{
		char* data = (char *)b._strData.c_str();
		if ('+' == *data)
			++data;
		_cout << data;
		return _cout;
	}
protected:
	bool IsINT64OverFlow()const //判断是否溢出
	{
		//BigData tmp("+9223372036854775807");
		//if ('-' == _strData[0])
		//{
		//	tmp._strData = "-9223372036854775808";
		//}
		////判断长度
		//if (_strData.size() > tmp._strData.size())
		//	return true;
		//else if (_strData.size() == tmp._strData.size()) //长度相同，比较数值大小是否超出
		//{
		//	if (_strData > tmp._strData)
		//		return true;
		//}
		//return false;
		return true;
	}

	bool IsLeftBig(string left, string right) //左操作数 >=右操作数，返回true
	{
		if (left[0] == '-'&& right[0] == '+')
			return false;
		int Lsize = left.size();
		int Rsize = right.size();

		if (Lsize > Rsize)
			return true;
		else if (Lsize == Rsize)
		{
			if (left.compare(right) < 0)
				return false;
			else
				return true;
		}
		return false;
	}
	string StrAdd(string left, string right)//同号字符串相加
	{
		int Lleft = left.size();
		int Lright = right.size();
		//把长度长的作为左操作数
		if (Lleft < Lright)
		{
			left.swap(right);
			swap(Lleft, Lright);
		}

		//进行计算
		string strRes;
		strRes.resize(Lleft + 1); //考虑进位情况，可能进1位
		strRes[0] = left[0];//同号相加，符号位一定相同。
		char step = 0;		//进位

		for (int idx = 1; idx < Lleft; idx++)
		{
			char cRes = left[Lleft - idx] + step - '0';
			if (idx < Lright)
				cRes = cRes + (right[Lright - idx] - '0');
			step = 0;
			while (cRes >= 10) //逢十进位
			{
				step = 1;
				cRes -= 10;
			}
			strRes[Lleft - idx + 1] = cRes + '0';
		}
		//加上最后一次的进位
		strRes[1] = step + '0';
		return strRes;
	}

	string StrSub(string left, string right)//字符串同号相减，异号相加
	{
		int Lleft = left.size();
		int Lright = right.size();
		//把大的字符串当左字符串
		if (!IsLeftBig(left,right))
		{
			left.swap(right);
			swap(Lleft, Lright);
		}
		//进行计算
		char ret = 0;//保存相减的结果
		for (int idx = 1; idx < Lleft; idx++)
		{
			char leftData = left[Lleft - idx] - '0';
			char rightData = right[Lright - idx] - '0';
			char src = left[Lleft - idx - 1];
			if (idx < Lright && leftData < rightData)//需要结尾 
			{
				left[Lleft - idx - 1] = src - 1;
				ret = leftData + 10 - rightData + '0';
				left[Lleft - idx] = ret;
			}
			else
			{
				if (idx < Lright)
					left[Lleft - idx] = leftData - rightData + '0';
				else
					break;
			}
		}
		return left;
	}
private:
	string _strData;//大数运算的数据
	long long _value;//没有超出范围的数
};