#include<iostream>

using namespace std;
enum color
{
	RED,
	BLACK,
};
template <class K,class V>
struct RBTreeNode
{
	K _key;
	V _value;
	int _color;
	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode<K, V>* _parent;

	RBTreeNode(const K& k, const V& v)
		:_key(k)
		, _value(v)
		, _color(RED)
		, _left(NULL)
		, _right(NULL)
		, _parent(NULL)
	{}
};

template <class K,class V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
public:
	RBTree()
		:_root(NULL)
	{}

	~RBTree()
	{
		_destroy(_root);
	}

	bool Insert(const K& key, const V& value)
	{
		if (_root == NULL)
		{
			_root = new Node(key, value);
			_root->_color = BLACK;
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
		cur = new Node(key, value);
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

		while (parent && parent->_color == RED)
		{
			Node* grandfather = parent->_parent;
			if (parent == grandfather->_left)
			{
				Node* uncle = grandfather->_right;
				//1. 存在且为红
				if (uncle && uncle->_color == RED)
				{
					//变色处理
					parent->_color = uncle->_color = BLACK;
					grandfather->_color = RED;
					cur = grandfather;
					parent = cur->_parent;
				}
				//叔叔可能不存在或存在为黑
				else
				{
					//双旋
					if (cur == parent->_right)
					{
						RotateL(parent);
						swap(parent, cur);
					}
					RotateR(grandfather);
					parent->_color = BLACK;
					grandfather->_color = RED;
					break;
				}
			}
			//父亲是右儿子，叔叔在左边
			else
			{
				Node* uncle = grandfather->_left;
				//叔叔存在且为红
				if (uncle && uncle->_color == RED)
				{
					parent->_color = uncle->_color = BLACK;
					grandfather->_color = RED;
					cur = grandfather;
					parent = cur->_parent;
				}
				//叔叔不存在或存在为黑
				else
				{
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

	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;
		Node* ppNode = parent->_parent;
		subL->_right = parent;
		parent->_parent = subL;
		if (ppNode == NULL)
		{
			_root = subL;
			_root->_parent = NULL;
		}
		else
		{
			if (ppNode->_right == parent)
				ppNode->_right = subL;
			else
				ppNode->_left = subL;
			subL->_parent = ppNode;
		}
	}
		void RotateL(Node* parent)
		{
			Node* subR = parent->_right;
			Node* subRL = subR->_left;
			parent->_right = subRL;
			if (subRL)
				subRL->_parent = parent;
			subR->_left = parent;
			Node* ppNode = parent->_parent;
			parent->_parent = subR;
			if (ppNode == NULL)
			{
				_root = subR;
				_root->_parent = NULL;
			}
			else
			{
				if (ppNode->_left == parent)
					ppNode->_left = subR;
				else
					ppNode->_right = subR;
				subR->_parent = ppNode;
			}
	}
		void InOrder()
		{
			_InOrder(_root);
			cout << endl;
		}
		bool IsBlance()
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
	void _destroy(Node* root)
	{
		if (root == NULL)
			return;
		_destroy(root->_left);
		_destroy(root->_right);
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
void Test()
{
	RBTree<int, int> t1;
	int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15, 9, 3 };
	for (size_t i = 0; i < sizeof(a) / sizeof(a[0]); ++i)
	{
		t1.Insert(a[i], i);
	}
	t1.InOrder();
	cout << t1.IsBlance() << endl;
}
int main()
{
	Test();
	system("pause");
	return 0;
}