#include<iostream>
#include<vector>
#include<string>
#include<assert.h>
using namespace std;

//线性探测法
namespace first
{
	enum State
	{
		EMPTY,
		EXIST,
		DELETE,
	};

	template<class K>
	struct __HashFunc
	{
		size_t operator()(const K& key)
		{
			return key;
		}
	};

	//特化
	template<>
	struct __HashFunc<string>
	{
	public:
		size_t operator()(const string& k)
		{
			return BKDHash(k.c_str());
		}

		static size_t BKDHash(const char* str)
		{
			unsigned int seed = 131;// 31 131 1313 13131 131313
			unsigned int hash = 0;
			while (*str)
			{
				hash = hash*seed + (*str++);
			}
			return(hash & 0x7FFFFFFF);
		}
	};
	template <class K, class V>
	struct HashNode
	{
		pair<K, V> _kv;
		State _s;

		HashNode()
			: _s(EMPTY)
		{}	
	};

	template <class K, class V, class HashFunc = __HashFunc<K>>
	class HashTable
	{
		typedef HashNode<K, V> Node;
	public:
		HashTable()
			:_size(0)
		{}

		HashTable(size_t n)
			:_size(0)
		{
			_tables.resize(n);
		}

		pair<Node*, bool> Insert(const pair<K, V>& kv)
		{
			_Check();
			size_t index = _HashFunc(kv.first);//得到哈希地址
			while (_tables[index]._s == EXIST)
			{
				if (_tables[index]._kv.first == kv.first)
					return make_pair(&_tables[index], false);
				index += 1;
				if (index == _tables.size())//如果到结尾 
					index = 0;//从头重新来过
			}

			_tables[index]._kv = kv;
			_tables[index]._s = EXIST;
			++_size;
			return make_pair(&_tables[index], true);
		}
		Node* Find(const K& key)
		{
			size_t index = _HashFunc(key);
			while (_tables[index]._s != EMPTY)
			{
				if (_tables[index]._kv.first == key)
				{
					if (_tables[index]._s == EXIST)
						return &_tables[index];
					else
						return NULL;
				}
				index += 1;
				if (index == _tables.size())
					index = 0;
			}
			return NULL;
		}

		bool Remove(const K& key)
		{
			Node* node = Find(key);
			if (node != NULL)
			{
				node->_s = DELETE;//将该位置的状态改为删除后的状态 
				--_size;//存入数据的个数--
				return true;
			}
			return false;
		}
		V& operator[](const K& key)
		{
			pair < Node*, bool > ret = Insert(make_pair(key, V()));
			return ((ret.first)->_kv).second;
		}
	protected:

		size_t _HashFunc(const K& key)
		{
			//return key % _tables.size();
			HashFunc hf;
			return hf(key) % _tables.size();
		}

		void Swap(HashTable<K, V>& ht)
		{
			swap(_size, ht._size);
			_tables.swap(ht._tables);
		}
		void _Check()
		{
			if (_tables.size() == 0)
			{
				_tables.resize(53);
			}
			else if (_size * 10 / _tables.size() == 7)
			{
				size_t newSize = _GetNextprime(_tables.size());
				HashTable<K, V, HashFunc> newHT(newSize);
				for (size_t i = 0; i < _tables.size(); ++i)
				{
					if (_tables[i]._s == EXIST)
					{
						newHT.Insert(_tables[i]._kv);
					}
				}
				Swap(newHT);
			}
		}
		//得到下个素数，，，，，一般情况下，哈希表的长度都是素数 ，，，
		size_t  _GetNextprime(size_t n)
		{
			const int _PrimeSize = 28;//下面为一个素数表 
			static const unsigned long _PrimeList[_PrimeSize] =
			{
				53ul, 97ul, 193ul, 389ul, 769ul,
				1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
				49157ul, 98317ul, 196613ul, 393241ul,
				786433ul,
				1572869ul, 3145739ul, 6291469ul, 12582917ul,
				25165843ul,
				50331653ul, 100663319ul, 201326611ul, 402653189ul,
				805306457ul,
				1610612741ul, 3221225473ul, 4294967291ul
			};
			for (size_t i = 0; i< _PrimeSize; ++i)
			{
				if (n < _PrimeList[i])
					return _PrimeList[i];//找到要找的下一个素数 
			}
			assert(false);
		}
	protected:
		vector<Node> _tables;
		size_t _size;
	};
}



//开链法
namespace second
{
	template <class K,class V>
	struct HashNode
	{
		pair<K, V> _kv;
		HashNode<K, V>* _next;
	
		HashNode(const pair<K,V>& kv)
			:_kv(kv)
			, _next(NULL)
		{}
	};
	template <class K>
	struct _HashFunc
	{
		size_t operator()(const K& key)
		{
			return key;
		}
	};
	
