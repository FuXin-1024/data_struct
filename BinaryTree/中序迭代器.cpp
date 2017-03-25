#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>

using namespace std;
enum PointerTag
{
	THREAD,
	LINK
};

template<class T>
struct BinaryTreeNodeThd
{
	BinaryTreeNodeThd(const T& t)
	:_data(t)
	, _left(NULL)
	, _right(NULL)
	, _leftTag(LINK)
	, _rightTag(LINK)
	{}

	T _data;
	BinaryTreeNodeThd* _left;
	BinaryTreeNodeThd* _right;
	PointerTag _leftTag;
	PointerTag _rightTag;
};
//中序迭代器
template<class T,class Ref,class Ptr>
struct BinaryTreeIterator
{
	typedef BinaryTreeNodeThd<T> Node;
	Node* _node;
	typedef BinaryTreeIterator<T, Ref, Ptr> Self;

	BinaryTreeIterator(Node* node)
		:_node(node)
	{}

	Self& operator++() //重载前置++
	{
		if (_node->_rightTag == THREAD)
		{
			_node = _node->_right;
		}
		else
		{
			Node* left = _node->_right;
			while (left&&left->_leftTag == LINK)
			{
				left = left->_left;
			}
			_node = left;
		}
		return *this;
	}

	Ref operator*()
	{
		return _node->_data;
	}
	Ptr operator->()
	{
		return &_node->_data;
	}

	bool operator!=(const Self &s)const
	{
		return _node != s._node;
	}

	Self operator--()
	{
		if (_node->_leftTag == THREAD)
		{
			_node = _node->_left;
		}
		else
		{
			Node* right = _node->_left;
			while (right && right->_rightTag == LINK)
			{
				right = right->_right;
			}
			_node = right;
		}
		return *this;
	}
};

template <class T>
class BinaryTreeThd
{
	typedef BinaryTreeNodeThd<T> Node;

public:
	typedef BinaryTreeIterator<T, T&, T*> Iterator;
	typedef BinaryTreeIterator<T, const T&, T*> ConstIterator;

	Iterator Begin()
	{
		Node* left = _root;
		while (left->_leftTag == LINK)
		{
			left = left->_left;
		}
		return Iterator(left);
	}

	Iterator End()
	{
		return Iterator(NULL);
	}

	BinaryTreeThd(T* a, size_t n, const T& invalid)
	{
		size_t index = 0;;
		_root = _CreateTree(a, n, invalid, index);
	}

	~BinaryTreeThd()
	{
		//_Destroy(_root);
	}
	//中序线索化
	void InOrderThreading()
	{
		Node* prev = NULL;
		_InOrderThreading(_root, prev);
	}

	// 中序线索遍历化
	void InOrderThd()
	{
		Node* cur = _root;
		while (cur)
		{
			while (cur->_leftTag == LINK)
			{
				cur = cur->_left;
			}
			cout << cur->_data << " ";
			while (cur->_rightTag == THREAD)
			{
				cur = cur->_right;
				cout << cur->_data << " ";
			}
			cur = cur->_right;
		}
	}

	
protected:
	Node* _CreateTree(T* a, size_t n, const T& invalid, size_t& index)
	{
		Node* root = NULL;
		if (index < n && a[index] != invalid)
		{
			root = new Node(a[index]);
			root->_left = _CreateTree(a, n, invalid, ++index);
			root->_right = _CreateTree(a, n, invalid, ++index);

		}
		return root;
	}
	
	void _InOrderThreading(Node* cur, Node*& prev)
	{
		if (cur == NULL)
			return;
		_InOrderThreading(cur->_left, prev);
		if (cur->_left == NULL)
		{
			cur->_leftTag = THREAD;
			cur->_left = prev;
		}
		if (prev && prev->_right == NULL)
		{
			prev->_right = cur;
			prev->_rightTag = THREAD;
		}
		prev = cur;
		_InOrderThreading(cur->_right, prev);
	}

	
private:
	Node* _root;
};

void PrintTree(BinaryTreeThd<int> &t)
{
	BinaryTreeThd<int>::Iterator it = t.Begin();
	while (it != t.End())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}
void Test()
{
	//int  a[] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	//BinaryTreeThd  <int> t(a, sizeof(a) / sizeof(a[0]), '#');
	///*t.InOrderThreading();
	//t.InOrederThd();*/
	///*t.PrevOrderThreading();
	//t.PrevOrderThd();*/
	//t.PostOrderThreading();
	int  a[] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	BinaryTreeThd  <int> t(a, sizeof(a) / sizeof(a[0]), '#');
	t.InOrderThreading();
	t.InOrderThd();
	cout << endl;
	PrintTree(t);
}
int main()
{
	Test();
	system("pause");
	return 0;
}

