#pragma once
#include<iostream>
#include<assert.h>
using namespace std;

//Ö±½Ó²åÈëÅÅÐò
void InsertSort(int* arr, int len)
{
	assert(arr);
	assert(len > 0);
	
	for (int i = 0; i < len - 1; ++i)
	{
		int tmp = arr[i+1];
		int j = i + 1;
		while (i >= 0 && arr[i]>tmp)
		{
			arr[i+1] = arr[i];
			--i;
		}
		arr[i + 1] = tmp;
	}
}

void InsertSortTest()
{
	int arr[] = { 3, 1, 5, 2, 8, 7, 9, 0, 6, 4 };
	InsertSort(arr, sizeof(arr) / sizeof(arr[0]));
	cout << "InsertSort: ";
	for (size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}