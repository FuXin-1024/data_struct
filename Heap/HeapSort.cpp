#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<assert.h>
using namespace std;

//���򣬽����
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
		AdjustDown(a, n,parent);
	}

	//�Ѷ������һ���������������һ�����������ɴ�ѡ�ѭ������֤ÿ���ѵ����һ����������
	for (int i = n - 1; i >= 0; --i)
	{
		swap(a[0], a[i]);
		AdjustDown(a, i, 0);
	}
}

void Print(int* a,int n)
{
	assert(a);
	for (size_t i = 0; i < n; ++i)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}
void Test()
{
	int a[] = { 10, 21, 13, 12, 3, 18, 15, 17, 14, 19 };
	int n = sizeof(a) / sizeof(a[0]);
	HeapSort(a, n);
	Print(a,n);
}
int main()
{
	Test();
	system("pause");
	return 0;
}