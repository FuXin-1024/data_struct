#include<iostream>
#include<assert.h>
#include<vector>
using namespace std;

template<class T>
class Heap
{
public:
	Heap(T* a, size_t n)
	{
		_a.reserve(n);
		for (size_t i = 0; i < n; ++i)
		{
			_a.push_back(a[i]);
		}

		for (int j = (_a.size() - 2) / 2; j >= 0; --j)
		{
			_AdjustDown(j);
		}
	}

	
protected:
	//向下调整
	void _AdjustDown(int root)//第一个非叶子节点
	{
		int parent = root;
		int child = parent * 2 + 1;
		while (child < _a.size())
		{
			if (child + 1 < _a.size() && _a[child] < _a[child + 1])
				++child;
			if (_a[child] > _a[parent])
			{
				swap(_a[child], _a[parent]);
				parent = child;
				child = parent * 2 + 1;
			}
			else
				break;
		}
	}
protected:
	vector<T> _a;
};

void HeapTest()
{
	int a[] = { 10, 11, 13, 12, 16, 18, 15, 17, 14, 19 };
	int n = sizeof(a) / sizeof(a[0]);
	Heap<int> hp(a, n);
}
int main()
{
	HeapTest();
	system("pause");
	return 0;
}