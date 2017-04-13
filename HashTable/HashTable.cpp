#include<iostream>
#include<vector>
using namespace std;
enum State
{
	EMPTY,
	EXIST,
	DELETE,
};
template <class K,class V>
struct HashNode
{
	pair<K, V> _kv;
	State _s;
};

template <class K, class V>
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

	bool Insert(const pair<K, V>& kv)
	{
		_Check();
		size_t index = _HashFunc(kv.first);
		while (_tables[index]._s == EXIST)
		{
			if (_tables[index]._kv.first == kv.first)
				return false;
			index += 1;
			if (index == _tables.size())
				index = 0;
		}

		_tables[index]._kv = kv;
		_tables[index]._s = EXIST;
		++_size;
		return true;
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
					retrun NULL;
			}
			index += 1;
			if (index = _tables.size())
				index = 0;
		}
		return NULL;
	}

	void Remove(K& key)
	{
		if (find(key)!=NULL)

	}
protected:
	size_t _HashFunc(const K& key)
	{
		return key % _tables.size();
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
			_tables.resize(10);
		}
		else if (_size * 10 / _tables.size() == 7)
		{
			size_t newSize = _tables.size() * 2;
			HashTable<K, V> newHT(newSize);
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
protected:
	vector<Node> _tables;
	size_t _size;
};
void Test()
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
}
int main()
{
	Test();
	system("pause");
	return 0;
}