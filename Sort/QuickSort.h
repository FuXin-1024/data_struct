#pragma once
#include<iostream>
using namespace std;

//快速排序
void QuickSort(int* a, int left, int right)
{
	if (left < right)
	{
		int l = left;
		int r = right;
		int x = a[l];
		while (l < r)
		{
			while (l<r && a[r]>x)//从后往前找比x小的元素
				r--;
			if (l < r)
				a[l++] = a[r];
			while (l < r && a[l] < x)//从前往前找比x大的元素
				l++;
			if (l < r)
				a[r--] = a[l];
		}
		//l=r时，退出
		a[l] = x;
		QuickSort(a, left, l - 1);
		QuickSort(a, l + 1, right);
	}
}

void QuickSorttTest()
{
	int arr[] = { 3, 1, 5, 2, 8, 7, 9, 0, 6, 4 };
	QuickSort(arr, 0,sizeof(arr) / sizeof(arr[0])-1);
	cout << "QuickSort: ";
	for (size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}