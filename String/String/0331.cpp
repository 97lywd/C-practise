#include<iostream>
#include<assert.h>
using namespace std;
class String {
public:
	typedef char* iterator;
	typedef const char* iterator;
	String(char* str = "")
	{
		assert(str != nullptr);
		_size = strlen(str);
		_str = new char[_size + 1];
		_capacity = _size;
	}
	String(const String& s)
		:_str(nullptr)
		,_size(0)
		,_capacity(0)
	{
		String tmp(s._str);
		Swap(tmp);
	}
	void Swap(String& s)
	{
		swap(_str, s._str);
		swap(_size, s._size);
		swap(_capacity, s._capacity);
	}
	String& operator=(String s)
	{
		Swap(s);
		return *this;
	}
	char& operator[](size_t pos)
	{
		assert(pos < _size);
		return _str[pos];
	}
	iterator begin()
	{
		return _str;
	}
	iterator end()
	{
		return _str + _size;
	}
	const_iterator begin()const
	{
		return _str;
	}
	const_iterator end()const
	{
		return _str + _size;
	}
	size_t Size()const
	{
		return _size;
	}
	~String()
	{
		if (_str)
		{
			delete[]_str;
			_str = nullptr;
			_size = _capacity = 0;
		}
	}
	char* c_str()
	{
		return _str;
	}
	void PushBack(char c)
	{
		if (_size == _capacity)
		{
			size_t newC = (_capacity == 0 ? 15 : 2 * _capacity);
			Reserve(newC);
		}
		_str[_size++] = c;
		_str[_size] = '\0';
	}
	void Reserve(size_t n)
	{
		if (n > _capacity)
		{
			char* tmp = new char[n + 1];
			strcpy(tmp, _str);
			delete _str;
			_str = tmp;
			_capacity = n;
		}
	}
	void Insert(size_t pos, const char* str)
	{
		assert(pos <= _size);
		//ÔöÈÝ
		size_t len = strlen(str);
		if (_size + len >_capacity) {
			Reserve(_size + len);
		}
		//Å²¶¯strlen(str)¸ö×Ö·û

	}
private:
	char* _str;
	size_t _size;
	size_t _capacity;
};