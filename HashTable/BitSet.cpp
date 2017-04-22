#include<iostream>
#include<vector>
using namespace std;

class BitSet
{
public:
	BitSet(size_t rang)
	{
		_a.resize((rang >> 5) + 1);
	}

	void Set(size_t num)
	{
		size_t index = num >> 5;
		size_t pos = num % 5;
		_a[index] |= (1 << pos);
	}

	void Reset(size_t num)
	{
		size_t index = num >> 5;
		size_t pos = num % 5;
		_a[index] &= ~(1 << pos);
	}

	bool Test(size_t num)
	{
		size_t index = num >> 5;
		size_t pos = num % 5;
		return _a[index] & (1 << pos);
	}
protected:
	vector <int> _a;
};

void BitSetTest()
{
	BitSet b(1000);
	b.Set(1);
	b.Set(33);
}
int main()
{
	BitSetTest();
	system("pause");
	return 0;
}