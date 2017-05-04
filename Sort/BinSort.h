#pragma once
#include<iostream>
using namespace std;

//’€∞Î≤Â»Î≈≈–Ú
void BinSort(int* arr, int len)
{
	for (int i = 1; i < len; ++i)
	{
		int tmp = arr[i];
		int first = 0;
		int end = i - 1;
		while (first <= end)
		{
			int mid = (first + end) >> 1;
			if (arr[mid]>tmp)
				end = mid - 1;
			else
				first = mid + 1;
		}
		for (int j = i - 1; j >= first; --j)
		{
			arr[j + 1] = arr[j];
		}
		arr[first] = tmp;
	}
}
void BinSortTest()
{
	int arr[] = { 3, 1, 5, 2, 8, 7, 9, 0, 6, 4 };
	BinSort(arr, sizeof(arr) / sizeof(arr[0]));
	cout << "BinSort: ";
	for (size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}