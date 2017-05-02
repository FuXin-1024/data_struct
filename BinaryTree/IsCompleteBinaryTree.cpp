#include<iostream>
#include<queue>
using namespace std;
 
struct Node
{
	int _value;
	Node* _left;
	Node* _right;

	Node(const int x)
		:_value(x)
		, _left(NULL)
		, _right(NULL)
	{}
};

Node* CreateTree(int* a, int n, int& index)
{
	if (index < n && a[index] != '#')
	{
		Node* root = new Node(a[index]);
		root->_left = CreateTree(a, n, ++index);
		root->_right = CreateTree(a, n, ++index);
		return root;
	}
	return NULL;
}

bool IsCompleteBinaryTree(Node* root)
{
	if (root == NULL)
		return false;
	queue<Node*> q;
	bool result = true;
	bool IsLeaf = false;
	q.push(root);
	while (!q.empty())
	{
		Node* node = q.front();
		q.pop();

		if (IsLeaf)
		{
			if (node->_left != NULL || node->_right != NULL)//叶子结点后面的结点都是叶子结点
			{
				result = false;
				break;
			}
		}
		else
		{
			if (node->_left != NULL && node->_right != NULL)
			{
				q.push(node->_left);
				q.push(node->_right);
			}
			else if (node->_left != NULL && node->_right == NULL)
			{
				q.push(node->_left);
				IsLeaf = true;
			}
			else if (node->_left == NULL && node->_right != NULL)
			{
				result = false;
				break;
			}
			else
			{
				IsLeaf = true;
			}
		}
	}
	return result;
}

void Test()
{
	int a[] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6, '#', '#' };
	int index = 0;
	Node* root = CreateTree(a, sizeof(a) / sizeof(a[0]), index);
	cout<<IsCompleteBinaryTree(root)<<endl;
}
int main()
{
	Test();
	system("pause");
	return 0;
}