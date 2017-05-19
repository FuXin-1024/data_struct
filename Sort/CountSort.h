#pragma once 
#include<iostream>
using namespace std;
#include<assert.h>
#include<memory.h>
#include<string.h>

void CountSort(int* a, int n)
{
	assert(a);
	int min = a[0];
	int max = a[0];

	for (int i = 1; i < n; ++i)
	{
		if (a[i] > max)
			max = a[i];
		if (a[i] < min)
			min = a[i];
	}
	int range = max - min + 1;
	int* counts = new int(range);
	memset(counts, 0, sizeof(int)*range);

	for (int i = 0; i < n; ++i)
	{
		counts[a[i] - min]++;
	}

	int j = 0;
	for (int i = 0; i < range; ++i)
	{
		while (counts[i]--)
			a[j++] = i + min;
	}
}

void CountSortTest()
{
	int arr[] = { 3, 1, 5, 2, 8, 7, 9, 0, 6, 4 };
	CountSort(arr, sizeof(arr) / sizeof(arr[0]));
	cout << "CountSort: ";
	for (size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}