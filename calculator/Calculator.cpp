#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<stack>

using namespace std;
// 首先把中缀表达式转化为后缀表达式

//定义优先级
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
//将中缀表达式变为后缀表达式
// 借助一个栈S 用来存放操作符
//一个数组用来存放后缀表达式
void  Tonibolan(char* ch, char* arr)
{
	stack <char> s; // 借助一个栈S 用来存放操作符
	int i = 0;
	while (*ch != '\0')
	{
		if (*ch >='0'&&*ch<='9')
		{
			arr[i++] = *ch;
		}
		else if (*ch=='(') // 左括号直接入栈
		{
			s.push(*ch);
		}
		else if (*ch == ')')  // 右括号从操作符栈弹出操作符，直到弹出‘）';
		{
			while (s.top() != '(')
			{
				arr[i++] = s.top();// 把操作符弹出到存有后缀表达式的数组里
				s.pop();
			}
			if (s.top() == '(')
			{
				s.pop();  //后缀表达式没有'('  ,   ')'
			}
		}

		// 存有操作符的栈为空或者 取出来的操作符的优先级 大于 栈顶操作符的优先级 直接入栈
		else if (s.empty() || Priority(*ch) > Priority(s.top()))
		{
			s.push(*ch);
		}

		// 取出来的操作符A   优先级小于等于操作符栈   栈顶的优先级。
		//把栈顶的操作符Pop出栈，放到后缀表达式的数组里，直到A的优先级大于栈顶 操作符的优先级 ，A入操作符栈
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

//计算后缀表达式
//遍历储存后缀表达式的列表，将元素依次进栈，当遇到操作符时，
//连续出栈两个元素，进行运算，再将结果进栈，最后栈内留下的元素就是计算结果
int Calcval(char* ret)
{
	stack<char> st;
	//遍历后缀表达式
	while (*ret != '\0')  
	{
		if (*ret >= '0'&&*ret <='9')  //若果是数字直接入栈
		{
			st.push(*ret);
		}
		else
		{
			//遇到操作符，连续出栈两个元素，进行运算，在将结果入栈
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
						   cout << "除数不能为0！" << endl;
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
	return st.top() - '0';     //栈里面的数据就是最后的结果
}

void Test()
{
	char ret[100] = { 0 };
	char arr[100] = { 0 };
	cout << "请输入要计算的表达式：" << endl;
	cin.get(arr, 100);

	Tonibolan(arr, ret);

	int len = strlen(ret);
	int i = 0;
	cout << "算式的逆波兰表达式为：" << endl;
	while (len--)
	{
		cout << ret[i++]<<" ";
	}
	cout << "\n算式的计算结果为：" << endl;
	cout << Calcval(ret) << endl;
}
	int main()
	{
		Test();
		system("pause");
		return 0;
	}