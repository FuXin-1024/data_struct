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

	const Node* Find(const T& key)
	{
		if (_root == NULL)
			return NULL;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key < key)
				cur = cur->_right;
			else if (cur->_key>key)
				cur = cur->_left;
			else
				return cur;
		}
		return NULL;
	}

	const Node* FindR(const T& key)
	{
		return _FindR(_root, key);
	}

	bool Remove(const T& key)
	{
		Node* cur = _root;
		Node* parent = cur;
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
			{
				Node* del = cur;
				//没有左子树
				if (cur->_left == NULL)
				{
					//删除没有左子树的根节点
					if (_root->_key == key)
					{
						_root = _root->_right;
						delete del;
						return true;
					}
					if (parent->_right == cur)
					{
						parent->_right = cur->_right;
					}
					else
					{
						parent->_left = cur->_right;
					}
				}
				//没有右子树
				else if (cur->_right==NULL)
				{
					//删除没有右子树的根节点
					if (_root->_key == key)
					{
						_root = _root->_left;
						delete del;
						return true;
					}
					if (parent->_right == cur)
					{
						parent->_right = cur->_left;
					}
					else
					{
						parent->_left = cur->_left;
					}
				}
				//既有左子树又有右子树
				else
				{
					//替换
					//左树的最右节点，右树的最左节点
					Node* subRight = cur->_right;
					Node* subParent = cur;//不能为空！
					while (subRight->_left)
					{
						subParent = subRight;
						subRight = subRight->_left;
					}
					// 右子树的最左节点，开始替换
					cur->_key = subRight->_key;

					del = subRight;
					if (subParent->_left == subRight)
					{
						subParent->_left = subRight->_right;
					}
					else
					{
						subParent->_right = subRight->_right;
					}
				}
				delete del;
				return true;
			}
		}
		return false;
	}

	bool RemoveR(const T& key)
	{
		return _RemoveR(_root, key);
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

	Node* _FindR(Node* root, const T& key)
	{
		if (root == NULL)
			return NULL;
		if (root->_key < key)
			return _FindR(root->_right, key);
		else if (root->_key>key)
			return _FindR(root->_left, key);
		else
			return root;
	}

	bool _RemoveR(Node*& root, const T& key)
	{
		if (root == NULL)
		{
			return false;
		}
		if (root->_key < key)
		{
			return _RemoveR(root->_right, key);
		}
		else if (root->_key > key)
		{
			return _RemoveR(root->_left, key);
		}
		else
		{
			Node* del = root;
			if (root->_left == NULL)
			{
				root = root->_right;
			}
			else if (root->_right == NULL)
			{
				root = root->_left;
			}
			else
			{
				Node* parent = root;
				Node* subRight = root->_right;
				while (subRight->_left)
				{
					parent = subRight;
					subRight = subRight->_left;
				}
				swap(subRight->_key, parent->_key);
				del = subRight;
				if (parent->_left == subRight)
				{
					parent->_left = subRight->_right;
				}
				else
				{
					parent->_right = subRight->_right;
				}
			}
			delete del;
			return true;
		}
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
	/*cout << "Find-->0  " << s.Find(0)->_key << endl;
	cout << "Find-->1  " << s.Find(1)->_key << endl;
	cout << "Find-->2  " << s.Find(2)->_key << endl;
	cout << "Find-->3  " << s.Find(3)->_key << endl;
	cout << "Find-->4  " << s.Find(4)->_key << endl;
	cout << "Find-->5  " << s.Find(5)->_key << endl;
	cout << "Find-->6  " << s.Find(6)->_key << endl;
	cout << "Find-->7  " << s.Find(7)->_key << endl;
	cout << "Find-->8  " << s.Find(8)->_key << endl;
	cout << "Find-->9  " << s.Find(9)->_key << endl;
	cout << "Find-->10  " << s.Find(10) << endl;*/

	/*cout << "Find-->0  " << s.FindR(0)->_key << endl;
	cout << "Find-->1  " << s.FindR(1)->_key << endl;
	cout << "Find-->2  " << s.FindR(2)->_key << endl;
	cout << "Find-->3  " << s.FindR(3)->_key << endl;
	cout << "Find-->4  " << s.FindR(4)->_key << endl;
	cout << "Find-->5  " << s.FindR(5)->_key << endl;
	cout << "Find-->6  " << s.FindR(6)->_key << endl;
	cout << "Find-->7  " << s.FindR(7)->_key << endl;
	cout << "Find-->8  " << s.FindR(8)->_key << endl;
	cout << "Find-->9  " << s.FindR(9)->_key << endl;
	cout << "Find-->10  " << s.FindR(10) << endl;*/
	/*s.Remove(0);
	s.Remove(5);*/
	s.RemoveR(0);
	s.InOrder();
}
int main()
{
	Test();
	system("pause");
	return 0;
}