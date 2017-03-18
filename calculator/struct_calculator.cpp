#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<stack>
#include<assert.h>
using namespace std;

enum Type
{
	OP_SYMBOL,//操作符
	OP_NUM,// 操作数
	ADD,//加
	SUB,//减
	MUL, //乘
	DIV,// 除
};

struct Cell
{
	Type _type;
	int _value;
};


int CountRPN(Cell* RPN, size_t n)
{
	stack<int > s;
	for (size_t i = 0; i < n; ++i)
	{
		if (RPN[i]._type == OP_NUM)
		{
			s.push(RPN[i]._value);
		}
		else if (RPN[i]._type == OP_SYMBOL)
		{
			int right = s.top();
			s.pop();
			int left = s.top();
			s.pop();
			switch (RPN[i]._value)
			{
			case ADD:
				s.push(left + right);
				break;
			case SUB:
				s.push(left - right);
				break;
			case MUL:
				s.push(left * right);
				break;
			case DIV:
				assert(right);
				s.push(left / right);
				break;
			default:
				assert(false);
				break;
			}
		}
		else
		{
			cout << "输入错误" << endl;
			assert(false);
		}
	}
	return s.top();
}
void Test()
{
	Cell RNP[] =
	{
		{ OP_NUM, 12 },
		{ OP_NUM, 3 },
		{ OP_NUM, 4 },
		{ OP_SYMBOL, ADD },
		{ OP_SYMBOL, MUL },
		{ OP_NUM, 6 },
		{ OP_SYMBOL, SUB },
		{ OP_NUM, 8 },
		{ OP_NUM, 2 },
		{ OP_SYMBOL, DIV },
		{ OP_SYMBOL, ADD }
	};
	cout << "运算结果:" << CountRPN(RNP, sizeof(RNP) / sizeof(Cell)) << endl;
}
int main()
{
	Test();
	system("pause");
	return 0;
}