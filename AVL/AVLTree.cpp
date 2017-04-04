#include<iostream>
#include<math.h>
using namespace std;
template<class K,class V>
struct AVLTreeNode
{
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;

	K _key;
	V _value;
	int _bf;

	AVLTreeNode(const K& key, const V& value)
		:_left(NULL)
		, _right(NULL)
		, _parent(NULL)
		, _key(key)
		, _value(value)
		, _bf(0)
	{}
};

template<class K,class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	AVLTree()
		:_root(NULL)
	{}
	~AVLTree()
	{
		_Destroy(_root);
	}
	bool Insert(const K& key, const V& value)
	{
		if (_root == NULL)
		{
			_root = new Node(key, value);
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

		//¸üÐÂÆ½ºâÒò×Ó
		while (parent)
		{
			if (cur == parent->_left)
				parent->_bf--;
			else
				parent->_bf++;

			if (parent->_bf == 0)
				break;
			else if (parent->_bf == 1 || parent->_bf == -1)
			{

				cur = parent;
				parent = cur->_parent;
			}
			else //2   -2
			{
				//Ðý×ª
				if (parent->_bf == 2)
				{
					Node* subR = parent->_right;
					if (subR->_bf == 1)
						//×óµ¥Ðý
						RotateL(parent);
					else
						//ÓÒ×óË«Ðý
						RotateRL(parent);
				}
				else
				{
					Node* subL = parent->_left;
					if (subL->_bf== -1)
						RotateR(parent);
					else //  1
						RotateLR(parent);
				}
				break;
			}
		}
	}

	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

	bool IsBalance()
	{
		return _IsBalance(_root);
	}
protected:
	//ÓÒµ¥Ðý
	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;
		subL->_right = parent;
		Node* ppNode = parent->_parent;
		parent->_parent = subL;
		if (ppNode == NULL)
		{
			_root = subL;
			subL->_parent = NULL;
		}
		else
		{
			if (ppNode->_left == parent)
				ppNode->_left = subL;
			else
				ppNode->_right = subL;
		}
		subL->_parent = ppNode;
		
		 subL->_bf = 0;
		 parent->_bf = 0;
		 /*if (parent->_left == NULL)
			 parent->_bf = 1;
		 else
			 parent->_bf = 0;*/
	}

	//×óµ¥Ðý
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
			subR->_parent = NULL;
		}
		else
		{
			if (ppNode->_left == parent)
				ppNode->_left = subR;
			else
				ppNode->_right = subR;
		}
		subR->_parent = ppNode;
		parent->_bf = subR->_bf = 0;
		/*if (parent->_right == NULL)
			parent->_bf = -1;
		else
			parent->_bf = 0;*/
	}

	//×óÓÒË«Ðý
	void RotateLR(Node* parent)
	{

		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf;
		RotateL(parent->_left);
		RotateR(parent);
		if (bf == 0)
		{
			parent->_bf = subL->_bf = subLR->_bf = 0;
		}
		else if (bf == 1)
		{
			parent->_bf = 0;
			subL->_bf = -1;
			subLR->_bf = 0;
		}
		else
		{
			parent->_bf = 1;
			subL->_bf = 0;
			subLR->_bf = 0;
		}
	}

	//ÓÒ×óË«Ðý
	void RotateRL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int bf = subRL->_bf;
		RotateR(parent->_right);
		RotateL(parent);
		if (bf == 0)
		{
			parent->_bf = subR->_bf = subRL->_bf = 0;
		}
		else if (bf == 1)
		{
			parent->_bf = -1;
			subR->_bf = 0;
			subRL->_bf = 0;
		}
		else //  -1
		{
			parent->_bf = 0;
			subR->_bf = 1;
			subRL->_bf = 0;
		}
	}

	void _InOrder(Node* root)
	{
		if (root == NULL)
			return;
		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);
	}

	size_t _Height(Node* root)
	{
		if (root == NULL)
			return 0;
		int l = _Height(root->_left);
		int r = _Height(root->_right);
		return l > r ? l + 1 : r + 1;
	}
	bool _IsBalance(Node* root)
	{
		if (root == NULL)
			return true;
		int l = _Height(root->_left);
		int r = _Height(root->_right);
		if (r - l != root->_bf)
		{
			cout << "Æ½ºâÒò×ÓÒì³£" << root->_key<<endl;
			return false;
		}
		return (abs(r-l) < 2 )&& _IsBalance(root->_left) && _IsBalance(root->_right);
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
	AVLTree<int, int> t1;
	int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 ,9,3};
	for (size_t i = 0; i < sizeof(a) / sizeof(a[0]); ++i)
	{
		t1.Insert(a[i], i);
	}
	t1.InOrder();
	cout << "t2? ? ?:   " << t1.IsBalance() << endl;
	AVLTree<int, int> t2;
	int a1[] = { 4,2,6,1,3,5,15,7,16,14};
	for (size_t i = 0; i < sizeof(a1) / sizeof(a1[0]); ++i)
	{
		t2.Insert(a1[i], i);
	}
	t2.InOrder();

	cout << "t2? ? ?:   " << t2.IsBalance() << endl;
}

int main()
{
	Test();
	system("pause");
	return 0;
}