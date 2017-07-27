#include"Date.h"
#include"Calcul.h"

void Menu()
{
	cout << "###############################################################" <<endl;
	cout << "###################   ---欢迎使用计算器---     ################" <<endl;
	cout << "###################    1.数据计算器            ################" <<endl;
	cout << "###################    2.日期计算器            ################" <<endl;
	cout << "###################    0.退出                  ################" <<endl;
	cout << "###############################################################" <<endl;
}
int main()
{	
	while (1)
	{
		Menu();
		int num = 0;
		cout << "请选择：";
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
			cout << "输入错误！请重新输入！" << endl;
		}
	}
	system("pause");
	return 0;
}