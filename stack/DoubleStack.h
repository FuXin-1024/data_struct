#include<iostream>
using namespace std;
//一个数组实现两个栈
template<class T>
class DoubleStack
{
public:
	DoubleStack()
		:_a(NULL)
		, _top1(0)
		, _top2(0)
		, _capacity(0)
	{
		_CheckCapacity();
	}

	~DoubleStack()
	{
		if (_a)
			delete[] _a;
	}

	void Push1(const T& x)
	{
		_CheckCapacity();
		_a[_top1++] = x;
	}

	void Push2(const T& x)
	{
		_CheckCapacity();
		_a[_top2--] = x;
	}

	void Pop1()
	{
		if (_top1 > 0)
			--_top1;
	}

	void Pop2()
	{
		if (_top2 < _capacity - 1)
			++_top2;
	}
	size_t Size1()
	{
		return _top1;
	}

	size_t Size2()
	{
		return _capacity - 1 - _top2;
	}

	bool Empty1()
	{
		return _top1 == 0;
	}

	bool Empty2()
	{
		return _top2 == _capacity - 1;
	}

	T& Top1()
	{
		if (_top1>0)
			return _a[_top1 - 1];
	}

	T& Top2()
	{
		if (_top2 < _capacity - 1)
			return _a[_top2 + 1];
	}

protected:
	void _CheckCapacity()
	{
		if (_a == NULL)
		{
			_capacity += 3;
			_a = new T[_capacity];
			_top2 = _capacity - 1;
			return;
		}
		if (_top1 == _top2)
		{
			size_t oldCapacity = _capacity;
			_capacity *= 2;
			T* tmp = new T[_capacity];

			for (size_t i = 0; i < _top1; ++i)
			{
				tmp[i] = _a[i];
			}

			for (size_t j = oldCapacity - 1, i = _capacity - 1; j>_top2; j--, i--)
			{
				tmp[i] = _a[j];
			}
			delete[] _a;
			_a = tmp;
			_top2 += _capacity / 2;
		}
	}
protected:
	T* _a;
	size_t _top1;
	size_t _top2;
	size_t _capacity;
};

void Test()
{
	DoubleStack<int> s;
	s.Push1(1);
	s.Push1(2);
	s.Push1(3);
	s.Push1(4);
	s.Push1(5);

	s.Push2(10);
	s.Push2(9);
	s.Push2(8);
	s.Push2(7);
	cout << "s1:" << s.Size1() << endl;;
	cout << "s2:" << s.Size2() << endl;
	while (!s.Empty1())
	{
		cout << s.Top1()<<" ";
		s.Pop1();
	}
	cout << endl;
	while (!s.Empty2())
	{
		cout << s.Top2()<<" ";
		s.Pop2();
	}
	cout << endl;
}
