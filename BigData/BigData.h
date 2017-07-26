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
		//���ַ���
		if (strData.empty())
			return;

		//             123456789
		char* data = (char*)strData.c_str();
		while (isspace(*data))
			++data;
		if (*data == '\0')
			return;
		// +12345678
		char symbol = *data; //�Ȱѷ���λ��������
		if (isdigit(*data))
			symbol = '+';
		else if (*data == '+' || *data == '-')
			++data;
		else
			return;
		
		//000000000000123456789
		while ('0' == *data)
			++data;
		//ֱ��ת��
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
		//���ж��Ƿ񳬳���Χ����û����ֱ�������������������������ַ�ת������
		if (IsINT64OverFlow() || b.IsINT64OverFlow())
		{
			//ͬ�Ŵ���
			if (_strData[0] == b._strData[0])
				return BigData(StrAdd(_strData, b._strData));
			else //���
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
	bool IsINT64OverFlow()const //�ж��Ƿ����
	{
		//BigData tmp("+9223372036854775807");
		//if ('-' == _strData[0])
		//{
		//	tmp._strData = "-9223372036854775808";
		//}
		////�жϳ���
		//if (_strData.size() > tmp._strData.size())
		//	return true;
		//else if (_strData.size() == tmp._strData.size()) //������ͬ���Ƚ���ֵ��С�Ƿ񳬳�
		//{
		//	if (_strData > tmp._strData)
		//		return true;
		//}
		//return false;
		return true;
	}

	bool IsLeftBig(string left, string right) //������� >=�Ҳ�����������true
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
	string StrAdd(string left, string right)//ͬ���ַ������
	{
		int Lleft = left.size();
		int Lright = right.size();
		//�ѳ��ȳ�����Ϊ�������
		if (Lleft < Lright)
		{
			left.swap(right);
			swap(Lleft, Lright);
		}

		//���м���
		string strRes;
		strRes.resize(Lleft + 1); //���ǽ�λ��������ܽ�1λ
		strRes[0] = left[0];//ͬ����ӣ�����λһ����ͬ��
		char step = 0;		//��λ

		for (int idx = 1; idx < Lleft; idx++)
		{
			char cRes = left[Lleft - idx] + step - '0';
			if (idx < Lright)
				cRes = cRes + (right[Lright - idx] - '0');
			step = 0;
			while (cRes >= 10) //��ʮ��λ
			{
				step = 1;
				cRes -= 10;
			}
			strRes[Lleft - idx + 1] = cRes + '0';
		}
		//�������һ�εĽ�λ
		strRes[1] = step + '0';
		return strRes;
	}

	string StrSub(string left, string right)//�ַ���ͬ�������������
	{
		int Lleft = left.size();
		int Lright = right.size();
		//�Ѵ���ַ��������ַ���
		if (!IsLeftBig(left,right))
		{
			left.swap(right);
			swap(Lleft, Lright);
		}
		//���м���
		char ret = 0;//��������Ľ��
		for (int idx = 1; idx < Lleft; idx++)
		{
			char leftData = left[Lleft - idx] - '0';
			char rightData = right[Lright - idx] - '0';
			char src = left[Lleft - idx - 1];
			if (idx < Lright && leftData < rightData)//��Ҫ��β 
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
	string _strData;//�������������
	long long _value;//û�г�����Χ����
};