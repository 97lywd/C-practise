#include"_rb_tree.h"
template <class K>
class set
{
	struct setKeyOfValue {
		const K& operator()(const K& key)
		{
			return key;
		}
	};
public:
	typedef typename RBTree<K, K, setKeyOfValue>::iterator iterator;
	pair<iterator, bool>Insert(const K& data)
	{
		return st.Insert(data);
	}
	iterator begin()
	{
		return st.begin();
	}
	iterator end()
	{
		return st.end();
	}
	void Inoder()
	{
		st.Inoder();
	}
private:
	RBTree<K, K, setKeyOfValue> st;
};

//void test()
//{
//	set<int> s;
//	s.Insert(11);
//	s.Insert(9);
//	s.Insert(1);
//	for (auto e : s)
//	{
//		cout << e;
//	}
//}
//
//int main()
//{
//	test();
//	system("pause");
//	return 0;
//}