//#include<iostream>
//using namespace std;
//
//struct Node
//{
//	int _value;
//	Node* _next;
//	Node* _random;
//
//	Node()
//		:_next(NULL)
//		, _random(NULL)
//	{}
//
//	Node(const int x)
//		:_value(x)
//		, _next(NULL)
//		, _random(NULL)
//	{}
//};
//
////复制结点
//void CloneNodes(Node* head)
//{
//	Node* cur = head;
//	while (cur != NULL)
//	{
//		Node* CloneNode = new Node();
//		CloneNode->_value = cur->_value;
//		CloneNode->_next = cur->_next;
//		CloneNode->_random = NULL;
//
//		cur->_next = CloneNode;
//		cur = CloneNode->_next;
//	}
//}
//
////复制Random
//void CloneRandom(Node* head)
//{
//	Node* cur = head;
//	while (cur)
//	{
//		Node* CloneNode = cur->_next;
//		if (cur->_random != NULL)
//		{
//			CloneNode->_random = cur->_random->_next;
//		}
//		cur = CloneNode->_next;
//	}
//}
//
////拆分两个链表
//Node* ReconnectNodes(Node* head)
//{
//	Node* cur = head;
//	Node* CloneHead = NULL;
//	Node* CloneNode = NULL;
//
//	if (cur)
//	{
//		CloneHead = CloneNode = cur->_next;
//		cur->_next = CloneNode->_next;
//		cur = cur->_next;
//	}
//	while (cur)
//	{
//		CloneNode->_next = cur->_next;
//		CloneNode = CloneNode->_next;
//		cur->_next = CloneNode->_next;
//		cur = cur->_next;
//	}
//	return CloneHead;
//}
//
//Node* Clone(Node* head)
//{
//	if (head == NULL)
//		return NULL;
//	CloneNodes(head);
//	CloneRandom(head);
//	ReconnectNodes(head);
//}
//
//void PrintList(Node* head)
//{
//	if (head == NULL)
//		return;
//	Node* cur = head;
//	while (cur)
//	{
//		cout << cur->_value << " ";
//		cur=cur->_next;
//	}
//	cout << endl;
//}
//void Test()
//{
//	 Node* head = new Node(1);
//	Node* n1 = new Node(2);
//	head->_next = n1;
//	Node* n2 = new Node(3);
//	n1->_next = n2;
//	Node* n3 = new Node(4);
//	n2->_next = n3;
//	Node* n4 = new Node(5);
//	n3->_next = n4;
//	n4->_next = NULL;
//
//	head->_random = n2;
//	n1->_random = n3;
//	n2->_random = NULL;
//	n3->_random = n4;
//	n4->_random = head;
//	cout << " Befor Clone: ";
//	PrintList(head);
//
//	Node* CloneHead = Clone(head);
//	cout << " After Clone: ";
//	PrintList(CloneHead);
//}
//int main()
//{
//	Test();
//	system("pause");
//	return 0;
//}