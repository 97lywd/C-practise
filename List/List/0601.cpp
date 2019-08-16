#include<iostream>
using namespace std;
template<class T>
struct ListNode{
	ListNode(const T&val = T())
		:_prev(nullptr)
	    , _next(nullptr)
		, _val(val)
	{}
	ListNode<T>*_prev;
	ListNode<T>*_next;
	T _val;
};
template<class T,class Ptr,class Ref>
struct ListIterator {
	typedef ListNode<T> Node;
	typedef ListIterator<T, Ptr, Ref> Self;
	Node* _node;
	ListIterator(Node* p = nullptr)
		:_node(p)
	{}
	Ref operator*()
	{
		return _node->_val;
	}
	Ptr operator->() 
	{
		return &_node->_val;
	}
	Self& operator++()
	{
		_node = _node->_next;
		return *this;
	 }
	bool operator!=(const Self& lt)
	{
		return _node != lt._node;
	}
	bool operator==(const Self& lt)
	{
		return _node == lt._node;
	}
};
template<class T>
class List{

	typedef  ListNode<T> Node;
	typedef ListIterator<T, T*, T&> iterator;

public:
	List()
		:_head(new Node)
	{
		_head->_next = _head;
		_head->_prev = _head;
	}
	void pushback(const T& val)
	{
		Node* newNode = new Node(val);
		Node* tail = _head->_prev;
		tail->_next = newNode;
		newNode->_prev = tail;
		newNode->_next = _head;
		_head->_prev = newNode;
	}
	void Insert(iterator pos, const T&val)
	{
		Node* newNode = new Node(val);
		Node* cur = pos._node;
		Node* prev = cur->_prev;
		prev->_next = newNode;
		newNode->_prev = prev;
		cur->_prev = newNode;
		newNode->_next = cur;
	}
	iterator Erase(iterator pos)
	{
		if (pos != end())
		{

			Node* cur = pos._node;
			Node* prev = cur->_prev;
			Node* next = cur->_next;
			delete cur;
			cur = nullptr;
			prev->_next = next;
			next->_prev = prev;
			pos = iterator(next);
		}
		return pos;
	}
	~List()
	{
		if ( _head)
		{
		Node* cur = _head->_next;
		while (cur != _head)
		{
			Node* next = cur->_next;
			delete cur;
			cur = next;
		}
		_head->_next = _head;
		_head->_prev = _head;
		}
	}
	iterator begin()
	{
		return iterator(_head->_next);
	}
	iterator end()
	{
		return iterator(_head);
	}
private:
	Node* _head;
};
template<class T>
void Print(List<T> lit)
{
	auto i = lit.begin();
	while (i != lit.end())
	{
		cout << *i << " ";
		++i;
	}
	cout << endl;
}
void test()
{
	List<int> lit;
	lit.pushback(1);
	lit.pushback(2);
	lit.pushback(3);
	lit.pushback(4);
	Print(lit);
}
int main()
{
	test();
	system("pause");
	return 0;
}