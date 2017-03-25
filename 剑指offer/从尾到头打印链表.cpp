#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<stack>
using namespace std;

template<class T>
struct ListNode
{
	T _data;
	ListNode<T>* _next;

	ListNode(const T& t)
		:_data(t)
		, _next(NULL)
	{}
};

template<class T>
class List
{
	typedef ListNode<T> Node;
public:
	List()
		:_head(NULL)
	{}

	void PushBack(const T& x)
	{
		if (_head == NULL)
		{
			_head = new Node(x);
		}
		else
		{
			Node* tmp = new Node(x);
			Node* cur = _head;
			while (cur->_next != NULL)
			{
				cur = cur->_next;
			}
			cur->_next = tmp;
		}
	}

	~List()
	{
		Node* cur = _head;
		while (cur)
		{
			Node* tmp = cur;
			cur = cur->_next;
			delete tmp;
		}
		_head= NULL;
	}
	
	void Print()
	{
		Node* cur = _head;
		
		while (cur != NULL)
		{
			cout << cur->_data << " ";
			cur = cur->_next;
		}
		
		cout << endl;
	}

	////利用递归实现
	void ReversePrintR()
	{
		_ReversePrint(_head);
	}

	//利用栈实现
	void ReversePrintS()
	{
		_ReversePrintS(_head);
	}
protected:
	//利用递归实现
	void _ReversePrint(Node* head)
	{
		if (head != NULL)
		{
			if (head->_next != NULL)
			{
				_ReversePrint(head->_next);
			}
			cout << head->_data << " ";
		}
	}

	//利用栈实现
	void _ReversePrintS(Node* head)
	{
		stack<int> s;
		Node* cur = head;
		while (cur)
		{
			s.push(cur->_data);
			cur = cur->_next;
		}

		while (!s.empty())
		{
			cout << s.top() << " ";
			s.pop();
		}
		cout << endl;
	}
private:
	Node* _head;
};

void Test()
{
	List<int> t;
	t.PushBack(1);
	t.PushBack(2);
	t.PushBack(3);
	t.Print();
	t.ReversePrintR();
	cout << endl;

	t.ReversePrintS();
}

int main()
{
	Test();
	system("pause");
	return 0;
}