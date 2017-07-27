#pragma once
#include<iostream>
using namespace std;

class Date
{
public:
	Date(int year = 2017, int month = 1, int day=1)
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
			ChangeDate();
			/*while (_month > 12)
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
			*/
		}
	}

	Date(const Date& d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}

	Date& operator=(const Date& d)
	{
		if (this != &d)
		{
			_year = d._year;
			_month = d._month;
			_day = d._day;
		}
		return *this;
	}
	Date& operator+(int day)
	{
		_day = _day + day;

		while (IsIllsral(_year, _month, _day))//������ڲ��Ϸ����Զ�ת��Ϊ�Ϸ�
		{
			ChangeDate();
		}
		return *this;
	}

	Date& operator++(int)
	{
		++_day;
		while (IsIllsral(_year, _month, _day))//������ڲ��Ϸ����Զ�ת��Ϊ�Ϸ�
		{
			ChangeDate();
		}
		return *this;
	}

	Date& operator++()
	{
		++_day;
		while (IsIllsral(_year, _month, _day))//������ڲ��Ϸ����Զ�ת��Ϊ�Ϸ�
		{
			ChangeDate();
		}
		return *this;
	}

	Date& operator-(int day)
	{
		_day = _day - day;

		while (IsIllsral(_year, _month, _day))//������ڲ��Ϸ����Զ�ת��Ϊ�Ϸ�
		{
			ChangeDate();
		}
		return *this;
	}

	int operator-(Date& d)
	{
		Date min(*this);
		Date max(d);
		int tag = -1;
		int count = 0;
		if (d < *this)
		{
			min = d;
			max = *this;
			tag = 1;
		}
		while (min != max)
		{
			++min;
			count++;
		}
		return tag*count;
	}

	Date& operator--()
	{
		_day--;
		while (IsIllsral(_year, _month, _day))//������ڲ��Ϸ����Զ�ת��Ϊ�Ϸ�
		{
			ChangeDate();
		}
		return *this;
	}

	Date& operator--(int)
	{
		_day--;
		while (IsIllsral(_year, _month, _day))//������ڲ��Ϸ����Զ�ת��Ϊ�Ϸ�
		{
			ChangeDate();
		}
		return *this;
	}

	bool operator>(const Date d)
	{
		if (_year > d._year)
		{
			return true;
		}
		else if (_year == d._year)
		{
			if (_month > d._month)
			{
				return true;
			}
			else if (_month == d._month)
			{
				if (_day > d._day)
				{
					return true;
				}
			}
		}
		return false;
	}

	bool operator<(const Date d)
	{
		if (_year < d._year)
			return true;
		else if (_year > d._year)
			return false;
		else
		{
			if (_month < d._month)
				return true;
			else if (_month > d._month)
				return false;
			else
			{
				if (_day<d._day)
					return true;
				else
					return false;
			}
		}
	}

	bool operator>=(const Date d)
	{
		if (_year >= d._year)
			return true;
		else if (_month >= d._month)
			return false;
		else
		{
			if (_month >= d._month)
				return true;
			else if (_month <= d._month)
				return false;
			else
			{
				if (_day >= d._day)
					return true;
				else
					return false;
			}
		}
	}

	bool operator<=(const Date d)
	{
		if (_year <= d._year)
			return true;
		else if (_month <= d._month)
			return false;
		else
		{
			if (_month <= d._month)
				return true;
			else if (_month <= d._month)
				return false;
			else
			{
				if (_day <= d._day)
					return true;
				else
					return false;
			}
		}
	}

	bool operator==(const Date d)
	{
		if ((_year == d._year) && (_month == d._month) && (_day == d._day))
			return true;
		else
			return false;
	}

	bool operator!=(const Date d)
	{
		if (*this == d)
			return false;
		else
			return true;
	}

	void PrintDate(int year, int month)//��ӡ����
	{
		cout << year << "��" << month << "��" << endl;
		cout << "�� " << "һ " << "�� " << "�� " << "�� " << "�� " << "�� " << endl;
		int i = 0;
		int j = 0;
		Date temp(year, month, 1);
		int week = WeekFirstDay(year, month);
		int day = temp.days_month(year, month);
		int k = 1;

		for (i = 0; i < week; i++)
		{
			cout << "   ";
		}
		for (i = 0; i < 6; i++)
		{
			for (j = 0; j < 7; j++)
			{
				if (i == 0)
				{
					if (j == 7 - week)
						break;
				}
				if (k <= day)
					printf("%2d ", k++);
			}
			cout << endl;
		}
	}

protected:
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

	void ChangeDate()
	{
		while (_month > 12)
		{
			_month -= 12;
			_year += 1;
		}

		while (_month <= 0)
		{
			_month += 12;
			_year -= 1;
		}

		while (_day > days_month(_year, _month))
		{
			_day = _day - days_month(_year, _month);
			_month += 1;
		}

		while (_day <= 0)
		{
			_day = days_month(_year, _month - 1) + _day + 1;
			_month -= 1;
		}
	}
	bool IsLeapYear(int year)//�ж��Ƿ�Ϊ����
	{
		if ((year % 4 == 0) || (year % 400 == 0) && (year % 100 != 0))
			return true;
		else
			return false;
	}

	public:
	int days_month(int  year, int month)//��Ŀ���·ݵ�����
	{
		int day[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		if (IsLeapYear(year))
		{
			day[2] = 29;
		}
		return day[month];
	}

	int WeekFirstDay(int year, int month)
	{
		Date d1(1949, 9, 1);//���й���1949�꿪ʼʹ�ù�Ԫ���귨
		int week = 4;//��Ԫ1949��9��1��Ϊ����
		int day = 0;
		Date d2(year, month, 1);
		day = d2 - d1;
		week += day % 7;
		if (week > 7)
		{
			week -= 7;
		}
		return week;
	}
	friend ostream& operator<<(ostream&_cout, const Date& d)
	{
		_cout << d._year << "-" << d._month << "-" << d._day;
		return _cout;
	}

	friend istream& operator>>(istream&_cin, Date& d)
	{
		_cin >> d._year >> d._month >> d._day;
		return _cin;
	}
protected:
	int _year;
	int _month;
	int _day;
};


void menu()
{
	cout << "####  ---����������е���������---  ####" << endl;
	cout << "#### 1.��ӡĿ���·���������ʽ���� �£�####" << endl;
	cout << "#### 2.�����������  #####################" << endl;
	cout << "#### 3.��������(�����ǰ�ƽ�) ##########" << endl;
	cout << "#### 0.�˳�###############################" << endl;

}
void DateTest()
{
	menu();
	while (1)
	{
		int num = 0;
		cin >> num;

		switch (num)
		{
		case 1:
		{
				  cout << "����������·�:";
				  int year = 0, month = 0;
				  Date d;
				  cin >> year;
				  cin >> month;
				  d.PrintDate(year, month);
				  break;
		}
		case 2:
		{
				  cout << "����������1��";
				  Date d1;
				  cin >> d1;

				  cout << "����������2��";
				  Date d2;
				  cin >> d2;

				  int day = 0;
				  day = d1 - d2;
				  cout << "����������1-����2����" << day << "��" << endl;
				  break;
		}

		case 3:
		{
				  cout << "���������ڣ�";
				  Date d1, d2;
				  cin >> d1;

				  cout << "�����������������";
				  int n = 0;
				  cin >> n;

				  cout << "���������Ϊ��";
				  if (n > 0)
				  {
					  d2 = d1 + n;
				  }
				  else
				  {
					  d2 = d1 - (-n);
				  }
				  cout << d2;
				  break;
		}
		case 0:
			return;
		}
	}
}