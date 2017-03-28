#include<iostream>
using namespace std;

template<class T>
struct ListNode
{
	T _data;
	ListNode<T>* _next;
	ListNode<T>* _random;
	
	ListNode()
		
		: _next(NULL)
		, _random(NULL)
	{}

	ListNode(const T& x)
		:_data(x)
		, _next(NULL)
		, _random(NULL)
	{}
};

template <class T>
class ComplexList
{
	typedef ListNode<T> Node;

public:
	ComplexList()
		:_head(NULL)
	{}


	void CreateComplexList()
	{
		//创建5个节点，连接在一起
		Node* Node1, *Node2, *Node3, *Node4, *Node5;
		Node* newNode = new Node(1);
		Node1 = newNode;
		_head = Node1;

		newNode = new Node(2);
		Node2 = newNode;
		Node1->_next = Node2;

		newNode = new Node(3);
		Node3 = newNode;
		Node2->_next = Node3;

		newNode = new Node(4);
		Node4 = newNode;
		Node3->_next = Node4;

		newNode = new Node(5);
		Node5 = newNode;
		Node4->_next = Node5;

		//设置随机指针
		Node1->_random = Node4; //1->4
		Node2->_random = Node5;//2->5
		Node3->_random = Node1;//3->1
		Node4->_random = Node4;//4->2;
		Node5->_random = Node3;//5->3;
	}

	void  _Clone(ComplexList<T>* t)
	{
		CopyNode(t->_head);
		CopyRandom(t->_head);
		_head =  SplitList(t->_head);
	}

	~ComplexList()
	{
		Node* cur = _head;
		while (cur)
		{
			Node * tmp = cur->_next;
			delete cur;
			cur = tmp;
		}
		_head = NULL;
	}
protected:
	
	//拷贝新的节点放在原节点的后面
	void CopyNode(Node* head)
	{
		Node* cur = head;
		while (cur)
		{
			Node* CopyNode = new Node();
			CopyNode->_data = cur->_data;
			CopyNode->_next = cur->_next;
			CopyNode->_random = NULL;

			cur->_next = CopyNode;
			cur = CopyNode->_next;
		}
	}

	//复制随机的指针
	void CopyRandom(Node* head)
	{
		Node* cur = head;
		while (cur)
		{
			Node* CopyNode = cur->_next;
			if (cur->_random)
			{
				CopyNode->_random = cur->_random->_next;
			}
			cur = CopyNode->_next;
		}
	}

	//把一个链表拆分为两个
	Node* SplitList(Node* head)
	{
		Node* cur = head;
		Node* CopyHead = NULL;
		Node* CopyNode = NULL;
		if (cur)
		{
			CopyHead = CopyNode = cur->_next;
			cur->_next = CopyNode->_next;
			cur = CopyNode->_next;
		}
		while (cur)
		{
			CopyNode->_next = cur->_next;
			CopyNode = CopyNode->_next;
			cur->_next = CopyNode->_next;
			cur = cur->_next;
		}

		return CopyHead;
	}
private:
	Node* _head;
};

void Test()
{
	ComplexList<int> t;
	t.CreateComplexList();
	ComplexList<int> t1;
	t1._Clone(&t);
}
int main()
{
	Test();
	system("pause");
	return 0;
}