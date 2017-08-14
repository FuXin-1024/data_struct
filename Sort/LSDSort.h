#include<assert.h>  
#pragma once 
#include<iostream>  
using namespace std;

//MSD：由高位到低位，排低位时要排上一个位相同的元素（否则会影响上一个位的排序结果）  
//LSD：由低位到高位 

size_t GetMaxDigit(size_t *arr, size_t len)
{
	size_t digit = 1;
	size_t base = 10;

	for (size_t i = 0; i < len; i++)
	{
		while (arr[i] >= base)
		{
			base *= 10;
			digit++;
		}
	}
	return digit;
}

void LSDSort(size_t *arr, size_t len)
{
	size_t maxDigit = GetMaxDigit(arr, len);
	size_t base = 1;

	size_t *bucket = new size_t[len];
	while ((maxDigit--) > 0)
	{
		size_t counts[10] = { 0 };
		size_t start[10] = { 0 };
		start[0] = 0;

		for (size_t i = 0; i < len; i++)
		{
			size_t num = (arr[i] / base) % 10;
			counts[num]++;
		}

		for (size_t i = 1; i < 10; i++)
		{
			start[i] = start[i - 1] + counts[i - 1];
		}

		for (size_t i = 0; i < len; i++)
		{
			size_t num = (arr[i] / base) % 10;
			bucket[start[num]++] = arr[i];
		}
		memcpy(arr, bucket, sizeof(size_t)*len);
		base *= 10;
	}
}

void LSDSortTest()
{
	size_t arr[] = { 49, 38, 65, 97, 76, 13, 27, 49, 50, 77 };
	LSDSort(arr, sizeof(arr) / sizeof(arr[0]));
}