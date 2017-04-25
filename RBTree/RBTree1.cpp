#include<iostream>
using namespace std;

enum COLOR
{
	BLACK,
	RED
};

template<class K,class V>
struct RBTreeNode
{
	K _key;
	V _value;
	COLOR _color;
	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode<K, V>* _parent;

	RBTreeNode(const K& key, const V& value)
		:_key(key)
		, _value(value)
		, _color(RED)
		, _left(NULL)
		, _right(NULL)
		, _parent(NULL)
	{}
};

template<class K,class V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
public:
	RBTree()
		:_root(NULL)
	{}

	~RBTree()
	{
		_Destroy(_root);
	}

	bool Insert(const K& key,const V& value)
	{
		if (_root == NULL)
		{
			_root = new Node(key,value);
			_root->_color = BLACK;
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
		cur = new Node(key,value);
		if (parent->_key < key)
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_left = cur;
			cur->_parent = parent;
		}

		//判断插入的几种情况
		while (parent && parent->_color == RED)
		{
			Node* grandfather = parent->_parent;
			if (parent == grandfather->_left)
			{
				Node* uncle = grandfather->_right;
				//1.叔叔存在且为红
				if (uncle && uncle->_color == RED)
				{
					//变色处理
					parent->_color = uncle->_color = BLACK;
					grandfather->_color = RED;
					cur = grandfather;
					parent = cur->_parent;
				}
				else//叔叔不存在或存在 为黑
				{	
					//如果cur在parent的右边，先左旋后右旋
					//如果cur在parent的右边，右旋
					if (cur = parent->_right)
					{
						RotateL(parent);
						swap(cur, parent);//旋转完，cur在parent的上面，交换
					}
					RotateR(grandfather);
					parent->_color = BLACK;
					grandfather->_color = RED;
					break;
				}
			}
			else//父亲在右边，叔叔在左边
			{
				Node* uncle = grandfather->_left;
				//叔叔存在且为红
				if (uncle && uncle->_color == RED)
				{
					parent->_color = BLACK;
					uncle->_color = BLACK;
					grandfather->_color = RED;
					cur = grandfather;
					parent = cur->_parent;
				}
				//叔叔不存在或存在为黑
				else
				{
					//如果cur在parent的左边，先右旋，再左旋
					//如果cur在parent的右边，左旋
					if (cur == parent->_left)
					{
						RotateR(parent);
						swap(parent, cur);
					}
					RotateL(grandfather);
					parent->_color = BLACK;
					grandfather->_color = RED;
					break;
				}
			}
		}
		_root->_color = BLACK;
		return true;
	}

	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

	bool IsBalance()
	{
		if (_root == NULL)
			return true;
		if (_root->_color == RED)
			return false;
		int blackNum = 0;
		Node* left = _root;
		while (left)
		{
			if (left->_color == BLACK)
				++blackNum;
			left = left->_left;
		}
		int num = 0;
		return _IsBalance(_root, blackNum, num);
	}

protected:
	void _Destroy(Node* root)
	{
		if (root == NULL)
			return;
		_Destroy(root->_left);
		_Destroy(root->_right);
		delete root;
	}

	void _InOrder(Node* root)
	{
		if (root == NULL)
			return;
		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);
	}

	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;

		Node* ppHead = parent->_parent;
		subR->_left = parent;
		parent->_parent = subR;
		if (ppHead == NULL)
		{
			_root = subR;
			subR->_parent = NULL;
		}
		else
		{
			if (ppHead->_left == parent)
			{
				ppHead->_left = subR;
				subR->_parent = ppHead;
			}
			else
			{
				ppHead->_right = subR;
				subR->_parent = ppHead;
			}
		}
	}

	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		Node* ppHead = parent->_parent;
		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;

		subL->_right = parent;
		parent->_parent = subL;

		if (ppHead == NULL)
		{
			_root = subL;
			subL->_parent = NULL;
		}
		else
		{
			if (ppHead->_left == parent)
			{
				ppHead->_left = subL;
				subL->_parent = ppHead;
			}
			else
			{
				ppHead->_right = subL;
				subL->_parent = ppHead;
			}
		}
	}

	bool _IsBalance(Node* root, const int blackNum, int num)
	{
		if (root == NULL)
		{
			if (num != blackNum)
			{
				cout << "异常" << endl;
				return false;
			}
			else
				return true;
		}
		if (root->_color == RED && root->_parent->_color == RED)
		{
			cout << "存在连续红节点" << root->_key << endl;
		}
		if (root->_color == BLACK)
		{
			++num;
		}
		return _IsBalance(root->_left, blackNum, num) && _IsBalance(root->_right, blackNum, num);
	}

protected:
	Node* _root;
};

void TestRBTree()
{
	RBTree<int, int> t1;
	int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15, 9, 3 };
	for (size_t i = 0; i < sizeof(a) / sizeof(a[0]); ++i)
	{
		t1.Insert(a[i], i);
		//cout << a[i] << " ";
	}
	t1.InOrder();
	cout << t1.IsBalance() << endl;
}
int main()
{
	TestRBTree();
	system("pause");
	return 0;
}