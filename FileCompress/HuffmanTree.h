#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include"Heap.h"
using namespace std;

template <class T>
struct HuffmanTreeNode
{
	T _w;  // 权值
	HuffmanTreeNode<T>* _left;
	HuffmanTreeNode<T>* _right;
	HuffmanTreeNode<T>* _parent;

	HuffmanTreeNode(const T& x)
		:_w(x)
		, _left(NULL)
		, _right(NULL)
		, _parent(NULL)
	{}

};

template <class T>
class HuffmanTree
{
	typedef HuffmanTreeNode<T> Node;
public:
	HuffmanTree()
		:root(NULL)
	{}

	HuffmanTree(T* a, size_t n, const T& invalid = T())
	{
		//比较权值的大小
		struct Compare
		{
			bool operator()(Node* l, Node* r) const
			{
				return l->_w < r->_w;
			}
		};

		//建小堆
		Heap<Node*, Compare> minHeap;

		for (size_t i = 0; i < n; ++i)
		{
			if (a[i] != invalid)
				minHeap.Push(new Node(a[i]));
		}

		//贪心算法
		while (minHeap.Size()>1)
		{
			Node* left = minHeap.Top();
			minHeap.Pop();
			Node* right = minHeap.Top();
			minHeap.Pop();
			Node* parent = new Node(left->_w + right->_w);

			parent->_left = left;
			parent->_right = right;

			left->_parent = parent;
			right->_parent = parent;

			minHeap.Push(parent);
		}
		_root = minHeap.Top();
	}
	~HuffmanTree()
	{
		_Destory(_root);
	}



protected:
	//防拷贝
	HuffmanTree(HuffmanTree<T>&);
	HuffmanTree& operator=(const HuffmanTree<T> &);

	void _Destory(Node* root)
	{
		if (root == NULL)
			return;

		_Destory(root->_left);
		_Destory(root->_right);

		delete root;
	}
private:
	Node* _root;
};