#pragma once
#include<iostream>
#include<cstdlib>
using namespace std;
enum COLOR
{
	red, black
};
template <class V>
struct RBTNode
{
	RBTNode(const V& data = V())
		:_parent(nullptr)
		, _right(nullptr)
		, _left(nullptr)
		, color(red)
		, _data(data)
	{}
	V _data;
	RBTNode<V>* _parent;
	RBTNode<V>* _right;
	RBTNode<V>* _left;
	COLOR color;
};

template <class V>
class _rb_tree_iterator
{
public:
	typedef RBTNode<V> Node;
	typedef _rb_tree_iterator<V> Self;
	_rb_tree_iterator(Node* node)
		:_node(node)
	{}
	V& operator*()
	{
		return _node->_data;
	}
	V* operator->()
	{
		return &_node->_data;
	}
	bool operator==(Self& it)
	{
		return _node != it._node;
	}
	bool operator!=(Self& it)
	{
		return _node == it._node;
	}
	Self& operator++()
	{
		increasement();
		return *this;
	}
	Self& operator--()
	{
		decreasement();
		return *this;
	}

private:
	void increasement()
	{
		//���ҵ�������������ڵ�
		if (_node->_right)
		{
			_node = _node->_right;
			while (_node->_left)
			{
				_node = _node->_left;
			}
		}
		else
		{
			Node* parent = _node->_parent;
			while (parent->_right == _node)
			{
				_node = parent;
				parent = parent->_parent;
			}
			if (parent != _node->_right)
			{
				_node = parent;
			}
		}
	}
	void decreasement()
	{
		if (_node->_left)
		{
			_node = _node->_left;
			while (_node->_right)
			{
				_node = _node->_right;
			}
		}
		else
		{
			Node* parent = _node->_parent;
			while (parent->_left == _node)
			{
				_node = parent;
				parent = parent->_parent;
			}
			if (parent != _node->_right)
			{
				_node = parent;
			}
		}
	}
	Node* _node;
};

template <class K, class V, class keyOfvalue>
class RBTree {
public:
	typedef RBTNode<V> Node;
	typedef _rb_tree_iterator<V> iterator;
	RBTree(const V& data = V())
	{
		_head = new Node(data);
		_head->_left = _head->_right = _head;
		_head->_parent = nullptr;
	}
	iterator begin()
	{
		return iterator(_head->_left);
	}
	iterator end()
	{
		return iterator(_head);
	}
	pair<iterator,bool> Insert(const V& data)
	{
		if (_head->_parent == nullptr)
		{
			Node* root = new Node(data);
			_head->_parent = root;
			_head->_left = _head->_right = root;
			root->color = black;
			root->_parent = _head;
			return make_pair(iterator(root), true);
		}
		Node* cur = _head->_parent;
		Node* parent = nullptr;
		keyOfvalue key;
		while (cur)
		{
			parent = cur;
			if (key(cur->_data) == key(data))
			{
				return make_pair(iterator(cur), false);
			}
			if (key(cur->_data) > key(data))
				cur = cur->_left;
			else
				cur = cur->_right;
		}
		cur = new Node(data);
		Node* newNode = cur;
		if (key(parent->_data) > key(data))
			parent->_left = cur;
		else
			parent->_right = cur;
		cur->_parent = parent;

		//���� �� cur��parent��Ϊ��ɫ����Ҫ����
		while (cur != _head->_parent && cur->_parent->color == red)
		{
			Node* parent = cur->_parent;
			Node* Gparent = parent->_parent;
			//�游�ڵ�����Ӵ��ڲ���Ϊ��ɫ
			if (Gparent->_left == parent)
			{
				Node* uncle = Gparent->_right;
				if (uncle && uncle->color == red)
				{
					uncle->color = parent->color = black;
					Gparent->color = red;
					cur = Gparent;
				}
				//���cur = parent->right ����һ��  
				//cur = parent->left �ҵ���һ�� �õ��������� ��������һ�μ���
				else
				{
					if (cur == parent->_right)
					{
						RotateLeft(parent);
						swap(cur, parent);
					}
					RotateRight(Gparent);
					parent->color = black;
					Gparent->color = red;
					break;
				}
			}
			else
			{
				Node *uncle = Gparent->_left;
				if (uncle && uncle->color == red)
				{
					uncle->color = parent->color = black;
					Gparent->color = red;
					cur = Gparent;
				}
				else
				{
					if (cur == parent->_left)
					{
						RotateRight(parent);
						swap(cur, parent);
					}
					RotateLeft(Gparent);
					parent->color = black;
					Gparent->color = red;
					break;
				}
			}
		}
		_head->_parent->color = black;
		_head->_right = rightMost();
		_head->_left = leftMost();
		return make_pair(iterator(newNode), true);
	}
	Node* leftMost()
	{
		Node* cur = _head->_parent;
		while (cur&&cur->_left)
		{
			cur = cur->_left;
		}
		return cur;
	}
	Node* rightMost()
	{

		Node* cur = _head->_parent;
		while (cur&&cur->_right)
		{
			cur = cur->_right;
		}
		return cur;
	}
	void _Inoder(Node* root)
	{
		if (root == nullptr)
			return;
		_Inoder(root->_left);
		cout << root->_data.first<< " ";
		_Inoder(root->_right);
	}
	void Inoder()
	{
		_Inoder(_head->_parent);
		cout << endl;
	}
	void RotateLeft(Node* parent)          //����
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		subR->_left = parent;
		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;
		if (parent != _head->_parent)
		{
			if (parent->_parent->_left == parent)
				parent->_parent->_left = subR;
			else
				parent->_parent->_right = subR;
			subR->_parent = parent->_parent;
		}
		else
		{
			_head->_parent = subR;
			subR->_parent = _head;
		}
		parent->_parent = subR;
	}
	void RotateRight(Node* parent)         //�ҵ���
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		subL->_right = parent;
		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;
		if (parent != _head->_parent)
		{
			if (parent->_parent->_left == parent)
				parent->_parent->_left = subL;
			else
				parent->_parent->_right = subL;
			subL->_parent = parent->_parent;
		}
		else
		{
			_head->_parent = subL;
			subL->_parent = _head;
		}
		parent->_parent = subL;
	}
	//�ж��Ƿ��Ǻ������������
	//��������������ɫ
	//һ��·���Ϻ�ɫ������ͬ
	//root ����Ϊ��ɫ
	bool IsRBTree()
	{
		Node* root = _head->_parent;
		if (root == nullptr)
			return true;
		if (root->color == red)
			return false;
		Node* cur = root;
		int BlackCout = 0;
		while (cur)
		{
			if (cur->color == black)
				BlackCout++;
			cur = cur->_left;           //�ҵ�һ����׼ֵ Ȼ�������ǰ������·�� �����һ�� �򷵻�true
		}
		_IsRBTree(root, BlackCout, 0);
	}
	bool _IsRBTree(Node* root, int BlackCout, int NowCout)
	{
		if (root == nullptr)
		{
			if (BlackCout == NowCout)
				return true;
			return false;
		}
		if (root->color == black)
			NowCout++;
		if (root->color == red && root->_parent->color == red)
			return false;
		return _IsRBTree(root->_left, BlackCout, NowCout) && _IsRBTree(root->_right, BlackCout, NowCout);
	}
private:
	Node * _head;
};
