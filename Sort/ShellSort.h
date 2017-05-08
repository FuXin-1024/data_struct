#pragma once
#include<iostream>
#include<assert.h>
using namespace std;

void ShellSort(int* arr, int len)
{
	assert(arr);
	assert(len > 0);
	int gap =len;
	while (gap > 1)
	{
		gap = gap / 3 + 1;
		//�ӵ�һ��ĵڶ���Ԫ�ؿ�ʼ
		for (size_t i = gap; i < len; ++i)
		{
			int end = i - gap;
			int tmp = arr[i];

			//���в�������ÿһ��Ĳ�ֵΪgap
			//�Ӻ���ǰ��ÿ���һ��Ԫ�ص�ǰһ��ֵһ��С��0
			while (end >= 0)
			{
				if (arr[end]<=tmp)
					break;

				arr[end + gap] = arr[end];
				end -= gap;
			}
			arr[end + gap] = tmp;
		}
	}
}

void ShellSortTest()
{
	int arr[] = { 3, 1, 5, 2, 8, 7, 9, 0, 6, 4 };
	ShellSort(arr, sizeof(arr) / sizeof(arr[0]));
	cout << "ShellSort: ";
	for (size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}