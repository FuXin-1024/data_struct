#include<iostream>
#include<assert.h>
using namespace std;

//升序，建大堆
void AdjustDown(int* heap, size_t n, size_t parent)
{
	size_t child = parent * 2 + 1;
	while (child < n)
	{
		if (child + 1 < n&&heap[child + 1] > heap[child])
		{
			++child;
		}

		if (heap[child] > heap[parent])
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

void HeapSort(int* a, int n)
{
	assert(a);
	int parent = (n - 2) >> 1;
	for (; parent >= 0; --parent)
	{
		AdjustDown(a, n, parent);
	}

	//堆顶与最后一个数交换，除最后一个数，调整成大堆。循环。保证每个堆的最后一个数是最大的
	for (int i = n - 1; i >= 0; --i)
	{
		swap(a[0], a[i]);
		AdjustDown(a, i, 0);
	}
}

void HeapSortTest()
{
	int arr[] = { 3, 1, 5, 2, 8, 7, 9, 0, 6, 4 };

	HeapSort(arr, sizeof(arr) / sizeof(arr[0]));
	cout << "HeaptSort: ";
	for (size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}