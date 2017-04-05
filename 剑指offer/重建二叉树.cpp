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
	//���ڵ�->ǰ������ĵ�һ��Ԫ��
	Node* root = new Node(*startPrevOrder);
	//Ҷ�ӽڵ�
	if (startPrevOrder == endPrevOrder)
		//ǰ�����ֻ��һ���ڵ�
	{
		if (startInOrder == endInOrder && *startPrevOrder == *endPrevOrder)
		{   //�������ֻ��һ���ڵ�
			return root;
		}
		else
		{
			assert(false);
		}
	}
	//����������Ҹ��ڵ�
	int* rootInOrder = startInOrder;
	while (rootInOrder <= endInOrder && *rootInOrder != *startPrevOrder)
	{
		++rootInOrder;
	}
	if (rootInOrder == endInOrder && *rootInOrder != *startPrevOrder)
	{
		//��������
		assert(false);
	}
	//�ɹ��ҵ����ڵ�
	int leftLength = rootInOrder - startInOrder;
	int* leftPrevOrderEnd = startPrevOrder + leftLength; //��������β
	//��������ĸ��� ��������������ұ���������
	if (leftLength > 0)
	{
		//����������
		root->_left = ConstructTree(startPrevOrder + 1, leftPrevOrderEnd, startInOrder, rootInOrder - 1);
	}
	if (leftLength < endPrevOrder - startPrevOrder)
	{
		root->_right = ConstructTree(leftPrevOrderEnd + 1, endPrevOrder, rootInOrder + 1, endInOrder);
	}
	return root;
}
//����������
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