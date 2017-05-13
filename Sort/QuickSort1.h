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