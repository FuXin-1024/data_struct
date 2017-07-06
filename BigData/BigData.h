#pragma once
#include<iostream>
#include<string>
using namespace std;

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
		while (0 == *data)
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
	friend ostream& operator<<(ostream& _cout, const BigData& b)
	{
		char* data = (char *)b._strData.c_str();
		if ('+' == *data)
			++data;
		_cout << data;
		return _cout;
	}
private:
	string _strData;
	long long _value;
};