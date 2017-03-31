#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

typedef int DataType;

typedef struct SeqList
{
	DataType* array;
	size_t size;
	size_t capacity;
}SeqLIst;


void CheckCapacity(SeqList* seq);//检查空间是否够大
void InitSeqList(SeqList* seq);//初始化顺序表
void DestorySeqList(SeqList* seq);//销毁顺序表
//增删改查
void PushBack(SeqList* seq, DataType x);//从尾部插入元素
void Popback(SeqList* seq);//从尾部删除元素

void PushFront(SeqList* seq, DataType x);//从头部插入元素
void PopFront(SeqList* seq);//从头部删除元素

void Insert(SeqList* seq, size_t pos, DataType x);//指定位置插入元素
int find(SeqList* seq, DataType x);// 寻找元素
void Erase(SeqList* seq, size_t pos);// 删除指定位置元素
void remove(SeqList* seq, DataType x);//删除元素X
void removeAll(SeqList* seq, DataType x);//删除顺序表中所有的X

void BubbleSort(SeqList* seq);//冒泡排序
void SelectSort(SeqList* seq);//选择排序
void InsertSort(SeqList* seq);//插入排序
int BinarySearch(SeqList* seq, DataType x);//二分查找
int BinarySearchD(SeqList* seq, size_t begin, size_t end, DataType x);//递归，二分查找
void PrintSeqList(SeqList* seq);//输入顺序表

void PrintSeqList(SeqList* seq);
