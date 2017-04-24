#include<iostream>
using namespace std;

template<class K,class V>
struct AVLTreeNode
{
	K _key;
	V _value;
	int _bf;//ƽ������
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

		//����ƽ������
		while (parent)
		{
			if (parent->_left == cur)//���뵽��ߣ�ƽ�����Ӽ�һ
				parent->_bf--;
			else//���뵽�ұߣ�ƽ�����Ӽ�һ
				parent->_bf++;

			//���º��ж��Ƿ�����AVLTree������-->_bf= 0,-1,1
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
						//����
						RotateL(parent);
					else
						//_bf=-1,������
						RotateRL(parent);
				}
				else// _bf=-2
				{
					Node* subL = parent->_left;
					if (subL->_bf == -1)
						//�ҵ���
						RotateR(parent);
					else//_bf=1
						//���ҵ���
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