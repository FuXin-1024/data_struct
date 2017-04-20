#define _CRT_SECURE_NO_WARNINGS 1

#ifndef __HEAD_H__
#define __HEAD_H__
#define DEFAULT_SZ 3
#define INCREASE_SZ 2
#define FILENAME "telephone.txt"
#define _CRT_SECURE_NO_WARNINGS 0
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
typedef struct Pinfo{
	char name[10];
	char sex[5];
	char number[12];
	char addr[20];
}Pinfo;
typedef struct phone_book{
	Pinfo *info;
	int length;
	int sz;
}Pbook;

void InitPbook(Pbook *book);
void AddPbook(Pbook *book);
void IsFull(Pbook *book);
void DelPbook(Pbook *book);
void MulPbook(Pbook *book);
void ShowPbook(Pbook *book);
void LoadPbook(Pbook *book);
void SavePbook(Pbook *book);
#endif