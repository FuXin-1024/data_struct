#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<queue>
using namespace std;

template <class T>
struct BinaryTreeNode
{
	T _data;
	BinaryTreeNode<T>* _left;
	BinaryTreeNode<T>* _right;
	BinaryTreeNode(const T& x)
		:_data(x)
		, _left(NULL)
		, _right(NULL)
	{}
};

template <class T>
class BinaryTree
{
	typedef BinaryTreeNode<T> Node;
public:
	BinaryTree()
		:_root(NULL)
	{}

	~BinaryTree()
	{}

	BinaryTree(const BinaryTreeNode<T>& t);
	BinaryTree<T>& operator=(const BinaryTree<T>& t);

	BinaryTree(T* a, size_t n, const T& invalid = T())
	{
		size_t index = 0;
		_root = CreateTree(a, n, invalid, index);
	}
	void PrevOrder()// 前序遍历
	{
		_PrevOrder(_root);
	}


	void InOrder()//中序遍历
	{
		_InOrder(_root);
	}

	void PostOrder()//后序遍历
	{
		_PostOrder(_root);
	}

	void LevelOrder()// 层序
	{
		_LevelOrder(_root);
	}

	size_t Size()
	{
		return _Size(_root);
	}

protected:
	Node* CreateTree(T* a, size_t n, const T& invalid, size_t& index)
	{
		Node* root = NULL;
		if ((index < n) && (a[index] != invalid))
		{
			root = new Node(a[index]);
			root->_left = CreateTree(a,n , invalid, ++index);
			root->_right = CreateTree(a, n, invalid, ++index);
		}
		return root;
	}

	void _PrevOrder(Node* root)
	{
		if (root == NULL)
		{
			return;
		}
		cout << root->_data << " ";
		_PrevOrder(root->_left);
		_PrevOrder(root->_right);
	}

	void _InOrder(Node* root)
	{
		if (root == NULL)
		{
			return;
		}
		_InOrder(root->_left);
		cout << root->_data << " ";
		_InOrder(root->_right);
	}

	void _PostOrder(Node* root)
	{
		if (root == NULL)
		{
			return;
		}
		_PostOrder(root->_left);
		_PostOrder(root->_right);
		cout << root->_data << " ";
	}
	void _LevelOrder(Node* root)
	{
		queue<Node*> q;
		if (root)
		{
			q.push(root);
		}
		while (!q.empty())
		{
			Node* front = q.front();
			cout << front->_data<<" ";
			q.pop();
			if (front->_left)
				q.push(front->_left);
			if (front->_right)
				q.push(front->_right);
		}
		cout << endl;
	}

		size_t _Size(Node* root)
	{
		if (root == NULL)
		{
			return 0;
		}
		return _Size(root->_left) + _Size(root->_right) + 1;
	}

protected:
	Node* _root;
};

void Test()
{
	int  a[] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	BinaryTree  <int> t(a, sizeof(a)/sizeof(a[0]), '#');
	t.PrevOrder();
	cout << endl;
	t.InOrder();
	cout << endl;
	t.PostOrder();
	cout << endl;
	t.LevelOrder();
	cout << t.Size() << endl;
}
int main()
{
	Test();
	system("pause");
	return 0;
}