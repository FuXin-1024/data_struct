#pragma once 
#include<iostream>
using namespace std;

template <class K,class M=3>
struct BTreeNode
{
	K _key[M];//多一个空间，方便分裂
	BTreeNode<K, M>* _subs[M + 1];//多分配一个空间
	BTreeNode<K, M>* _parent;//父节点
	size_t _size;

	BTreeNode()
	{
		memset(_subs, 0, sizeof(_subs));
		_parent = NULL;
		_size = 0;
	}
};

template <class K,class M=3>
class BTree
{
	typedef BTreeNode Node;
public:
	BTree()
		:_root(NULL)
	{}

	bool Insert(const K& key)
	{

	}
protected:
	Node* _root;
};