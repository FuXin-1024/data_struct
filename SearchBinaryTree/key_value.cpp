#include<iostream>
#include<string>
using namespace std;

template<class K,class V>
struct SearchBinaryTreeNode
{	
	K _key;
	V _value;

	SearchBinaryTreeNode<K, V>* _left;
	SearchBinaryTreeNode<K, V>* _right;

	SearchBinaryTreeNode(const K& key, const V& value)
		:_key(key)
		, _value(value)
		, _left(NULL)
		, _right(NULL)
	{}

};

template<class K,class V>
class SearchBinaryTree
{
	typedef SearchBinaryTreeNode<K, V> Node;
public:
	SearchBinaryTree()
		:_root(NULL)
	{}

	bool Insert(const K& key, const V& value)
	{
		return _Insert(_root, key, value);
	}

	Node* Find(const K& key)
	{
		return _Find(_root, key);
	}
protected:
	bool _Insert(Node*& root, const K& key, const V& value)
	{
		if (root == NULL)
		{
			root = new Node(key, value);
			return true;
		}

		if (root->_key < key)
		{
			return _Insert(root->_right, key, value);
		}
		else if (root->_key > key)
		{
			return _Insert(root->_left, key, value);
		}
		else
		{
			return false;
		}
	}

	Node* _Find(Node* root, const K& key)
	{
		if (root == NULL)
			return false;
		if (root->_key < key)
		{
			return _Find(root->_right, key);
		}
		else if (root->_key > key)
		{
			return _Find(root->_left, key);
		}
		else
		{
			return root;
		}
	}
protected:
	Node* _root;
};

void Test()
{
	SearchBinaryTree<string, string> dict;
	dict.Insert("Sort", "ÅÅÐò");
	dict.Insert("One", "Ò»");
	dict.Insert("tree", "Ê÷");

	SearchBinaryTreeNode<string,string>* ret1=dict.Find("Sort");
	ret1->_value = "sort";
	cout << "ret1=" << ret1->_value << endl;
	SearchBinaryTreeNode<string, string>* ret2 = dict.Find("One");
	cout << "ret2=" << ret2->_value << endl;

	SearchBinaryTreeNode<string, string>* ret3 = dict.Find("tree");
	cout << "ret3=" << ret3->_value << endl;

	SearchBinaryTreeNode<string, string>* ret4 = dict.Find("ree");
	cout << "ret4=" << ret4 << endl;
}
int main()
{
	Test();
	system("pause");
	return 0;
}