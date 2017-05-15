#pragma once
#include<iostream>
#include<stack>
#include<assert.h>
using namespace std;


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

//左右指针法
int PartSort1(int* a, int left, int right)
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

		while (begin<end && a[end]>=key)//找小
		{
			--end;
		}
		if (begin < end)
			swap(a[begin], a[end]);
	}
	swap(a[begin], a[right]);
	return begin;
}

//挖坑法
int PartSort2(int* a, int left, int right)
{
	assert(a);
	int key = a[right];//坑
	while (left < right)
	{
		while (left < right && a[left] <= key)
		{
			++left;
		}
		a[right] = a[left];
		while (left < right && a[right] >= key)
		{
			--right;
		}
		a[left] = a[right];
	}
	a[left] = key;
	return left;
}

//前后指针法
int PartSort3(int* a, int left, int right)
{
	assert(a);
	int mid = GetMidindex(a, left, right);//三数取中
	swap(a[mid], a[right]);

	int cur = left;
	int prev = left - 1;
	int key = a[right];
	while (cur < right)
	{
		if (a[cur] < key && ++prev != cur)
			swap(a[cur], a[prev]);
		++cur;
	}
	swap(a[++prev], a[right]);
	return prev;
}

void QuickSort(int* a, int left,int right)
{
	assert(a);
	if (left >= right)
		return;

	//小区间优化
	/*if (right - left < 4)
	{
		InsertSort(a, right - left);
	}*/
	/*else
	{
	}*/
	//int div = PartSort2(a, left, right);
	int div = PartSort3(a, left, right);

	QuickSort(a, left, div - 1);
	QuickSort(a, div + 1,right);
}

//非递归实现快速排序
void QuickSortNoR(int* a, int left, int right)
{
	stack <int> s;
	s.push(right);
	s.push(left);

	while (!s.empty())
	{
		int begin = s.top();
		s.pop();
		int end = s.top();
		s.pop();
		
		int div = PartSort3(a,begin,end);
		if (div - 1 > begin)
		{
			s.push(div - 1);
			s.push(begin);
		}
		if (div + 1 < end)
		{
			s.push(end);
			s.push(div + 1);
		}
	}
}
void QuickSorttTest()
{
	int arr[] = { 3, 1, 5, 2, 8, 7, 9, 0, 6, 4 };
	QuickSortNoR(arr, 0, sizeof(arr) / sizeof(arr[0]) - 1);
	cout << "QuickSort: ";
	for (size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}