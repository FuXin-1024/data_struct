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

	bool Insert(const K& key)
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
		cur = new Node(key);
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

		//�жϲ���ļ������
		while (parent && parent->_color == RED)
		{
			Node* grandfather = parent->_parent;
			if (parernt == grandfather->_left)
			{
				Node* uncle = grandfather->_right;
				//1.���������Ϊ��
				if (uncle && uncle->_color == RED)
				{
					//��ɫ����
					parent->_color = uncle->_color = BLACK;
					grandfather->_color = RED;
					cur = grandfather;
					parent = cur->_parent;
				}
				else//���岻���ڻ���� Ϊ��
				{	
					//���cur��parent���ұߣ�������������
					//���cur��parent���ұߣ�����
					if (cur = parent->_right)
					{
						RotateL(parent);
						swap(cur, parent);//��ת�꣬cur��parent�����棬����
					}
					RotateR(grandfather);
					parent->_color = BLACK;
					grandfather->_color = RED;
					break;
				}
			}
			else//�������ұߣ����������
			{
				Node* uncle = grandfather->_left;
				//���������Ϊ��
				if (uncle && uncle->_color == RED)
				{
					parent->_color = BLACK;
					uncle->_color = BLACK;
					grandfather->_color = RED;
					cur = grandfather;
					parent = cur->_parent;
				}
				//���岻���ڻ����Ϊ��
				else
				{
					//���cur��parent����ߣ���������������
					//���cur��parent���ұߣ�����
					if (cur = parent->_left)
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
		}
		_root->_color = BLACK;
		return true;
	}

	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
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

protected:
	Node* _root;
};
int main()
{
	system("pause");
	return 0;
}