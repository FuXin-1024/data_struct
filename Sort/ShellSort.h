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
		//从第一组的第二个元素开始
		for (size_t i = gap; i < len; ++i)
		{
			int end = i - gap;
			int tmp = arr[i];

			//进行插入排序，每一组的差值为gap
			//从后向前，每组第一个元素的前一个值一定小于0
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