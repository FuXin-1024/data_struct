#include<iostream>
#include<assert.h>
using namespace std;

void AdjustUp(int* a, int i, int n)//从第一个非叶子结点开始调整
{
	assert(a);
	int j = (i - 1) / 2;
	int tmp = a[i];
	
	while (j >= 0 && i != 0)
	{
		if (a[j] <= tmp)
			break;
		a[i] = a[j];
		i = j;
		j = (i - 1) / 2;
	}
	a[i] = tmp;
}

void MakeMinHeap(int* a,int n)
{
	assert(a);
	for(int i = n / 2 - 1; i >= 0; --i)
	{
		AdjustUp(a, i, n);
	}
}

void HeapSort(int* a, int len)
{
	for (int i = len - 1; i >= 1; --i)
	{
		swap(a[i], a[0]);
		AdjustUp(a, 0, i);
	}
}