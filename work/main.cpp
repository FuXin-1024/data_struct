#include"Date.h"
#include"Calcul.h"

void Menu()
{
	cout << "###############################################################" <<endl;
	cout << "###################   ---��ӭʹ�ü�����---     ################" <<endl;
	cout << "###################    1.���ݼ�����            ################" <<endl;
	cout << "###################    2.���ڼ�����            ################" <<endl;
	cout << "###################    0.�˳�                  ################" <<endl;
	cout << "###############################################################" <<endl;
}
int main()
{	
	while (1)
	{
		Menu();
		int num = 0;
		cout << "��ѡ��";
		cin >> num;
		switch (num)
		{
		case 1:
			CalTest();
			break;
		case 2:
			DateTest();
			break;
		case 0:
			exit(1);
		default:
			cout << "����������������룡" << endl;
		}
	}
	system("pause");
	return 0;
}