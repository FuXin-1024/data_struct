#include<iostream>
using namespace std;
//二叉树中最远的两个节点的距离
struct Node
{
	int _data;
	Node* _left;
	Node* _right;
	Node (const int x)
		:_data(x)
		, _left(NULL)
		, _right(NULL)
	{}
};

Node* CreateTree(int* a, size_t n, const int& invalid, size_t& index)
{
	Node* root = NULL;
	if ((index < n) && (a[index] != invalid))
	{
		root = new Node(a[index]);
		root->_left = CreateTree(a, n, invalid, ++index);
		root->_right = CreateTree(a, n, invalid, ++index);
	}
	return root;
}

void PrevOrder(Node* root)//根 左 右
{
	if (root == NULL)
		return;
	cout << root->_data << " ";
	PrevOrder(root->_left);
	PrevOrder(root->_right);
}

size_t _MaxDistance(Node* root, int& maxLength)
{
	if (root == NULL)
		return 0;

	int leftDepth = _MaxDistance(root->_left, maxLength);//左子树的深度
	int rightDepth = _MaxDistance(root->_right, maxLength);//右子树的深度

	//判断当前子树的左右深度是否比最远距离lenth大，大则替换；
	int tmp = leftDepth + rightDepth;
	if (tmp > maxLength)
		maxLength = tmp;
	return leftDepth > rightDepth ? leftDepth + 1 : rightDepth + 1;

}

size_t MaxDistance(Node* root)
{
	int maxLength = 0;
	 _MaxDistance(root, maxLength);

	return maxLength;
}

void Test()
{
	size_t index = 0;
	int  a[] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	Node* root = CreateTree(a, sizeof(a) / sizeof(a[0]), '#',index);
	cout << "PrevOrder: "; PrevOrder(root); cout << endl;

	cout << "MaxDistance: " << MaxDistance(root) << endl;
	size_t index1 = 0;
	int  a1[] = { 1,2,'#',3,'#','#',4,5,'#',6,'#',7,'#','#',8 };
	Node* root1 = CreateTree(a1, sizeof(a1) / sizeof(a1[0]), '#', index1);
	cout << "PrevOrder: "; PrevOrder(root1); cout << endl;
	cout << "MaxDistance: " << MaxDistance(root1) << endl;

	size_t index2 = 0;
	int a2[] = { 1, 2, 1, 3, '#', '#', 4, 5, '#', 6, '#', 7, '#', '#', 8 };
	Node* root2 = CreateTree(a2, sizeof(a2) / sizeof(a2[0]), '#', index2);
	cout << "PrevOrder: "; PrevOrder(root2); cout << endl;
	cout << "MaxDistance: " << MaxDistance(root2) << endl;
	
}
int main()
{
	Test();
	system("pause");
	return 0;
}