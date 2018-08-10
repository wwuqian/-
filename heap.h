#pragma once
#include<vector>

template<class T>
//仿函数
struct Less  //小堆
{
	bool operator()(const T& left,const T& right)
	{
		return left < right;
	}
};

template<class T>
struct Greater   //大堆
{
	bool operator()(const T& left,const T& right)
	{
		return left > right;
	}
};

template<class T,class Compare = Less<T>>
class Heap
{
public:
	Heap()
	{}

	Heap(const T* a,size_t n)
	{
		//预先分配n个空间
		_a.reserve(n);
		for(size_t i = 0;i < n;++i)
			_a.push_back(a[i]);
		//建堆 O(N*lgN)
		for(int i = (_a.size()-2)/2;i >= 0;--i)
			_AdjustDown(i);
	}

	void Push(const T& x)
	{
		_a.push_back(x);
		_AdjustUp(_a.size()-1);
	}

	void Pop()
	{
		assert(!_a.empty());
		swap(_a[0],_a[_a.size()-1]);
		_a.pop_back();
		_AdjustDown(0);
	}

	const T& Top()
	{
		assert(!_a.empty());
		return _a[0];
	}

	size_t Size()
	{
		return _a.size();
	}

	bool Empty()
	{
		return _a.empty();
	}

	void Print()
	{
		cout << "堆为：";
		for(int i = 0;i < _a.size();++i)
			cout << _a[i] << " ";
		cout << endl;
	}

protected:
	void _AdjustDown(int root)
	{
		Compare com;
		int parent = root;
		int child = parent*2 + 1;
		while(child < _a.size())
		{
			if(child+1 < _a.size() && com(_a[child+1],_a[child]))
				++child;
			if(com(_a[child],_a[parent]))
			{
				swap(_a[child],_a[parent]);
				parent = child;
				child = parent*2 + 1;
			}
			else
				break;
		}
	}

	void _AdjustUp(int child)
	{
		Compare com;
		int parent = (child-1)/2;
		while(parent >= 0)
		{
			if(com(_a[child],_a[parent]))
			{
				swap(_a[child],_a[parent]);
				child = parent;
				parent = (child-1)/2;
			}
			else
				break;
		}
	}

protected:
	vector<T> _a;
};

////////////////////////////////////////////////
////测试Heap的函数
////////////////////////////////////////////////
void TestHeap()
{
	int a[] = {12,1,5,8,25,27,18,20,16,19,12};
	Heap<int,Less<int>> heap(a,sizeof(a)/sizeof(a[0]));
	heap.Print();
}





