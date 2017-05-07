#pragma once 
#include<iostream>
using namespace std;

template <class K,size_t M=3>
struct BTreeNode
{
	K _keys[M];						//多一个空间，方便分裂
	BTreeNode<K, M>* _subs[M + 1];	//多分配一个空间
	BTreeNode<K, M>* _parent;		//父节点
	size_t _size;					//实际key的个数

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
		if (ret.second >= 0)//key已经存在
			return false;
		Node* cur = ret.first;
		Node* sub = cur;
		K newKey = key;
		while (1)
		{
			_Insert(cur, sub, key);
		}
	}
protected:
	void _Insert(Node* cur, Node* sub, const K& key)
	{

	}
protected:
	Node* _root;
};