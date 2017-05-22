#pragma once
#include<iostream>
#include<queue>
#include<assert.h>
using namespace std;

template<class T>
class Stack
{
public:
	void Push(const T& x)
	{
		if (!q1.empty())
			q1.push(x);
		else
			q2.push(x);
	}

	void Pop()
	{
		assert(q1.size() || q2.size());
		//队1为空时，把队2出最后一个元素倒入队1
		if (q1.empty())
		{
			while (q2.size() > 1)
			{
				q1.push(q2.front());
				q2.pop();
			}
			q2.pop();
		}
		else
		{
			while (q1.size() > 1)
			{
				q2.push(q1.front());
				q1.pop();
			}
			q1.pop();
		}
	}

	T top()
	{
		T tmp;
		assert(q1.size() || q2.size());
		//队1为空时，把队2出最后一个元素倒入队1
		if (q1.empty())
		{
			while (q2.size() > 1)
			{
				q1.push(q2.front());
				q2.pop();
			}
			tmp = q2.front();
			q1.push(tmp);
			q2.pop();
			return tmp;
		}
		else
		{
			while (q1.size() > 1)
			{
				q2.push(q1.front());
				q1.pop();
			}
			tmp = q1.front();
			q2.push(tmp);
			q1.pop();
			return tmp;
		}
		
	}
protected:
	queue<T> q1;
	queue<T> q2;
};

void StackTest()
{
	Stack<int> s;
	s.Push(1);
	s.Push(2);
	s.Push(3);
	cout << s.top() << endl;
	s.Pop();
	cout << s.top() << endl;
	s.Push(4);
	s.Push(5);
	cout << s.top() << endl;
	s.Pop();
	s.Pop();
	cout << s.top() << endl;
}