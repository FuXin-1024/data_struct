#pragma once
#include<iostream>
using namespace std;

//��������
void QuickSort(int* a, int left, int right)
{
	if (left < right)
	{
		int l = left;
		int r = right;
		int x = a[l];
		while (l < r)
		{
			while (l<r && a[r]>x)//�Ӻ���ǰ�ұ�xС��Ԫ��
				r--;
			if (l < r)
				a[l++] = a[r];
			while (l < r && a[l] < x)//��ǰ��ǰ�ұ�x���Ԫ��
				l++;
			if (l < r)
				a[r--] = a[l];
		}
		//l=rʱ���˳�
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