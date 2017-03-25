#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<assert.h>
using namespace std;

//�������ݴ���
//�Ӿ޴����N���ҳ� ������С��K������

//�Ҵ��������С�ѣ���С�����������

//���µ����㷨
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

	//��С��
	for (int i = (k - 2) / 2; i >= 0; --i)
	{
		AdJustDown(heap, k, i);
	}

	//k�Ժ�����ͶѶ����бȽ�(�Ѷ�������С)�����ȶѶ��������滻������
	for (size_t i = k; i < n; ++i)
	{
		if (a[i] > heap[0])
		{
			heap[0] = a[i];
			AdJustDown(heap, k, 0);
		}
	}

	//��ӡ
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