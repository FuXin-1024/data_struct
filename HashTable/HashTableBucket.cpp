#include<iostream>
#include<vector>
using namespace std;

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

//ÌØ»¯
template<>
struct _HashFunc<string>
{
	size_t operator()(const string& key)
	{
		return BKDRHash(key.c_str());
	}
protected:
	//×Ö·û´®¹þÏ£´¦ÀíËã·¨
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
template<class K,class V,class HashFunc=_HashFunc<K>>
class HashTableBucket
{
	typedef HashNode<K, V> Node;
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
		//Í·²å
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

void TestHashTableBucket()
{
	int a[] = { 89, 18, 49, 58, 9 };
	HashTableBucket<int, int> ht;
	for (size_t i = 0; i < sizeof(a) / sizeof(a[0]); ++i)
	{
		ht.Insert(make_pair(a[i], 1));
	}
	ht.Insert(make_pair(10, 1));
	ht.Insert(make_pair(53, 1));
	ht.Insert(make_pair(54, 1));
	ht.Insert(make_pair(55, 1));
	ht.Insert(make_pair(56, 1));
	ht.Insert(make_pair(106, 1));
	ht.Insert(make_pair(212, 1));
	ht.Print();
	ht.Remove(53);
	ht.Remove(212);
	ht.Remove(106);
	ht.Remove(49);
	ht.Print();

	HashTableBucket<string, string,_HashFunc<string>> ht1;
	ht1.Insert(make_pair("Left", "×ó±ß"));
	ht1.Insert(make_pair("Left", "Ê£Óà"));
	ht1["Left"] = "Ê£Óà";
}
int main()
{
	TestHashTableBucket();
	system("pause");
	return 0;
}