	//特化
	template<>
	struct _HashFunc<string>
	{
		size_t operator()(const string& key)
		{
			return BKDRHash(key.c_str());
		}
	protected:
		//字符串哈希处理算法
		static size_t BKDRHash(const char* str)
		{
			unsigned int seed = 131;// 31 131 1313 13131 131313
			unsigned int hash = 0;
			while (*str)
			{
				hash = hash*seed + (*str++);
			}
			return(hash & 0x7FFFFFFF);
		}
	};

	//声明
	template<class K, class V, class HashFunc>
	class HashTableBucket;

	template<class K,class V,class HashFunc,class ValueTypePtr,class ValueTypeRef>
	struct __HashTableIterator
	{
		typedef HashNode<K, V> Node;
		typedef __HashTableIterator<K, V, HashFunc, ValueTypePtr, ValueTypeRef> Self;
		typedef pair<K, V> ValueType;
		Node* _node;
		HashTableBucket<K, V,HashFunc>* _ht;

		__HashTableIterator(Node* node, HashTableBucket<K, V, HashFunc>* ht)
			:_node(node)
			, _ht(ht)
		{}

		ValueType operator*()
		{
			return _node->_kv;
		}

		ValueType operator->()
		{
			return &(operator*());
		}

		bool operator!=(const Self& s)const
		{
			return _node != s._node;
		}
		bool operator==(const Self& s)const
		{
			return _node == s._node;
		}

		Self&  operator++()
		{
			_node = _Next(_node);
			return *this;
		}

	protected:
		Node* _Next(Node* node)
		{
			Node* next = node->_next;
			if (next)
			{
				return next;
			}
			else
			{
				size_t index = _ht->_HashFunc(_node->_kv.first) + 1;
				for (; index < (_ht->_tables.size()); ++index)
				{
					next = _ht->_tables[index];
					if (next)
						return next;
				}
			}
			return NULL;
		}
	};

	template<class K,class V,class HashFunc=_HashFunc<K>>
	class HashTableBucket
	{
		typedef HashNode<K, V> Node;
		friend struct __HashTableIterator<K, V, HashFunc, pair<K, V>*, pair<K, V>&>;
		
	public:
		typedef __HashTableIterator<K, V, HashFunc, pair<K, V>*, pair<K, V>&> Iterator;
		typedef __HashTableIterator<K, V, HashFunc, const pair<K, V>*, const pair<K, V>&> ConstIterator;
		friend Iterator;
		friend  ConstIterator;
		HashTableBucket()
			:_size(0)
		{}
	
		HashTableBucket(const size_t n)
			:_size(0)
		{
			_tables.resize(n);
		}
	
		~HashTableBucket()
		{
			_Clear();
			_size = 0;
		}
	
		V& operator[](const K& key)
		{
			pair<Node* ,bool> ret = Insert(make_pair(key, V()));
			return ((ret.first)->_kv).second;
		}
	
		pair<Node*,bool> Insert(const pair<K, V>& kv)
		{
			_Check();
			size_t index = _HashFunc(kv.first);
			Node* cur = _tables[index];
			
			while (cur)
			{
				if (cur->_kv.first == kv.first)
				{
					return make_pair(cur, false);
				}
				cur = cur->_next;
			}
			//头插
			Node* newNode = new Node(kv);
			newNode->_next = _tables[index];
			_tables[index] = newNode;
			++_size;
			return make_pair(_tables[index], true);
		}
	
		Node* Find(const K& key)
		{
			size_t index = _HashFunc(key);
			Node* cur = _tables[index];
			while (cur)
			{
				if (cur->_kv.first == key)
					return cur;
				cur = cur->_next;
			}
			return false;
		}
	
		bool Remove(const K& key)
		{
			size_t index = _HashFunc(key);
			Node* cur = _tables[index];
			Node* parent = NULL;
			if (cur == NULL)
				return false;
			while (cur)
			{
				if (cur->_kv.first == key)
				{
					if (cur == _tables[index])
					{
						_tables[index] = cur->_next;
					}
					else
					{
						parent->_next = cur->_next;
					}
					delete cur;
					cur = NULL;
					--_size;
					break;
				}
				parent = cur;
				cur = cur->_next;
			}
			return false;
		}
		void Print()
		{
			for (size_t i = 0; i < _tables.size(); ++i)
			{
				Node* cur = _tables[i];
				while (cur)
				{
					cout << cur->_kv.first << " ";
					cur = cur->_next;
				}
			}
			cout << endl;
		}

		Iterator Begin()
		{
			for (size_t i = 0; i < _tables.size(); ++i)
			{
				Node* cur = _tables[i];
				if (cur)
				{
					return Iterator(cur, this);
				}
			}
			return Iterator(NULL,this);
		}

