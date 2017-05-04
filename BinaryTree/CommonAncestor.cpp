#include<iostream>
#include<stack>
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

bool GetPath(Node* root, Node* node, stack<Node*>& s)
{
	if (root == NULL)
		return false;
	if (root->_value == node->_value)
	{
		s.push(root);
		return true;
	}

	s.push(root);
	if (GetPath(root->_left, node, s))
		return true;
	if (GetPath(root->_right, node, s))
		return true;
	s.pop();
	return false;
}
Node* CommonAncestor(Node* root,Node* node1,Node* node2)
{
	if (root == NULL)
		return NULL;

	stack<Node*> s1;
	stack<Node*> s2;

	GetPath(root, node1, s1);
	GetPath(root, node2, s2);
	while (s1.size() > s2.size())
		s1.pop();
	while (s1.size() < s2.size())
		s2.pop();
	while (s1.top() != s2.top())
	{
		s1.pop();
		s2.pop();
	}
	return s1.top();
}

Node* Find(Node* root,const int& value)
{
	if (root == NULL)
		return NULL;
	if (root->_value == value)
		return root;
	Node* tmp = Find(root->_left, value);
	if (tmp)
		return tmp;
	return Find(root->_right, value);
}
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
void Test()
{
		size_t index = 0;
		int  a[] = { 1, 2, 4, '#', '#', 5, '#', '#', 3, 6, '#', '#', 7, '#', '#' };
		Node* root = CreateTree(a, sizeof(a) / sizeof(a[0]), '#',index);
		Node* node1 = Find(root, 5);
		Node* node2 = Find(root, 8);

		Node* ret = CommonAncestor(root, node1, node2);
		cout << ret<< endl;
}
int main()
{
	Test();
	system("pause");
	return 0;
}