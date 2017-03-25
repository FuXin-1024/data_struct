#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<assert.h>
using namespace std;

//海量数据处理
//从巨大的数N中找出 最大或最小的K个数；

//找大的数，建小堆；找小的数，建大堆

//向下调整算法
void AdJustDown(int* heap, size_t k, size_t parent)
{
	size_t child = parent * 2 + 1;
	while (child < k)
	{
		if (child + 1 < k && heap[child + 1] < heap[child])
		{
			++child;
		}

		if (heap[child] < heap[parent])
		{
			swap(heap[child], heap[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}

void TopK(int* a, int n, int k)
{
	assert(n > k);
	int* heap = new int[k];
	for (size_t i = 0; i < k; ++i)
	{
		heap[i] = a[i];
	}

	//建小堆
	for (int i = (k - 2) / 2; i >= 0; --i)
	{
		AdJustDown(heap, k, i);
	}

	//k以后的数和堆顶进行比较(堆顶的数最小)，若比堆顶的数大，替换，调整
	for (size_t i = k; i < n; ++i)
	{
		if (a[i] > heap[0])
		{
			heap[0] = a[i];
			AdJustDown(heap, k, 0);
		}
	}

	//打印
	for (size_t i = 0; i < k; ++i)
	{
		cout << heap[i] << " ";
	}
	cout << endl;

	delete[] heap;
}

void Test()
{
	const int N = 1000;
	const int K = 10;

	int a[N];
	for (size_t i = 0; i < N; ++i)
	{
		a[i] = i;
	}
	a[10] = 1002;
	a[123] = 2036;
	a[147] = 7854;
	TopK(a, N, K);
}
int main()
{
	Test();
	system("pause");
	return 0;
}