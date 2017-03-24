#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<assert.h>
using namespace std;

void BubbleSort1(int* a, int n)
{
	assert(a);
	for (size_t i = n; i > 0; --i)
	{
		for (size_t j = 1; j < i; ++j)
		{
			if (a[j - 1] > a[j])
			{
				swap(a[j - 1], a[j]);
			}
		}
	}

	for (size_t i = 0; i < n; ++i)
	{
		cout << a[i] << " ";
	}
	cout << endl;
	
}

//����һ��flag����ֻ�������־�������ˣ��Ͳ��ٽ���ѭ����
void BubbleSort2(int* a, int n)
{
	assert(a);
	bool flag = 1;
	for (size_t i = n; flag; --i)
	{
		flag = 0;
		for (size_t j = 1; j < i; ++j)
		{
			if (a[j - 1] > a[j])
			{
				swap(a[j - 1], a[j]);
				flag = 1;
			}
		}
	}

	for (size_t i = 0; i < n; ++i)
	{
		cout << a[i] << " ";
	}
	cout << endl;

}

// ��һ���Ż�������������100��������90�������ź����Ҷ�����ǰ��10�����֣�
//��ô�ڵ�һ�˱����������������λ�ñض�С��10�������λ��֮������ݱض��Ѿ������ˣ�
//��¼����λ�ã��ڶ���ֻҪ������ͷ�����������λ�þͿ����ˡ� 
void BubbleSort3(int *a, int n)
{
	int flag = n;
	for (int i; flag;)
	{
		i = flag;
		flag = 0;
		for (int j = 1; j<i; j++)
		{
			if (a[j - 1]>a[j])
			{
				swap(a[j - 1], a[j]);
				flag = j;
			}
		}
	}

	for (size_t i = 0; i < n; ++i)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}
void Test()
{
	int a[] = { 1, 4,0, 12, 43, 3, 13, 44, 80 };
	int len = sizeof(a) / sizeof(a[0]);
	BubbleSort3(a, len);
}

int main()
{
	Test();
	system("pause");
	return 0;
}