#include<iostream>
#include<vector>
using namespace std;

template <class K, class V>
struct HashNode
{
	pair<K, V> _kv;
	HashNode<K, V>* _next;

	HashNode(const pair<K, V>& kv)
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

template<class K, class V, class HashFunc, class ValueTypePtr, class ValueTypeRef>
struct __HashTableIterator
{
	typedef HashNode<K, V> Node;
	typedef __HashTableIterator< K, V, HashFunc, ValueTypePtr, ValueTypeRef> Self;

	Node* _node;
	HashTableBucket<K, V, HashFunc>* _ht;

	__HashTableIterator(Node* node, HashTableBucket<K, V, HashFunc>* ht)
		:_node(node)
		, _ht(ht)
	{}

	ValueTypeRef operator*()
	{
		return _node->_kv;
	}

	ValueTypePtr operator->()
	{
		return &(operator*());
	}

	bool operator == (const Self& s)const
	{
		return _node == s._node;
	}

	bool operator !=(const Self& s)const
	{
		return _node != s._node;
	}

	Self& operator++()
	{
		_node = _Next(_node);
		return *this;
	}

protected:
	Node* _Next(Node* node)
	{
		Node* next = node->_next;
		if (next)
			return next;
		else
		{
			size_t index = _ht->_HashFunc(node->_kv.first) + 1;
			for (; index < _ht->_tables.size(); ++index)
			{
				next = _ht->_tables[index];
				if (next)
					return next;
			}
		}
		return NULL;
	}
};

template<class K, class V, class HashFunc = _HashFunc<K>>
class HashTableBucket
{
public:
	typedef HashNode<K, V> Node;
	typedef __HashTableIterator<K, V, HashFunc, pair<K, V>*, pair<K, V>&> Iterator;
	friend Iterator;
public:
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
		pair<Node*, bool> ret = Insert(make_pair(key, V()));
		return ((ret.first)->_kv).second;
	}

	pair<Node*, bool> Insert(const pair<K, V>& kv)
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
				return Iterator(cur, this);
		}
		return Iterator(NULL, this);
	}

	Iterator End()
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

	void _Swap(HashTableBucket<K, V, HashFunc>& ht)
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

template<class K, class V, class HashFunc = _HashFunc<K>>
class UnorderMap
{
	typedef HashNode<K, V> Node;
public:
	typedef typename HashTableBucket<K, V, HashFunc>::Iterator Iterator;

	UnorderMap()
	{}

	pair<Node*, bool> Insert(const K& key, const V& value)
	{
		return _ht.Insert(make_pair(key, value));
	}

	Node* Find(const K& key)
	{
		return _ht.Find(key);
	}

	bool Remove(const K& key)
	{
		return _ht.Remove(key);
	}

	Iterator Begin()
	{
		return _ht.Begin();
	}

	Iterator End()
	{
		return _ht.End();
	}
protected:
		HashTableBucket<K, V, HashFunc> _ht;
};

void TestUnorderMap()
{
	HashTableBucket<int, int> um;
	um.Insert(make_pair(31, 3));
	um.Insert(make_pair(53, 1));
	um.Insert(make_pair(3, 2));
	um.Insert(make_pair(106, 2));
	um.Insert(make_pair(212, 3));
	um.Remove(106);

	UnorderMap<int, int>::Iterator it = um.Begin();

	while (it != um.End())
	{
			cout << it->first << ":" << it->second<<" ";
			++it;
	}
	cout << endl;
}
int main()
{
	TestUnorderMap();
	system("pause");
	return 0;
}