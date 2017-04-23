#include<iostream>
using namespace std;

template<class T>
struct SearchBinaryTreeNode
{
	T _key;
	SearchBinaryTreeNode<T>* _left;
	SearchBinaryTreeNode<T>* _right;

	SearchBinaryTreeNode(const T& x)
		:_key(x)
		, _left(NULL)
		, _right(NULL)
	{}
};

template <class T>
class SearchBinaryTree
{
	typedef SearchBinaryTreeNode<T> Node;
public:
	SearchBinaryTree()
		:_root(NULL)
	{}

	~SearchBinaryTree()
	{
		_Destroy(_root);
	}

	bool Insert(const T& key)
	{
		if (_root == NULL)
		{
			_root = new Node(key);
			return true;
		}
		Node* parent = NULL;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key>key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
				return false;
		}
		if (parent->_key < key)
		{
			parent->_right = new Node(key);
			return true;
		}
		else
		{
			parent->_left = new Node(key);
			return true;
		}
	}

	bool InsertR(const T& key)
	{
		return _InsertR(_root, key);
	}

	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

protected:
	bool _InsertR(Node*& root, const T& key)
	{
		if (root == NULL)
		{
			root = new Node(key);
			return true;
		}
		if (root->_key < key)
		{
			return _InsertR(root->_right, key);
		}
		else if (root->_key>key)
		{
			return _InsertR(root->_left, key);
		}
		else
			return false;
	}

	void _InOrder(Node* root)
	{
		if (root == NULL)
			return;
		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);
	}

	void _Destroy(Node* root)
	{
		if (root == NULL)
			return;
		_Destroy(root->_left);
		_Destroy(root->_right);
		delete root;
	}

protected:
	Node* _root;
};

void Test()
{
	SearchBinaryTree<int> s;
	/*s.Insert(5);
	s.Insert(3);
	s.Insert(4);
	s.Insert(1);
	s.Insert(7);
	s.Insert(8);
	s.Insert(2);
	s.Insert(6);
	s.Insert(0);
	s.Insert(9);*/
	s.InsertR(5);
	s.InsertR(3);
	s.InsertR(4);
	s.InsertR(1);
	s.InsertR(7);
	s.InsertR(8);
	s.InsertR(2);
	s.InsertR(6);
	s.InsertR(0);
	s.InsertR(9);
	s.InOrder();
}
int main()
{
	Test();
	system("pause");
	return 0;
}