#include<iostream>
#include<assert.h>
using namespace std;

typedef struct TreeNode
{
	int _value;
	TreeNode* _left;
	TreeNode* _right;

	TreeNode(const int value)
		:_value(value)
		, _left(NULL)
		, _right(NULL)
	{}
}Node;

Node* ConstructTree(int* startPrevOrder, int* endPrevOrder, 
	int* startInOrder, int* endInOrder)
{
	//根节点->前序遍历的第一个元素
	Node* root = new Node(*startPrevOrder);
	//叶子节点
	if (startPrevOrder == endPrevOrder)
		//前序遍历只有一个节点
	{
		if (startInOrder == endInOrder && *startPrevOrder == *endPrevOrder)
		{   //中序遍历只有一个节点
			return root;
		}
		else
		{
			assert(false);
		}
	}
	//在中序遍历找根节点
	int* rootInOrder = startInOrder;
	while (rootInOrder <= endInOrder && *rootInOrder != *startPrevOrder)
	{
		++rootInOrder;
	}
	if (rootInOrder == endInOrder && *rootInOrder != *startPrevOrder)
	{
		//参数有误；
		assert(false);
	}
	//成功找到根节点
	int leftLength = rootInOrder - startInOrder;
	int* leftPrevOrderEnd = startPrevOrder + leftLength; //左子树的尾
	//中序遍历的根的 左边是左子树，右边是右子树
	if (leftLength > 0)
	{
		//构建左子树
		root->_left = ConstructTree(startPrevOrder + 1, leftPrevOrderEnd, startInOrder, rootInOrder - 1);
	}
	if (leftLength < endPrevOrder - startPrevOrder)
	{
		root->_right = ConstructTree(leftPrevOrderEnd + 1, endPrevOrder, rootInOrder + 1, endInOrder);
	}
	return root;
}
//构建二叉树
Node* Construct(int* prevOrder, int* inOrder, size_t n)
{
	assert(prevOrder);
	assert(inOrder);
	assert(n);
	return ConstructTree(prevOrder, prevOrder + n - 1, inOrder, inOrder + n - 1);
}

void Test()
{
	int preOrder[] = { 1, 2, 4, 7, 3, 5, 6, 8 };
	int inOrder[] = { 4, 7, 2, 1, 5, 3, 8, 6 };
	Node *root = Construct(preOrder, inOrder, sizeof(preOrder) / sizeof(*preOrder));
}
int main()
{
	Test();
	system("pause");
	return 0;
}