#pragma once
#include<iostream>
using namespace std;

//ֱ�Ӳ�������:�ѵ�i�����뵽ǰi-1�����ʵ���λ��
void InsSort(int* arr, int len)
{
	for (size_t i = 1; i < len; ++i)
	{
		int tmp = arr[i];
		int j = i - 1;
		while (j >= 0 && arr[j]>tmp)
		{
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = tmp;
	}
}


void InsSortTest()
{
	int arr[] = { 3, 1, 5, 2, 8, 7, 9, 0, 6, 4 };
	InsSort(arr, sizeof(arr) / sizeof(arr[0]));
	cout << "InsSort: ";
	for (size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}