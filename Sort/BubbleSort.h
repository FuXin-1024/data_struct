#pragma once
#include<iostream>
using namespace std;

void SubbleSort(int* arr, int len)
{
	for (int i = 0; i < len; ++i)
	{
		for (int j = 1; j < len - i; j++)
		{
			if (arr[j - 1]>arr[j])
				swap(arr[j - 1], arr[j]);
		}
	}
}

void SubbleSort1(int* arr, int len)
{
	bool flag = true;
	int n = len;
	while (flag)
	{
		flag = false;
		for (int j = 1; j < n; j++)
		{
			if (arr[j - 1]>arr[j])
				swap(arr[j - 1], arr[j]);
			flag = true;
		}
		n--;
	}
}
void SubbleSortTest()
{
	int arr[] = { 3, 1, 5, 2, 8, 7, 9, 0, 6, 4 };
	SubbleSort1(arr, sizeof(arr) / sizeof(arr[0]));
	cout << "SubbleSort: ";
	for (size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}