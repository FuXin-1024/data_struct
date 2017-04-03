#include<iostream>
using namespace std;

template <class K>
struct SerachBinaryTreeNode
{
	K _key;
	SerachBinaryTreeNode<K>* _left;
	SerachBinaryTreeNode<K>* _right;

	SerachBinaryTreeNode(const K& key)
		:_key(key)
		, _left(NULL)
		, _right(NULL)
	{}
};

template < class K>
class SerachBinaryTree
{
	typedef SerachBinaryTreeNode<K> Node;
public:
	SerachBinaryTree()
		:_root(NULL)
	{}
	~SerachBinaryTree()
	{
		_Destroy(_root);
	}
	bool Insert(const K& key)
	{
		if (_root == NULL)
		{
			_root = new Node(key);
			return true;
		}
		Node* cur = _root;
		Node* parent = NULL;
		while (cur)
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
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

	bool InsertR(const K& key)
	{
		return _InsertR(_root, key);
	}
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

	const Node* Find(const K& key)
	{
		if (_root == NULL)
			return NULL;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key < key)
			{
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				cur = cur->_left;
			}
			else
			{
				return cur;
			}
		}
		return NULL;
	}

	const Node* FindR(const K& key)
	{
		return _FindR(_root, key);
	}

	bool Remove(const K& key)
	{
		Node* cur = _root;
		Node* parent = NULL;

		while (cur)
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key > key)
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
					//没有左树删根节点
					if (_root->_key == key)
					{
						_root = cur->_right;
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
				else if (cur->_right == NULL)
				{
					//没有右树删根节点
					if (_root->_key == key)
					{
						_root = cur->_left;
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
					//右树的最左节点或左树的最右节点
					Node* subRight = cur->_right;
					Node* subParent = cur; //不能设为空！！！！
					while (subRight->_left)
					{
						subParent = subRight;
						subRight = subRight->_left;
					}
					cur->_key = subRight->_key; //替换
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

	bool RemoveR(const K& key)
	{
		return _RemoveR(_root, key);
	}
protected:
	void _InOrder(Node* root)
	{
		if (root == NULL)
			return;
		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);
	}

	Node* _FindR(Node* root, const K& key)
	{
		if (root == NULL)
			return NULL;
		if (root->_key < key)
		{
			return _FindR(root->_right, key);
		}
		else if (root->_key>key)
		{
			return _FindR(root->_left, key);
		}
		else
		{
			return root;
		}
	}

	bool _InsertR(Node*& root, const K& key)
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
		else if (root->_key > key)
		{
			return _InsertR(root->_left, key);
		}
		else
		{
			return false;
		}

	}

	bool _RemoveR(Node*& root, const K& key)
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

void _Destroy(Node* root)
{
	if (root == NULL)
		return;
	_Destroy(root->_left);
	_Destroy(root->_right);
	delete root;
}
private:
	Node* _root;
};

void Test()
{
	SerachBinaryTree<int> s;
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
	//cout << s.Find(0)->_key << endl;
	//cout << s.Find(1)->_key << endl;
	//cout << s.Find(2)->_key << endl;
	//cout << s.Find(3)->_key << endl;
	//cout << s.Find(4)->_key << endl;
	//cout << s.Find(5)->_key << endl;
	//cout << s.Find(6)->_key << endl;
	//cout << s.Find(7)->_key << endl;
	//cout << s.Find(8)->_key << endl;
	//cout << s.Find(9)->_key << endl;
	//cout << s.Find(11) << endl;

	/*cout << s.FindR(0)->_key << endl;
	cout << s.FindR(1)->_key << endl;
	cout << s.FindR(2)->_key << endl;
	cout << s.FindR(3)->_key << endl;
	cout << s.FindR(4)->_key << endl;
	cout << s.FindR(5)->_key << endl;
	cout << s.FindR(6)->_key << endl;
	cout << s.FindR(7)->_key << endl;
	cout << s.FindR(8)->_key << endl;
	cout << s.FindR(9)->_key << endl;
	cout << s.FindR(11) << endl;*/
	//s.Remove(5);
	s.Remove(0);
	s.Remove(1);
	s.Remove(2);
	s.Remove(3);
	s.Remove(4);
	s.Remove(5);

	//s.Remove(6);
	//s.Remove(7);
	//s.Remove(8);
	//s.Remove(9);
	//s.Remove(10);
	s.InOrder();
}
int main()
{
	Test();
	system("pause");
	return 0;
}
