#pragma once
#include<iostream>
#include<assert.h>
using namespace std;

//左右指针法
int GetMidindex(int* a, int left, int right)
{
	int mid = left + (right - left) / 2;
	if (a[left] < a[mid])
	{
		if (a[left]>a[right])
			return left;
		else if (a[mid] > a[right])
			return right;
		else
			return mid;
	}
	else//a[left]>a[mid]
	{
		if (a[mid] > a[right])
			return mid;
		else if (a[left] > a[right])
			return right;
		else
			return left;
	}
}
int PartSort(int* a, int left, int right)
{
	assert(a);
	int mid = GetMidindex(a, left, right);//三数取中
	swap(a[mid], a[right]);
	int key = a[right];
	int begin = left;
	int end = right;

	while (begin < end)
	{
		while (begin < end && a[begin] <= key)//找大
		{
			++begin;
		}

		while (begin<end && a[end]>key)//找小
		{
			--end;
		}
		if (begin < end)
			swap(a[begin], a[end]);
	}
	swap(a[begin], a[right]);
	return begin;
}

void QuickSort(int* a, int left,int right)
{
	assert(a);
	if (left >= right)
		return;
	int div = PartSort(a, left, right);

	QuickSort(a, left, div - 1);
	QuickSort(a, div + 1,right);
}

void QuickSorttTest()
{
	int arr[] = { 3, 1, 5, 2, 8, 7, 9, 0, 6, 4 };
	QuickSort(arr, 0, sizeof(arr) / sizeof(arr[0]) - 1);
	cout << "QuickSort: ";
	for (size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}