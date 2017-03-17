#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<stack>

using namespace std;
// ���Ȱ���׺���ʽת��Ϊ��׺���ʽ

//�������ȼ�
int Priority(char ch)
{
	int i = 0;
	switch (ch)
	{
	case'(':
	{
			   i = 1;
			   break;
	}

	case'+':
	{
			   i = 2;
			   break;
	}

	case'-':
	{
			   i = 2;
			   break;
	}

	case'*':
	{
			   i = 3;
			   break;
	}

	case'/':
	{
			   i = 3;
			   break;
	}

	case')':
	{
			   i = 4;
			   break;
	}
	default:
	{
			   i = -1;
			   break;
	}
	}
	return i;
}
//����׺���ʽ��Ϊ��׺���ʽ
// ����һ��ջS ������Ų�����
//һ������������ź�׺���ʽ
void  Tonibolan(char* ch, char* arr)
{
	stack <char> s; // ����һ��ջS ������Ų�����
	int i = 0;
	while (*ch != '\0')
	{
		if (*ch >='0'&&*ch<='9')
		{
			arr[i++] = *ch;
		}
		else if (*ch=='(') // ������ֱ����ջ
		{
			s.push(*ch);
		}
		else if (*ch == ')')  // �����ŴӲ�����ջ������������ֱ����������';
		{
			while (s.top() != '(')
			{
				arr[i++] = s.top();// �Ѳ��������������к�׺���ʽ��������
				s.pop();
			}
			if (s.top() == '(')
			{
				s.pop();  //��׺���ʽû��'('  ,   ')'
			}
		}

		// ���в�������ջΪ�ջ��� ȡ�����Ĳ����������ȼ� ���� ջ�������������ȼ� ֱ����ջ
		else if (s.empty() || Priority(*ch) > Priority(s.top()))
		{
			s.push(*ch);
		}

		// ȡ�����Ĳ�����A   ���ȼ�С�ڵ��ڲ�����ջ   ջ�������ȼ���
		//��ջ���Ĳ�����Pop��ջ���ŵ���׺���ʽ�������ֱ��A�����ȼ�����ջ�� �����������ȼ� ��A�������ջ
		else
		{
			while (Priority(*ch) <= Priority(s.top()))
			{
				arr[i++] = s.top();
				s.pop();
				if (s.empty())
				{
					break;
				}
			}
			s.push(*ch);
		}
		++ch;
	}
	while (!s.empty())
	{
		arr[i++] = s.top();
		s.pop();
	}
}

//�����׺���ʽ
//���������׺���ʽ���б���Ԫ�����ν�ջ��������������ʱ��
//������ջ����Ԫ�أ��������㣬�ٽ������ջ�����ջ�����µ�Ԫ�ؾ��Ǽ�����
int Calcval(char* ret)
{
	stack<char> st;
	//������׺���ʽ
	while (*ret != '\0')  
	{
		if (*ret >= '0'&&*ret <='9')  //����������ֱ����ջ
		{
			st.push(*ret);
		}
		else
		{
			//������������������ջ����Ԫ�أ��������㣬�ڽ������ջ
			switch (*ret)
			{
			case'+':
			{
					   char a = st.top();
					   st.pop();
					   char b = st.top();
					   st.pop();
					   st.push(((a - '0') + (b - '0')) + '0');
					   break;
			}

			case'-':
			{

					   char a = st.top();
					   st.pop();
					   char b = st.top();
					   st.pop();
					   st.push(((b - '0') - (a - '0')) + '0');
					   break;
			}

			case'*':
			{

					   char a = st.top();
					   st.pop();
					   char b = st.top();
					   st.pop();
					   st.push(((b - '0') * (a - '0')) + '0');
					   break;
			}

			case'/':
				{
					   char a = st.top();
					   st.pop();
					   char b = st.top();
					   st.pop();
					   if (a != '0')
					   {
						   st.push(((b - '0') / (a - '0')) + '0');
					   }
					   else
					   {
						   cout << "��������Ϊ0��" << endl;
					   }
					   break;
				}
			default:
				{
					break;
				}
			}
		}
		++ret;
	}
	return st.top() - '0';     //ջ��������ݾ������Ľ��
}

void Test()
{
	char ret[100] = { 0 };
	char arr[100] = { 0 };
	cout << "������Ҫ����ı��ʽ��" << endl;
	cin.get(arr, 100);

	Tonibolan(arr, ret);

	int len = strlen(ret);
	int i = 0;
	cout << "��ʽ���沨�����ʽΪ��" << endl;
	while (len--)
	{
		cout << ret[i++]<<" ";
	}
	cout << "\n��ʽ�ļ�����Ϊ��" << endl;
	cout << Calcval(ret) << endl;
}
	int main()
	{
		Test();
		system("pause");
		return 0;
	}