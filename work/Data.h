#pragma once
#include<iostream>
using namespace std;

class Data
{
public:
	Data(int year = 2017, int month = 1, int day=1)
		:_year(year)
		, _month(month)
		, _day(day)
	{
		if (month == 0 || day == 0)
		{
			cout << "���ڲ��Ϸ�" << endl;
			return;
		}
		
		while (IsIllsral(_year, _month, _day))//����������벻�Ϸ����Զ�ת��Ϊ�Ϸ�
		{
			while (_month > 12)
			{
				_month -= 12;
				_year += 1;
			}

			while (_month < 0)
			{
				_month += 12;
				_year -= 1;
			}

			while(_day > days_month(_year, _month)) 
			{
				_day = day - days_month(_year, _month);
				_month += 1;
			}
						
			while (_day < 0)
			{
				_day = days_month(year, month - 1) + day + 1;
				_month -= 1;
			}
			
		}
	}

	Data(const Data& d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._month;
	}
	bool IsIllsral(int year,int month,int day) //Υ��������
	{
		if ((year<0) ||
			(month<0 || month>12) ||
			(day<0 || day>days_month(year, month)))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool IsLeapYear(int year)//�ж��Ƿ�Ϊ����
	{
		if ((year % 4 == 0) || (year % 400 == 0) && (year % 100 != 0))
			return true;
		else
			return false;
	}

	int days_month(int  year, int month)//��Ŀ���·ݵ�����
	{
		int day[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		if (IsLeapYear(year))
		{
			day[2] = 29;
		}
		return day[month];
	}

	/*ostream& operator<<(ostream&_cout, const Date& d)
	{
		_cout << d._year << "-" << d._month << "-" << d._day;
		return _cout;
	}*/
protected:
	int _year;
	int _month;
	int _day;
};