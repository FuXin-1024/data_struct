#pragma once
#include<iostream>
#include<assert.h>
using namespace std;

void SelectSort(int* arr, int len)
{
	assert(arr);
	assert(len);
	for (size_t i = 0; i < len - 1; ++i)
	{
		for (size_t j = i + 1; j < len; ++j)
		{
			if (arr[i]>arr[j])
				swap(arr[i], arr[j]);
		}
	}
}

void SelectSortTest()
{
	int arr[] = { 3, 1, 5, 2, 8, 7, 8,2,1,9, 0, 6, 4 };
	int arr1[] = { 3, 3, 2 };

	SelectSort(arr, sizeof(arr) / sizeof(arr[0]));
	cout << "SelectSort: ";
	for (size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}