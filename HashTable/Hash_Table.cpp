#include<iostream>
#include<vector>
#include<string>
#include<assert.h>
using namespace std;

//线性探测法
enum STATE
{
	EMPTY,
	EXIST,
	DELETE,
};

template<class K>
struct __HashFunc
{
	size_t operator()(const K& k)
	{
		return k;
	}
};

//特化
template<>
struct __HashFunc<string>
{
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
	STATE  _s;

	HashNode()
		:_s(EMPTY)
	{}
};

template<class K, class V, class HashFunc = __HashFunc<K>>
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
		_CheckCapacity();
		size_t index = _GetIndex(kv.first);
		while (_tables[index]._s == EXIST)
		{
			//检查是否存在
			if (_tables[index]._kv.first == kv.first)
				return make_pair(&_tables[index], false);
			++index;
			if (index == _tables.size())
				index = 0;
		}
		_tables[index]._kv = kv;
		_tables[index]._s = EXIST;
		++_size;
		return make_pair(&_tables[index], true);
	}

	Node* Find(const K& key)
	{
		size_t index = _GetIndex (key);
		while (_tables[index]._s != EMPTY)
		{
			if (_tables[index]._kv.first == key)
			{
				if (_tables[index]._s == EXIST)
					return &_tables[index];
				else
					return NULL; 
			}
			++index;
			if (index == _tables.size())
				index = 0;
		}
		return NULL;
	}

	bool Remove(const K& key)
	{
		Node* del = Find(key);
		if (del != NULL)
		{

			del->_s = DELETE;
			--_size;
			return true;
		}
		return false;

	}

	void Print()
	{
		size_t size = _tables.size();
		for (size_t i = 0; i < size; ++i)
		{
			if (_tables[i]._s == EXIST)
			{
				cout << _tables[i]._kv.first << "-- "<<_tables[i]._kv.second<<"   ";
			}
		}
		cout << endl;
	}

	V& operator[](const K& key)
	{
		pair<Node*, bool> ret = Insert(make_pair(key, V()));
		return ((ret.first)->_kv).second;
	}
protected:
	size_t _GetIndex(const K& key)
	{
		HashFunc k;
		return k(key) % _tables.size();
	}

	void Swap(HashTable<K, V> ht)
	{
		swap(_size, ht._size);
		_tables.swap(ht._tables);
	}
	void _CheckCapacity()
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
			this->Swap(newHT);
		}
	}

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

void TestHash()
{
		int a[] = { 89, 18, 49, 58, 9 };
		HashTable<int, int> ht;
		for (size_t i = 0; i < sizeof(a) / sizeof(a[0]); ++i)
		{
		ht.Insert(make_pair(a[i], i));
		}
		ht.Insert(make_pair(10, 1));
		ht.Insert(make_pair(11, 1));
		ht.Insert(make_pair(12, 1));
		ht.Insert(make_pair(13, 1));
		ht.Insert(make_pair(14, 1));
		ht.Print();
		cout<<ht.Find(10)<<endl;
		ht.Remove(10);
		ht.Print();

		HashTable<string, string,__HashFunc<string>> ht1;
		ht1.Insert(make_pair("Left", "左边"));
		ht1.Insert(make_pair("Left", "剩余"));
		ht1.Print();
		ht1["Left"] = "剩余";
		ht1.Print();
}
int main()
{
	TestHash();
	system("pause");
	return 0;
}