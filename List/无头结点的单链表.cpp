#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<assert.h>
using namespace std;

//不带头结点的链表(含有指向头结点和尾节点的指针)
template<class	T>
struct ListNode
{
	T _data;
	ListNode* _next;

	ListNode(const T& x)
		:_data(x)
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
		, _tail(NULL)
	{}

	List(const List& s)
		:_head(NULL)
		, _tail(NULL)
	{
		Node* cur = s._head;
		while (cur)
		{
			if (_head == NULL)
			{
				_head = _tail = new Node(cur->_data);
			}
			else
			{
				_tail->_next = new Node(cur->_data);
				cur = cur->_next;
			}
			cur = cur->_next;
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
		_head = _tail = NULL;
	}

	void PushBack(const T& x) //尾插
	{
		if (_head == NULL)
		{
			_head = _tail = new Node(x);
		}
		else
		{
			_tail->_next = new Node(x);
			_tail = _tail->_next;
		}
	}

	void PopBack() //尾删
	{
		if (_head == NULL)
		{
			return;
		}
		else if (_head->_next==NULL)
		{
			delete _head;
			_head = _tail = NULL;
		}
		else
		{
			Node* prev=_head;
			while (prev->_next != _tail)
			{
				prev = prev->_next;
			}
			_tail = NULL;
			_tail = prev;
			_tail->_next = NULL;
		}
	}

	void PushFront(const T& x)//头插
	{
		if (_head == NULL)
		{
			_head = _tail = new Node(x);
		}
		else
		{
			Node* tmp = new Node(x);
			tmp->_next = _head;
			_head = tmp;
		}
	}

	void PopFront()
	{
		if (_head == NULL)
		{
			return;
		}
		else if (_head->_next == NULL)
		{
			delete _head;
			_head = _tail = NULL;
		}
		else
		{
			Node* cur = _head->_next;
			delete _head;
			_head = cur;
		}
	}

	Node* Find(const T& x)
	{
		Node* cur = _head;
		while (cur)
		{
			if (cur->_data == x)
			{
				return cur;
			}
			cur = cur->_next;
		}
		return (Node*) -1;
	}

	void Insert(Node* pos, const T& x)
	{
		assert(pos);

	}

	void Print()
	{
		Node* cur = _head;
		while (cur)
		{
			cout << cur->_data << " ";
			cur = cur->_next;
		}
		cout << endl;
	}
private:
	Node* _head;
	Node* _tail;
};

void Test()
{
	List<int> t;
	t.PushBack(1);
	t.PushBack(2);
	t.PushBack(3);
	t.PushBack(4);
	t.Print();

	/*t.PopBack();
	t.Print();*/
	t.PushFront(0);
	t.Print();

	t.PopFront();
	t.Print();
}
int main()
{
	Test();
	system("pause");
	return 0;
}