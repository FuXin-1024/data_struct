#pragma once
#include<iostream>
#include<stack>
#include<assert.h>
using namespace std;

//两个栈实现一个队列
template <class K>
class Queue
{
public:
	Queue()
	{}
	void Push(const K& x)
	{
		s1.push(x);
	}

	void Pop()
	{
		if (!s2.empty())
			s2.pop();
		else
		{	
			while (s1.size()>1)
			{
				s2.push(s1.top());
				s1.pop();
			}
			s1.pop();
		}
	}

	K front()
	{
		assert(s1.size() > 1 || s2.size() > 1);
		if (s2.empty())
		{
			while (!s1.empty())
			{
				s2.push(s1.top());
				s1.pop();
			}
		}
		return s2.top();
	}
protected:
	stack<K> s1;
	stack<K> s2;
};

void QueueTest()
{
	Queue<int> q;
	q.front();
	q.Push(1);
	q.Push(2);
	q.Push(3);
	q.Push(4);
	q.Pop();
	q.Pop();
	q.Push(5);
	q.Push(6);
	cout << q.front() << endl;
}