#define _CRT_SECURE_NO_WARNINGS 1
#include"telephone.h"
void Menu(){
	printf("********************************\n");
	printf("************1.���**************\n");
	printf("************2.ɾ��**************\n");
	printf("************3.��ʾ**************\n");
	printf("************4.�޸�**************\n");
	printf("************0.�˳�**************\n");
	printf("********************************\n");
}
void Exit(Pbook *book){
	exit(0);
}
int main(){
	Pbook my_pbook = { 0 };
	void(*table[5])(Pbook *book) = { AddPbook, DelPbook, ShowPbook, MulPbook, Exit };
	int op = 0;
	InitPbook(&my_pbook);
	do{
		Menu();
		printf("���������:>");
		scanf("%d", &op);
		if (op == 0)
			break;
		table[op - 1](&my_pbook);
	} while (1);
	SavePbook(&my_pbook);
	return 0;
}




void InitPbook(Pbook *book){
	book->info = (Pinfo *)malloc(sizeof(Pinfo)*DEFAULT_SZ);
	memset(book->info, 0, sizeof(sizeof(Pinfo)*DEFAULT_SZ));
	book->length = 0;
	book->sz = DEFAULT_SZ;
	LoadPbook(book);
}
void AddPbook(Pbook *book){
	IsFull(book);
	printf("����:>");
	scanf("%s", book->info[book->length].name);
	printf("�Ա�:>");
	scanf("%s", book->info[book->length].sex);
	printf("�ֻ�����:>");
	scanf("%s", book->info[book->length].number);
	printf("��ͥסַ:>");
	scanf("%s", book->info[book->length].addr);
	book->length++;
	printf("��ӳɹ�!\n");
}
void IsFull(Pbook *book){
	if (book->length == book->sz){
		Pinfo *tmp = (Pinfo *)realloc(book->info, sizeof(book->info) + sizeof(book->info)*INCREASE_SZ);
		if (!tmp){
			perror("realloc");
			system("pause");
			exit(1);
		}
		book->info = tmp;
	}
}
void DelPbook(Pbook *book){
	int i = 0;
	int pos = 0;
	char name[10] = { 0 };
	printf("����:>");
	scanf("%s", name);
	for (i = 0; i<book->length; i++){
		if (strcmp(book->info[i].name, name) == 0){
			pos = i;
			break;
		}
	}
	for (i = pos; i<book->length - 1; i++){
		book->info[i] = book->info[i + 1];
	}
	book->length--;
	printf("ɾ���ɹ�!\n");
}
void MulPbook(Pbook *book){
	int i = 0;
	int pos = 0;
	char name[10] = { 0 };
	printf("���������:>");
	scanf("%s", name);
	for (i = 0; i<book->length; i++){
		if (strcmp(book->info[i].name, name) == 0){
			pos = i;
			break;
		}
	}
	printf("������:>");
	scanf("%s", book->info[pos].name);
	printf("���Ա�:>");
	scanf("%s", book->info[pos].sex);
	printf("���ֻ�����:>");
	scanf("%s", book->info[pos].number);
	printf("�¼�ͥסַ:>");
	scanf("%s", book->info[pos].addr);
	printf("�޸ĳɹ�!\n");
}
void ShowPbook(Pbook *book){
	int i = 0;
	printf("����\t�Ա�\t�ֻ�����\t��ͥסַ\n");
	for (i = 0; i<book->length; i++){
		printf("%s\t%s\t%s\t%s\n",
			book->info[i].name,
			book->info[i].sex,
			book->info[i].number,
			book->info[i].addr);
	}
}
void LoadPbook(Pbook *book){
	FILE *fp = fopen(FILENAME, "r");
	Pinfo tmp = { 0 };
	if (!fp){
		perror(FILENAME);
		system("pause");
		exit(1);
	}
	while (fread(&tmp, sizeof(Pinfo), 1, fp)){
		IsFull(book);
		book->info[book->length] = tmp;
		book->length++;
	}
	fclose(fp);
}
void SavePbook(Pbook *book){
	int i = 0;
	FILE *fp = fopen(FILENAME, "w");
	if (!fp){
		perror(FILENAME);
		system("pause");
		exit(1);
	}
	for (i = 0; i<book->length; i++){
		fwrite(&book->info[i], sizeof(Pinfo), 1, fp);
	}
	fclose(fp);
}