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

template <class T>
class BinaryTreeThd
{
	typedef BinaryTreeNodeThd<T> Node;

public:
	BinaryTreeThd(T* a, size_t n, const T& invalid)
	{
		size_t index = 0;;
		_root=_CreateTree(a, n, invalid, index);
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
	void InOrederThd()
	{
		Node* cur = _root;
		while (cur)
		{
			while (cur->_leftTag==LINK)
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

	//前序线索化
	void PrevOrderThreading()
	{
		Node* prev = NULL;
		_PrevOrderThreading(_root, prev);
	}

	void PrevOrderThd()
	{
		Node* cur = _root;
		while (cur)
		{
			while (cur->_leftTag == LINK)
			{
				cout << cur->_data << " ";
				cur = cur->_left;
			}
			cout << cur->_data << " ";
			cur = cur->_right;
		}
	}
		
	void PostOrderThreading()
	{
		Node* prev = NULL;
		_PostOrderThreading(_root, prev);
	}
protected:
	Node* _CreateTree(T* a, size_t n, const T& invalid, size_t& index)
	{
		Node* root = NULL;
		if (index < n && a[index] != invalid)
		{
			root = new Node(a[index]);
			root->_left=_CreateTree(a, n, invalid,++index);
			root->_right=_CreateTree(a, n, invalid,++index);

		}
		return root;
}
	//void _Destroy(Node* root)
	//{
	//	if (root == NULL)
	//		return;
	//	_Destroy(root->_left);
	//	_Destroy(root->_right);
	//	delete root;
	//}
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

	void _PrevOrderThreading(Node* cur, Node*& prev)
	{
		if (cur == NULL)
			return;
		if (cur->_left == NULL)
		{
			cur->_leftTag = THREAD;
			cur->_left = prev;
		}
		if (prev && prev->_right == NULL)
		{
			prev->_rightTag = THREAD;
			prev->_right = cur;
		}
		prev = cur;

		if (cur->_leftTag == LINK)
		{
			_PrevOrderThreading(cur->_left, prev);
		}

		if (cur->_rightTag == LINK)
		{
			_PrevOrderThreading(cur->_right, prev);
		}
	}

	void _PostOrderThreading(Node* cur, Node*& prev)
	{
		if (cur == NULL)
			return;
		_PostOrderThreading(cur->_left, prev);
		_PostOrderThreading(cur->_right, prev);
		if (cur->_left == NULL)
		{
			cur->_leftTag = THREAD;
			cur->_left = prev;
		}
		if (prev && prev->_right == NULL)
		{
			prev->_rightTag = THREAD;
			prev->_right = cur;
		}
		prev = cur;
	}
private:
	Node* _root;
};

void Test()
{
	int  a[] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	BinaryTreeThd  <int> t(a, sizeof(a)/sizeof(a[0]), '#');
	/*t.InOrderThreading();
	t.InOrederThd();*/
	/*t.PrevOrderThreading();
	t.PrevOrderThd();*/
	t.PostOrderThreading();
}
int main()
{
	Test();
	system("pause");
	return 0;
}