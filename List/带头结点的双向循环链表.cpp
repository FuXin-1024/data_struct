#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<assert.h>
using namespace std;

template<class T>
struct ListNode
{
	T _data;
	ListNode* _prev;
	ListNode* _next;

	ListNode(const T& x=T())
		:_data(x)
		, _prev(NULL)
		, _next(NULL)
	{}
};

template <class T>
class List
{
	typedef ListNode<T> Node;
public:
	List()
	{
		_head = new Node;
		_head->_next = _head;
		_head->_prev = _head;
	}

	//s1(s2)
	List(const List<T>& l)
	{
		_head = new Node();
		_head->_next = _head;
		_head->_prev = _head;

		Node* cur = (l._head)->_next;
		while (cur  != l._head)
		{
			PushBack(cur->_data);
			cur = cur->_next;
		}
	}

	//s1=s2
	/*List<T>& operator=(const List<T>& l)
	{
		if (this != &s)
		{
			Clear();
			Node* cur = (l._head)->_next;
			while (cur != l._head)
			{
				PushBack(cur->_data);
				cur = cur->_next;
			}
		}
		return *this;
	}*/

	List<T>& operator=(List<T> l)
	{
		swap(_head, l._head);
		return *this;
	}

	void Clear()
	{
		Node* cur = _head->_next;
		while (cur != _head)
		{
			Node* next = cur->_next;
			delete cur;

			cur = next;
		}
		_head->_next = _head;
		_head->_prev = _head;
	}

	size_t Size()
	{
		size_t count = 0;
		Node* cur = _head->_next;
		while (cur != _head)
		{
			++count;
			cur = cur->_next;
		}
		return count;
	}

	T& Front()
	{
		assert(_head->_next != _head);
		return _head->_next->_data;
	}

	T& Back()
	{
		assert(_head->_next != _head);
		return _head->_prev->_data;
	}

	void PushBack(const T& x)//尾插
	{
		/*Node* tail = _head->_prev;
		Node* tmp = new Node(x);

		tail->_next = tmp;
		tmp->_prev = tail;

		_head->_prev = tmp;
		tmp->_next = _head;*/
		Insert(_head, x);
	}

	void PopBack()//尾删
	{
		Erase(_head->_prev);
	}

	void PushFront(const T& x)// 头插
	{
		Insert(_head->_next, x);
	}

	void PopFront()//头删
	{
		Erase(_head->_next);
	}
	Node* Find(const T& x)
	{
		Node* cur = _head->_next;
		while (cur != _head)
		{
			if(cur->_data == x)
			{
				return cur;
			}
			cur = cur->_next;
		}
		return NULL;
	}

	//在Pos前面插入
	void Insert(Node* pos, const T& x)
	{
		assert(pos);
		Node* cur = pos;
		Node* tmp = new Node(x);
		Node* prev = pos->_prev;

		prev->_next = tmp;
		tmp->_prev = prev;

		tmp->_next = cur;
		cur->_prev = tmp;
	}
	void Erase(Node* pos)
	{
		assert(pos && pos!=_head);
		Node* prev = pos->_prev;
		Node* next = pos->_next;

		prev->_next = next;
		next->_prev = prev;

		delete pos;
	}
	void Print()
	{
		Node* cur = _head->_next;
		while (cur != _head)
		{
			cout << cur->_data << " ";
			cur = cur->_next;
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
	t.PushBack(4);
	t.PushBack(5);
	t.PushBack(6);
	t.PushBack(7);
	t.Print();
	/*List<int> t1(t);
	t1.PushBack(4);
	t1.Print();
	List<int> t2=t1;
	t2.Print();*/
	/*cout << t.Size() << endl;*/
	/*cout << "Front:" << t.Front() << endl;
	cout << "Back:" << t.Back() << endl;*/
	/*t.Insert(t.Find(1), 0);
	t.Print();*/
	/*t.Erase(t.Find(4));
	t.Print();*/
	/*t.PopBack();*/
	t.PushFront(0);
	t.PopFront();
	t.Print();
}
int main()
{
	Test();
	system("pause");
	return 0;
}