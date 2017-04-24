#include<iostream>
using namespace std;

template<class K,class V>
struct AVLTreeNode
{
	K _key;
	V _value;
	int _bf;//平衡因子
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;

	AVLTreeNode(const K& key, const V& value)
		:_key(key)
		, _value(value)
		, _left(NULL)
		, _right(NULL)
		, _parent(NULL)
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
			_root = new Node(key,value);
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
			else if (cur->_key>key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
				return false;
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

		//更新平衡因子
		while (parent)
		{
			if (parent->_left == cur)//插入到左边，平衡因子减一
				parent->_bf--;
			else//插入到右边，平衡因子加一
				parent->_bf++;

			//更新后，判断是否满足AVLTree的性质-->_bf= 0,-1,1
			if (parent->_bf == 0)
				break;
			else if (parent->_bf == 1 || parent->_bf == -1)
			{
				cur = parent;
				parent = cur->_parent;
			}
			else //_bf=2 || _bf=-2
			{
				if (parent->_bf == 2)
				{
					Node* subR = parent->_right;
					if (subR->_bf == 1)
						//左单旋
						RotateL(parent);
					else
						//_bf=-1,右左单旋
						RotateRL(parent);
				}
				else// _bf=-2
				{
					Node* subL = parent->_left;
					if (subL->_bf == -1)
						//右单旋
						RotateR(parent);
					else//_bf=1
						//左右单旋
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
		//return _IsBalance(_root);
		int Height = 0;
		return _IsBalance(_root, Height);
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

	void RotateL(Node* parent)//左单旋
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;
		Node* ppHead = parent->_parent;
		subR->_left = parent;
		parent->_parent = subR;

		if (ppHead == NULL)//根节点
		{
			_root = subR;
			subR->_parent = NULL;
		}
		else//不是根节点
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
		parent->_bf = subR->_bf = 0;
	}

	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;
		Node* ppHead = parent->_parent;
		subL->_right = parent;
		parent->_parent = subL;

		if (ppHead == NULL)//根节点
		{
			_root = subL;
			subL->_parent = NULL;
		}
		else//不是根节点
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
		parent->_bf = subL->_bf = 0;
	}

	void RotateLR(Node* parent)//左右双旋
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf;

		RotateL(parent->_left);
		RotateR(parent);

		//调整平衡因子
		if (bf == 0)
		{
			parent->_bf = subL->_bf = subLR->_bf = 0;
		}
		else if (bf == -1)
		{
			parent->_bf = 1;
			subL->_bf = 0;
			subLR->_bf = 0;
		}
		else
		{
			parent->_bf = 0;
			subL->_bf = -1;
			subLR->_bf = 0;
		}
	}

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
		else if (bf == -1)
		{
			parent->_bf = 0;
			subR->_bf = 1;
			subRL->_bf = 0;
		}
		else
		{
			parent->_bf = -1;
			subR->_bf = 0;
			subRL->_bf = 0;
		}
	}

	void _InOrder(Node* root)
	{
		if (root == NULL)
			return ;
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

	bool _IsBalance(Node* root) //O(n)
	{
		if (root == NULL)
			return true;
		int l = _Height(root->_left);
		int r = _Height(root->_right);

		if ((r - l) != root->_bf)
		{
			cout << "平衡因子异常： " << root->_key << endl;
			return false;
		}

		return (abs(r - l) < 2) && _IsBalance(root->_left) && _IsBalance(root->_right);
	}

	bool _IsBalance(Node* root, int& Height)
	{
		if (root == NULL)
		{
			Height = 0;
			return true;
		}
		int l = 0; int r = 0;
		if (_IsBalance(root->_left, l)
			&& _IsBalance(root->_right, r)
			&& abs(r - l) < 2)
		{
			if ((r - l) != root->_bf)
			{
				cout << "平衡因子异常： " << root->_key << endl;
				return false;
			}
			Height = l>r ? l + 1 : r + 1;
			return true;
		}
		else
			return false;
	}

protected:
	Node* _root;
};


void AVLTreeTest()
{
	AVLTree<int ,int> t1;
	int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15, 9, 3 };
	for (size_t i = 0; i < sizeof(a) / sizeof(a[0]); ++i)
	{
		t1.Insert(a[i], i);
	}
	t1.InOrder();
	cout << "t1? ? ?:   " << t1.IsBalance() << endl;

	AVLTree<int, int> t2;
	int a1[] = { 4,2,6,1,3,5,15,7,16,14};
	for (size_t i = 0; i < sizeof(a1) / sizeof(a1[0]); ++i)
	{
		t2.Insert(a1[i], i);
	}
	t2.InOrder();
	cout << "t2? ? ?:   " << t1.IsBalance() << endl;
}
int main()
{
	AVLTreeTest();
	system("pause");
	return 0;
}