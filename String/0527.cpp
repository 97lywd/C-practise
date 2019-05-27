#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <assert.h>
using namespace std;
class String
{
public:

	typedef char* Iterator;
	typedef const char* const_Iterator;

	String(const char* str = "")
	{
		size_t len = strlen(str);
		_size = len;
		_capacity = _size;
		_str = new char[_capacity + 1];
		strcpy(_str, str);
	}

	

	String(const String& s)
		:_str(nullptr)
		, _size(0)
		, _capacity(0)
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

	void pushBack(const char c)
	{
		if (_size == _capacity)
		{
			size_t newC = _capacity == 0 ? 15 : 2 * _capacity;
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
			if (_str)
			{
				strcpy(tmp, _str);
				delete[] _str;
			}
			_str = tmp;
			_capacity = n;
		}
	}

	void Resize(size_t n, char c = '\0')
	{
		if (n < _size)
		{
			_size = n;
			_str[_size] = '\0';
			return;
		}
		if (n > _capacity)
		{
			size_t newC = _capacity == 0 ? 15 : 2 * _capacity;
			Reserve(newC);
		}
		for (int i = _size; i < n; i++)
		{
			_str[i] = c;
		}
		_size = n;
		_str[_size] = '\0';
	}

	void Insert(size_t pos, const char c)
	{
		assert(pos <= _size);
		if (_size == _capacity)
		{
			size_t newC = _capacity == 0 ? 15 : 2 * _capacity;
			Reserve(newC);
		}
		size_t end = _size;
		while (end > pos)
		{
			_str[end] = _str[end - 1];
			--end;
		}

		_str[pos] = c;
		_str[++_size] = '\0';

	}

	void Insert(size_t pos, const char* str)
	{
		int len = strlen(str);
		assert(pos <= _size);
		if (_size + len > _capacity)
		{
			Reserve(_size + len);
		}
		//ÔªËØÒÆ¶¯
		size_t end = _size + len;
		while (end > pos + len - 1)  
		{
			_str[end] = _str[end - len];
			--end;
		}

		//²åÈë×Ö·û´®
		while (*str)
		{
			_str[pos++] = *str;
			++str;
		}
		_size += len;
	}

	void Erase(size_t pos, size_t n)
	{
		assert(pos < _size);
		if (n >= _size - pos)
		{
			_size = pos;
			_str[_size] = '\0';
			return;
		}
		size_t begin = pos + n;
		while (begin <= _size)
		{
			_str[pos++] = _str[begin];
			++begin;
		}

		_size -= n;
	}

	void pop_back()
	{
		if (_size > 0)
		{
			--_size;
			_str[_size] = '\0';
		}
	}

	void Append(const char* str)
	{
		Insert(_size, str);
	}

	String& operator+=(char c)
	{
		pushBack(c);
		return *this;
	}
	String& operator+=(const char* str)
	{
		Append(str);
		return *this;
	}
	String& operator+=(const String& s)
	{

		Insert(_size, s._str);
		return *this;
	}

	size_t find(size_t pos, char c)
	{
		for (int i = pos; i < _size; i++)
		{
			if (_str[i] == c)
				return i;
		}
		return -1;
	}
	size_t find(size_t pos, const char* str)
	{
		char* ret = strstr(_str + pos, str);
		if (ret != NULL)
			return ret - _str;
		else
			return -1;
	}

	char& operator[](size_t pos)
	{
		assert(pos < _size);
		return _str[pos];
	}

	const char& operator[](size_t pos) const
	{
		assert(pos < _size);
		return _str[pos];
	}

	String& operator=(String s)
	{
		Swap(s);
		return *this;
	}

	size_t Size() const
	{
		return _size;
	}

	size_t Capacity() const
	{
		return _capacity;
	}

	Iterator begin()
	{
		return _str;
	}

	Iterator end()
	{
		return _str + _size;
	}


	const_Iterator begin() const
	{
		return _str;
	}

	const_Iterator end() const
	{
		return _str + _size;
	}
	char* c_str()const
	{
		return _str;
	}

	~String()
	{
		if (_str)
		{
			delete[] _str;
			_str = nullptr;
			_size = _capacity = 0;
		}
	}

	static size_t npos;
private:
	char* _str;
	size_t _size;
	size_t _capacity;

};

String operator+(const String& s, char c) {
	String tmp = s;
	tmp += c;  
	return tmp;
}
String operator+(const String& s, const String& s2)
{
	String temp(s);
	temp += s2; 
	return temp;
}

String operator+(const String& s, const char* str)
{
	String tmp = s;
	tmp += str; 
	return tmp;
}

ostream& operator<<(ostream& _cout, const String& s)
{
	_cout << s.c_str() << endl;
	return _cout;
}

void PrintStringFor(const String& s)
{
	for (const auto& e : s)
		cout << e << " ";
	cout << endl;
}

void testString()
{
	String s;
	s.pushBack('0');
	s.pushBack('1');
	s.pushBack('2');
	s.pushBack('3');
	s.pushBack('4');
	s.pushBack('5');
	s += 'a';
	s += "bcd";
	PrintStringFor(s);
}
int main()
{
	testString();
	system("pause");
	return 0;
}

