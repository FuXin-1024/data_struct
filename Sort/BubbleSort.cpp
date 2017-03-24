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

//设置一个flag，若只经过几轮就排序好了，就不再进行循环了
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

// 进一步优化，假如数组有100个，后面90个都已排好序且都大于前面10个数字，
//那么在第一趟遍历后，最后发生交换的位置必定小于10，且这个位置之后的数据必定已经有序了，
//记录下这位置，第二次只要从数组头部遍历到这个位置就可以了。 
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