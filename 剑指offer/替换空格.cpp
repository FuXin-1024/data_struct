#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<assert.h>

using namespace std;

 //��ʵ��һ�����������ַ����е�ÿ���ո��滻��%20.����
//����"We are happy." ���"we are%20are%20happy."��
char* ReplaceBlank(char* str)
{
	assert(str);
	int count = 0;  // ͳ�ƿո�ĸ���
	char* front_ptr = str;
	while (*front_ptr != '\0')
	{
		if (*front_ptr == ' ')
		{
			++count;
		}
		++front_ptr;// front_ptrָ��ԭ�����ĩβ->'\0'
	}

	//�滻�������βָ��
	char* back_ptr = front_ptr + count*(3 - 1);   // һ���ո������������ַ�
	//��ʼ���дӺ���ǰ����
	while (back_ptr > front_ptr)
	{
		//�����ո��滻��%20.   front_ptr��ǰ��һ����back_ptr��ǰ������
		if (*front_ptr == ' ')
		{
			*back_ptr-- = '0'; 
			*back_ptr-- = '2';
			*back_ptr-- = '%';
			--front_ptr;
		}
		else
		{
			//û�����ո����θ���
			*back_ptr-- = *front_ptr--;
		}
	}
	return str;
}

void Test()
{
	char str1[50]="We are happy.";
	cout << ReplaceBlank(str1) << endl;
	char str2[50] = " We are happy.";
	cout << ReplaceBlank(str2) << endl;
	char str3[50] = " We are happy. ";
	cout << ReplaceBlank(str3) << endl;
	char str4[50] = "We  are happy.";
	cout << ReplaceBlank(str4) << endl;
	char str5[50] = "      ";
	cout << ReplaceBlank(str5) << endl;
	char str6[50] = "Wearehappy.";
	cout << ReplaceBlank(str6) << endl;
	char* str7 = NULL;
	cout << ReplaceBlank(str7) << endl;
}
int main()
{
	Test();
	system("pause");
	return 0;	
}