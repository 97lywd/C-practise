#include<assert.h>
#include<iostream>
using namespace std;
template<class T>
class Vector {
public:
	typedef T* iterator;
	Vector()
		:_start(nullptr)
		, _finish(nullptr)
		, _endOfStorage(nullptr)
	{}
	size_t Size()
	{
		return _finish - _start;
	}
	size_t Capacity()
	{
		return _endOfStorage - _start;
	}
	iterator begin()
	{
		return _start;
	}
	iterator end()
	{
		return _finish;
	}
	void Reserve(size_t n)
	{
      if (n > Capacity())
		{
			size_t size = Size();
			T* tmp  = new T[n];
			for (int i = 0; i < size; i++) 
			{
				tmp[i] = _start[i];
			}
			_start = tmp;
		    _finish= _start + size;
			_endOfStorage = _start + n;
		}
	}
	void pushback(const T&val)
	{
		if (_finish == _endOfStorage)
		{
			size_t newCapacity = Capacity() == 0 ? 1 : Capacity() * 2;
			Reserve(newCapacity);
		}
		*_finish = val;
		++_finish;
	}
	void Insert(T* pos, const T&val)
	{
		assert(pos <= _finish && pos >= _start);
		if (_finish == _endOfStorage)
		{
			size_t size = Size();
			size_t newCapacity = Capacity() == 0 ? 1 : Capacity() * 2;
			Reserve(newCapacity);
			pos = _start + size;
		}
		iterator end = _finish - 1;
		while (pos <= end) {
			*end = *(end - 1);
			end--;
		}
		*pos = val;
		_finish++;
	}
	
	iterator Erase(iterator pos)
	{
		assert(pos < _finish && pos >= _start);
		iterator begin = pos + 1;
		while (begin < _finish) {
			*(begin - 1) = *(begin);
			begin++;
		}
		_finish--;
		return pos;
	}
	void Resize(size_t n, const T&val = T())
	{
		if (n <= Size())
		{
			_finish = _start + n;
		}
		else {
			if (n > Capacity())
			{
				Reserve(n);
			 }
			while (_finish != _start + n)
			{
				*_finish = val;
				_finish++;
			}
		}
	}
	~Vector()
	{
		delete[]_start;
		_start = _endOfStorage = _finish;
	}
private:
	T*_start;   //指向数据块的开始
	T*_finish;     //指向有效数据的尾
	T*_endOfStorage;    //指向存储容量的尾
};
template<class T>
void PrintVector(Vector<T>& v)
{
	for (auto& e : v)
	{
		cout << e << "";
	}
	cout << endl;
}
int main()
{
	Vector<int>v1;
	v1.Insert(v1.begin(), 1);
	v1.Insert(v1.begin(), 2);
	v1.Insert(v1.begin(), 3);
	v1.Erase(v1.begin());
	v1.Resize(10);
	PrintVector(v1);
	system("pause");
	return 0;
}
