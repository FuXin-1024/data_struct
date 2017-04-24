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
						RotatelLR(parent);
				}
				break;
			}
		}
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

protected:
	Node* _root;
};


void AVLTreeTest()
{
	AVLTree<int ,int> t;
}
int main()
{
	AVLTreeTest();
	system("pause");
	return 0;
}