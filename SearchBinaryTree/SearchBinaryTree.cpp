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

	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

	Node* Find(const K& key)
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
			if (cur &&cur->_key == key)
			{
				return cur;
			}
		}
		return NULL;
	}

	bool Remove(const K& key)
	{

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
private:
	Node* _root;
};

void Test()
{
	SerachBinaryTree<int> s;
	s.Insert(5);
	s.Insert(3);
	s.Insert(4);
	s.Insert(1);
	s.Insert(7);
	s.Insert(8);
	s.Insert(2);
	s.Insert(6);
	s.Insert(0);
	s.Insert(9);
	s.InOrder();
	cout << s.Find(0)->_key << endl;
	cout << s.Find(1)->_key << endl;
	cout << s.Find(2)->_key << endl;
	cout << s.Find(3)->_key << endl;
	cout << s.Find(4)->_key << endl;
	cout << s.Find(5)->_key << endl;
	cout << s.Find(6)->_key << endl;
	cout << s.Find(7)->_key << endl;
	cout << s.Find(8)->_key << endl;
	cout << s.Find(9)->_key << endl;
	cout << s.Find(11) << endl;
}
int main()
{
	Test();
	system("pause");
	return 0;
}