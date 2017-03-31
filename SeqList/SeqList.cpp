#define _CRT_SECURE_NO_WARNINGS 1
#include"SeqList.h"

void PrintSeqList(SeqList* seq)
{
	assert(seq);
	for (int i = 0; i < seq->size; i++)
	{
		printf("%d ", seq->array[i]);
	}
	printf("\n");
}

void InitSeqList(SeqList* seq)
{
	assert(seq);
	seq->array = (DataType*)malloc(3 * sizeof(DataType));
	assert(seq->array);

	seq->size = 0;
	seq->capacity = 3;
}

void DestorySeqList(SeqList* seq)
{
	assert(seq);
	if (seq->array)
	{
		free(seq->array);
	}
	seq->array = NULL;
	seq->size = 0;
	seq->capacity = 0;
}

void CheckCapacity(SeqList* seq)
{
	if (seq->size >= seq->capacity)
	{
		seq->array = (DataType*)realloc(seq->array, sizeof(DataType)*(seq->capacity) * 2);
		assert(seq->array);
		seq->capacity *= 2;
	}
}

void PushBack(SeqList* seq, DataType x)
{
	assert(seq);
	CheckCapacity(seq);
	seq->array[seq->size++] = x;
}

void Popback(SeqList* seq)
{
	assert(seq);
	if (seq->size <= 0)
	{
		printf("The SeqList is empty\n");
		return;
	}
	seq->size--;
}

void PushFront(SeqList* seq, DataType x)
{
	assert(seq);
	CheckCapacity(seq);
	int end = seq->size;
	while (end >= 0)
	{
		seq->array[end] = seq->array[end - 1];
		end--;
	}
	seq->size++;
	seq->array[0] = x;
}

void PopFront(SeqList* seq)
{
	assert(seq);
	if (seq->size <= 0)
	{
		printf("The SeqList is empty\n");
		return;
	}
	for (size_t i = 0; i < seq->size - 1; i++)
	{
		seq->array[i] = seq->array[i + 1];
	}
	seq->size--;
}

void Insert(SeqList* seq, size_t pos, DataType x)
{
	assert(seq);
	assert(pos > 0);
	assert(pos <= seq->size);
	CheckCapacity(seq);
	int end = seq->size;
	while (end >= pos)
	{
		seq->array[end] = seq->array[end - 1];
		end--;
	}
	seq->size++;
	seq->array[pos - 1] = x;
}

int find(SeqList* seq, DataType x)
{
	assert(seq);
	for (size_t i = 0; i < seq->size; i++)
	{
		if (seq->array[i] == x)
		{
			return i + 1;
		}
	}
	return -1;
}

void Erase(SeqList* seq, size_t pos)
{
	assert(seq);
	assert(pos > 0);
	assert(pos <= seq->size);
	if (seq->size <= 0)
	{
		printf("The SeqList is empty\n");
		return;
	}
	for (size_t i = pos - 1; i < seq->size - 1; i++)
	{
		seq->array[i] = seq->array[i + 1];
	}
	seq->size--;
}

void remove(SeqList* seq, DataType x)
{
	assert(seq);
	if (seq->size <= 0)
	{
		printf("The SeqList is empty\n");
		return;
	}
	size_t i = find(seq, x);
	if (i != -1)
	{
		Erase(seq, i);
	}
	else
		printf("The SeqList do not have %d\n", x);
}

void removeAll(SeqList* seq, DataType x)
{
	assert(seq);
	if (seq->size <= 0)
	{
		printf("The SeqList is empty\n");
		return;
	}
	int i = 0;
	int j = 0;
	int count = 0;
	for (i = 0; j < seq->size; i++)
	{
		if (seq->array[i] == x)
		{
			count++;
		}
		else
		{
			seq->array[j] = seq->array[i];
			j++;
		}
	}
	seq->size -= count;
}

void swap(int *a, int *b)
{
	int  c;
	c = *a;
	*a = *b;
	*b = c;
}

void BubbleSort(SeqList* seq)
{
	assert(seq);
	if (seq->size <= 0)
	{
		printf("The SeqList is empty\n");
		return;
	}
	for (size_t i = 0; i < seq->size; i++)
	{
		for (size_t j = i + 1; j < seq->size; j++)
		{
			if (seq->array[i]>seq->array[j])
				swap(&(seq->array[i]), &(seq->array[j]));
		}
	}
}

void SelectSort(SeqList* seq)
{
	assert(seq);
	if (seq->size <= 0)
	{
		printf("The SeqList is empty\n");
		return;
	}
	int begin = 0;
	int end = seq->size - 1;
	while (begin <= end)
	{
		int MinIndex = begin;
		int MaxIndex = end;
		for (int i = begin; i <= end; i++)
		{
			if (seq->array[i] < seq->array[MinIndex])
				MinIndex = i;
			if (seq->array[i] > seq->array[MaxIndex])
				MaxIndex = i;
		}
		swap(&(seq->array[begin]), &(seq->array[MinIndex]));
		if (MaxIndex == begin)
		{
			MaxIndex = MinIndex;
		}
		swap(&(seq->array[end]), &(seq->array[MaxIndex]));
		begin++;
		end--;
	}
}

void InsertSort(SeqList* seq)
{
	assert(seq);
	if (seq->size <= 0)
	{
		printf("The SeqList is empty\n");
		return;
	}
	for (int i = 0; i < seq->size - 1; i++)
	{
		int end = i;
		int tmp = seq->array[end + 1];
		while (end >= 0 && seq->array[end] > tmp)
		{
			seq->array[end + 1] = seq->array[end];
			end--;
		}
		seq->array[end + 1] = tmp;
	}
}
int BinarySearch(SeqList* seq, DataType x)
{
	assert(seq);
	if (seq->size <= 0)
	{
		printf("The SeqList is empty\n");
		return -1;
	}
	int begin = 0;
	int end = seq->size - 1;
	while (begin <= end)
	{
		int mid = begin + (end - begin) / 2;
		if (seq->array[mid] < x)
		{
			begin = mid + 1;
		}
		else if (seq->array[mid] > x)
		{
			end = mid - 1;
		}
		else
			return mid + 1;
	}
	return -1;
}