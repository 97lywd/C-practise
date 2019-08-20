#include<iostream>
#include<vector>
using namespace std;
enum state{Exist,Delete,Empty};
template<class K, class V>
struct HashNode
{
	pair<K, V> _data;
	state _state = Empty;
};
template<class K, class V>
class HashTable
{
public:
	typedef HashNode<K, V> Node;
	//构造
	HashTable(const size_t size = 10)
		:_size(0)
	{
		_ht.resize(size);
	}
	
	//插入 --- 除留余数法

	bool Insert(const pair<K, V>& data)
	{
		CheckCapcity();
		int index = data.first % _ht.size();
		while (_ht[index]._state == Exist)
		{
			if (_ht[index]._data.first == data.first)
				return false;
			++index;
			if (index == _ht.size())
				index = 0;
		}
		_ht[index]._data = data;
		_ht[index]._state = Exist;
		++_size;
		return true;
	}
	Node* Find(const K& key)
	{
		int index = key % _ht.size();
		while (_ht[index]._state != Empty)
		{
			if (_ht[index]._state == Exist)
			{
				if(_ht[index]._data.first == key)
					return &_ht[index];
			}
			++index;
			if (index == _ht.size())
				index = 0;
		}
		return nullptr;
	}
	bool Erase(const K& key)
	{
		Node* pos = Find(key);
		if (pos)
		{
			pos->_state = Delete;
			--_size;
			return true;
		}
		return false;
	}
protected:
	void CheckCapcity()
	{
		if (_ht.size() == 0 || _size * 10 / _ht.size() >= 8)
		{
			int newCap = _ht.size() == 0 ? 0 : 2 * _ht.size();
			HashTable<K, V> newht(newCap);
			for (int i = 0; i < _ht.size(); i++)
			{
				if (_ht[i]._state == Exist)
					newht.Insert(_ht[i]._data);
			}
			swap(_ht, newht._ht);
		}
	}
private:
	vector<Node> _ht;
	size_t _size;
};


int main()
{
	HashTable<int,int> m;
	m.Insert(make_pair(10, 1));
	m.Insert(make_pair(6, 1));
	m.Insert(make_pair(5, 1));
	m.Insert(make_pair(4, 1));
	m.Insert(make_pair(100, 1));
	m.Insert(make_pair(20, 1));
	m.Insert(make_pair(2, 1));
	m.Insert(make_pair(0, 1));
	m.Insert(make_pair(1, 1));
	m.Insert(make_pair(8, 1));
	m.Insert(make_pair(9, 1));
	m.Insert(make_pair(11, 1));
	system("pause");
	return 0;
}