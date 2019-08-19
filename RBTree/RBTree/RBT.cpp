#include<iostream>
#include<cstdlib>
using namespace std;
enum COLOR
{red,black};
template <class K,class V>
struct RBTNode
{
	RBTNode(const pair<K,V>& data = pair<K,V>())
		:_parent(nullptr)
		,_right(nullptr)
		,_left(nullptr)
		,color(red)
		,_data(data)
	{}
	pair<K,V> _data;
	RBTNode<K,V>* _parent;
	RBTNode<K,V>* _right;
	RBTNode<K,V>* _left;
	COLOR color;
};

template <class K, class V>
class RBTree {
public:
	typedef RBTNode<K, V> Node;
	RBTree(const pair<K, V>& data = pair<K, V>())
	{
		_head = new Node(data);
		_head->_left = _head->_right = _head;
		_head->_parent = nullptr;
	}
	bool Insert(const pair<K, V>& data)
	{
		if (_head->_parent == nullptr)
		{
			Node* root = new Node(data);
			_head->_parent = root;
			_head->_left = _head->_right = root;
			root->color = black;
			root->_parent = _head;
			return true;
		}
		Node* cur = _head->_parent;
		Node* parent = nullptr;
		while (cur)
		{
			parent = cur;
			if (cur->_data.first == data.first)
			{
				return false;
			}
			if (cur->_data.first > data.first)
				cur = cur->_left;
			else
				cur = cur->_right;
		}
		cur = new Node(data);
		if (parent->_data.first > data.first)
			parent->_left = cur;
		else
			parent->_right = cur;
		cur->_parent = parent;

		//调整 ： cur和parent都为红色，需要调整
		while (cur != _head->_parent && cur->_parent->color == red)
		{
			Node* parent = cur->_parent;
			Node* Gparent = parent->_parent;
			//祖父节点的左孩子存在并且为红色
			if (Gparent->_left == parent)
			{
				Node* uncle = Gparent->_right;
				if (uncle && uncle->color == red)
				{
					uncle->color = parent->color = black;
					Gparent->color = red;
					cur = Gparent;
				}
			         //如果cur = parent->right 左单旋一次  
					 //cur = parent->left 右单旋一次 得到上面的情况 再做单旋一次即可
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
		return true;
	}
	Node* leftMost()
	{
		Node* cur = _head->_parent;
		while (cur)
		{
			cur = cur->_left;
		}
		return cur;
	}
	Node* rightMost()
	{

		Node* cur = _head->_parent;
		while (cur)
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
		cout << root->_data.first << " ";
		_Inoder(root->_right);
	}
	void Inoder()
	{
		_Inoder(_head->_parent);
		cout << endl;
	}
	void RotateLeft(Node* parent)          //左单旋
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
	void RotateRight(Node* parent)         //右单旋
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
	//判断是否是红黑树的条件：
	//不能连续两个红色
	//一个路径上黑色必须相同
	//root 必须为黑色
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
			cur = cur->_left;           //找到一个基准值 然后遍历（前序）所有路径 如果都一样 则返回true
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


void test()
{
	RBTree<int,int> rbt;
	rbt.Insert(make_pair(1, 1));
	rbt.Insert(make_pair(10, 1));
	rbt.Insert(make_pair(2, 1));
	rbt.Insert(make_pair(5, 1));
	rbt.Insert(make_pair(3, 1));
	rbt.Insert(make_pair(4, 1));
	rbt.Insert(make_pair(7, 1));
	rbt.Inoder();
	cout << rbt.IsRBTree();
}
int main()
{
    test();
	system("pause");
	return 0;
}