#include"_rb_tree.h"
template<class K,class V>
class map
{
	struct mapKeyOfValue
	{
		const K& operator()(const pair<K, V>& data)
		{
			return data.first; 
		}
	};
public:
	typedef typename RBTree<K, pair<K, V>, mapKeyOfValue>::iterator iterator;
		pair<iterator, bool> Insert(const pair<K, V>& data)
	{
			return rbt.Insert(data);
	}
		iterator begin()
		{
			return rbt.begin();
		}
		iterator end()
		{
			return rbt.end();
		}
		void Inoder()
		{
			rbt.Inoder();
		}
		V& operator[](const K& key)
		{
			pair<iterator, bool> ret = rbt.Insert(make_pair(key, V()));
			return ret.first->second;
		}
private:
	RBTree<K, pair<K, V>, mapKeyOfValue> rbt;
};


void test()
{	
	map<int, int> m;
	m.Insert(make_pair(10, 1));
	m.Insert(make_pair(3, 1));
	m.Insert(make_pair(9, 1));
	m.Insert(make_pair(2, 1));
	m.Insert(make_pair(1, 1));
	//cout << m[5] << endl;
	//m[20] = 20;
//	m.Inoder();
	for (auto e : m)
	{
		cout << e.first;
	}
}
int main()
{
	test();
	system("pause");
	return 0;
}