#include<iostream>
#include<assert.h>
using namespace std;

void AdjustUp(int* a, int i, int n)//�ӵ�һ����Ҷ�ӽ�㿪ʼ����
{
	assert(a);
	int j = 2 * i + 1;
	int tmp = a[i];
	
	while (j < n)
	{

	}
}

void MakeMinHeap(int* a,int n)
{
	assert(a);
	for(int i = n / 2 - 1; i >= 0; --i)
	{
		AdjustUp(a, i, n);
	}
}