		ConstIterator CBegin()const
		{
			for (size_t i = 0; i < _tables.size(); ++i)
			{
				Node* cur = _tables[i];
				if (cur)
				{
					return Iterator(cur, this);
				}
			}
			return Iterator(NULL, this);
		}

		Iterator End()
		{
			return Iterator(NULL, this);
		}

		ConstIterator CEnd() const
		{
			return Iterator(NULL, this);
		}

	protected:
		void _Check()
		{
			if (_tables.size() == 0 || _size / _tables.size() >= 1)
			{
				size_t newSize = _GetPrimenum(_tables.size());
				HashTableBucket<K, V, HashFunc> newTable(newSize);
				for (size_t i = 0; i < _tables.size(); ++i)
				{
					Node* cur = _tables[i];
					while (cur)
					{
						newTable.Insert(make_pair(((cur->_kv).first), ((cur->_kv).second)));
						cur = cur->_next;
					}
				}
				_Swap(newTable);
			}
		}
	
		void _Swap(HashTableBucket<K,V,HashFunc>& ht)
		{
			swap(_size, ht._size);
			_tables.swap(ht._tables);
		}
		size_t _HashFunc(const K& key)
		{
			HashFunc hf;
			return hf(key) % _tables.size();
		}
		size_t _GetPrimenum(const size_t& sz)
		{
			const int Primesize = 28;
			static const unsigned long Primenum[Primesize] =
			{
				53ul, 97ul, 193ul, 389ul, 769ul,
				1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
				49157ul, 98317ul, 196613ul, 393241ul,
				786433ul,
				1572869ul, 3145739ul, 6291469ul, 12582917ul,
				25165843ul,
				50331653ul, 100663319ul, 201326611ul, 402653189ul,
				805306457ul,
				1610612741ul, 3221225473ul, 4294967291ul
			};
			for (int i = 0; i < Primesize; ++i)
			{
				if (Primenum[i] > sz)
				{
					return Primenum[i];
				}
			}
			return sz;
		}
		void _Clear()
		{
			for (size_t i = 0; i < _tables.size(); ++i)
			{
				Node* cur = _tables[i];
				while (cur)
				{
					Node* del = cur;
					cur = cur->_next;
					delete del;
				}
				_tables[i] = NULL;
			}
		}
	protected:
		vector<Node*> _tables;
		size_t _size;
	};
}
void TestFirst()
{
	int a[] = { 89, 18, 49, 58, 9 };
	first::HashTable<int, int> ht;
	for (size_t i = 0; i < sizeof(a) / sizeof(a[0]); ++i)
	{
	ht.Insert(make_pair(a[i], i));
	}
	ht.Insert(make_pair(10, 1));
	ht.Insert(make_pair(11, 1));
	ht.Insert(make_pair(12, 1));
	ht.Insert(make_pair(13, 1));
	ht.Insert(make_pair(14, 1));
	ht.Remove(13);
	first::HashTable<string, string, first::__HashFunc<string>> ht1;
	ht1.Insert(make_pair("Left", "左边"));
	ht1.Insert(make_pair("Left", "剩余"));
	ht1["Left"]="剩余";
}

//void PrintSecond(second::HashTableBucket<int, int>& ht)
//{
//	second::HashTableBucket<int, int>::Iterator it = ht.Begin();
//	while (it != ht.End())
//	{
//		cout << it->first << " ";
//		++it;
//	}
//	cout << endl;
//}
void TestSecond()
{
	
	int a[] = { 89, 18, 49, 58, 9 };
	second::HashTableBucket<int, int> ht;
	for (size_t i = 0; i < sizeof(a) / sizeof(a[0]); ++i)
	{
		ht.Insert(make_pair(a[i], i));
	}

	ht.Insert(make_pair(10, 1));
	ht.Insert(make_pair(53, 1));
	ht.Insert(make_pair(54, 1));
	ht.Insert(make_pair(55, 1));
	ht.Insert(make_pair(56, 1));
	ht.Insert(make_pair(106, 1));
	ht.Insert(make_pair(212, 1));

	ht.Print();
	
	second::HashTableBucket<int, int>::Iterator it = ht.Begin();
	while (it != ht.End())
	{
		cout << it->first << " ";
		++it;
	}
	cout << endl;


	//PrintSecond(ht);
	/*ht.Remove(106);
	ht.Print();*/
	//
	second::HashTableBucket<string, string, second::_HashFunc<string>> ht1;
	ht1.Insert(make_pair("Left", "左边"));
	ht1.Insert(make_pair("Left", "剩余"));
	//ht1.Print();
	ht1["Left"] = "剩余";
	//ht1.Print();
}
int main()
{
	//TestFirst();
	TestSecond();
	system("pause");
	return 0;
}