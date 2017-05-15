#pragma once
#include<iostream>
#include<assert.h>
using namespace std;

void _MergeSort(int* src, int* dst, int left, int right)
{
	if (left >= right)
		return;
	int mid = left + (right - left) / 2;
	//[left,mid],[mid+1,right],¹é²¢Ç°ÓÐÐò
	_MergeSort(src,dst, left, mid);
	_MergeSort(src,dst, mid+1,right);

	int begin1 = left; int begin2 = mid + 1;
	int index = 0;

	while (begin1 <= mid && begin2 <= right)
	{
		if (src[begin1] < src[begin2])
			dst[index++] = src[begin1++];
		else
			dst[index++] = src[begin2++];
	}

	while (begin1 <= mid)
		dst[index++] = src[begin1++];
	while (begin2 < right)
		dst[index++] = src[begin2++];

	int i = 0; int j = left;
	while (i < index)
		src[j++] = dst[i++];
}

void MergeSort(int* a, int n)
{
	assert(a);
	int* tmp = new int[n];
	_MergeSort(a, tmp, 0, n - 1);
}