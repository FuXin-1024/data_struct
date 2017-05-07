#pragma once 
#include<iostream>
#include<assert.h>
using namespace std;

template <class K,size_t M=3>
struct BTreeNode
{
	K _keys[M];						//��һ���ռ䣬�������
	BTreeNode<K, M>* _subs[M + 1];	//�����һ���ռ�
	BTreeNode<K, M>* _parent;		//���ڵ�
	size_t _size;					//ʵ��key�ĸ���

	BTreeNode()
	{
		memset(_subs, 0, sizeof(_subs));
		_parent = NULL;
		_size = 0;
	}
};

template <class K, size_t M = 3>
class BTree
{
	typedef BTreeNode<K,M> Node;
public:
	BTree()
		:_root(NULL)
	{}

	pair <Node* ,int>  Find(const K& key)
	{
		Node* parent = cur;
		Node* cur = _root;
		while (cur)
		{
			size_t i = 0;
			for (; i < cur->_size;)
			{
				if (cur->_keys[i] < key)
					++i;
				else if (cur->_keys[i] > key)
					break;
				else
					return make_pair(cur, i);
			}
			parent = cur;
			cur = cur->_keys[i];
		}
		return make_pair(parent, -1);
	}

	bool Insert(const K& key)
	{
		if (root == NULL)
		{
			_root = new node;
			_root->_keys[0] = key;
			_root->_size = 1;
			return true;
		}
		pair<Node*, int> ret = Find(key);
		if (ret.second >= 0)//key�Ѿ�����
			return false;
		Node* cur = ret.first;
		Node* sub = NULL;
		K newKey = key;
		while (1)
		{
			//����key
			_Insert(cur, sub, newKey);

			//�жϹؼ��������Ƿ�����
			if (cur->_size < M) //�ؼ����������ΪM-1
				return true;
			//�����㣬��ʼ����
			Node* newNode = new Node;
			size_t index = 0;
			size_t mid = M / 2;
			size_t i = mid + 1;
			for (; i < cur->_size; ++i)
			{
				newNode->_keys[index] = cur->_keys[i];
				newNode->_subs[index] = cur->_subs[i];
				if (cur->_subs[i])
				{
					cur->_subs[i]->_parent = newNode;
				}
				newNode->_size++;
			}
			newNode->_keys[i] = cur->_keys[i];//���һ��Ԫ��
			if (cur->_subs[i])
			{
				cur->_subs[i]->_parent = newNode;
			}
			cur->_size = (cur->_size) - (newNode->_size )- 1;

			if (cur->_parent == NULL)
			{
				_root = new Node;
				_root->_keys[0] = cur->_keys[mid];
				_root->_subs[0] = cur;
				cur->_parent = _root;
				_root->_subs[1] = newNode;
				newNode->_parent = _root;
				_root->_size = 1;
				return true;
			}
			else
			{
				newKey = cur->_keys[mid];
				cur = parent;
				sub = newNode;
			}
		}
	}
protected:
	void _Insert(Node* cur, Node* sub, const K& key)
	{
		assert(cur);
		int end = cur->_size - 1;
		for (; end >= 0; --end)
		{
			//key����������
			if (cur->_keys[end] > key)
				break;
			else
			{
				//��key���뵽����λ�á�
				cur->_keys[end+1] = cur->_keys[end];
				sub->_keys[end + 2] = sub->_keys[end + 1];//���Һ��������
			}

			cur->_keys[end + 1] = key;
			cur->_subs[end + 2] = sub;
			if (sub)
				sub->_parent = cur;
			cur->_size + 1;
		}
	}
protected:
	Node* _root;
};