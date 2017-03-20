#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;

 //模拟实现 auto_ptr
template <class T>
class AutoPtr
{
public:
	AutoPtr( T* ptr=NULL)
		:_ptr(ptr)
	{
	
	}

	AutoPtr(AutoPtr<T>& p)
	{
		delete _ptr;
		_ptr = p._ptr;
		p._ptr = NULL;

	}

	AutoPtr& operator=(AutoPtr<T>& p)
	{
		if (this！ = &p)
		{
			delete _ptr;
			_ptr = p._ptr;
			p._ptr = NULL;
		}
		return *this;
	}

	~AutoPtr()
	{
		if (_ptr)
		{
			delete _ptr;
			_ptr = NULL;
		}
	}

	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return _ptr;
	}
private:
	T* _ptr;
};

//模拟实现 ScopedPtr
template <class T>
class ScopedPtr
{
public:
	ScopedPtr(T* ptr)
	:_ptr(ptr)
	{

	}

	~ScopedPtr()
	{
		delete _ptr;
	}

	T& operator* ()
	{
		return *_ptr;
	}
	T* operator->()
	{
		return _ptr;
	}
private:
	T* _ptr;
};

// 模拟实现SharePtr------引用计数
template<class T>
class SharedPtr
{
public:
	SharedPtr(T* ptr)
		:_ptr(ptr)
		, RefCount(new int(1))
	{}

	~SharedPtr()
	{
		Release();
	}

	void Release()
	{
		if (--(*RefCount) == 0)
		{
			delete _ptr;
			_ptr = NULL;
			delete RefCount;
			RefCount = NULL;
		}
	}

	SharedPtr(SharedPtr<T>& p)
		:_ptr(p._ptr)
		, RefCount(p.RefCount)
	{
		++(*RefCount);
	}

	SharedPtr<T>& operator=(SharedPtr<T>& p)
	{
		if (this != &p)
		{
			Release();
			_ptr = p._ptr;
			RefCount = p.RefCount;
			++(*RefCount);
		}
		return *this;
	}

	T& operator*()
	{
		return *_ptr;
	}
	T* operator->()
	{
		return _ptr;
	}
private:
	T* _ptr;
	int* RefCount;
};

void Test()
{

	//AutoPtr<int> p1(new int(1));
	//AutoPtr<int> p2(p1);
	SharedPtr<int> p1(new int(1));
	SharedPtr<int> p2(p1);

}
int main()
{
	Test();
	system("pause");
	return 0;
}