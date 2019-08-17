#include<iostream>
using namespace std;
template<class T>
struct AVLNode
{
	AVLNode(const T& data)
		:_data(data)
		,_left(nullptr)
		,_right(nullptr)
		,_parent(nullptr)
		,_bf(0)
	{}

	T _data;
	AVLNode<T>*_left;
	AVLNode<T>*_right;
	AVLNode<T>*_parent;
	int _bf;
};


template<class T>
class AVLTree{
public:
	typedef AVLNode<T> Node;
	typedef AVLNode<T>* pNode; 
	AVLTree(pNode root = nullptr)
		:_root(nullptr)
	{}
	bool Insert(const T& data)
	{
		pNode cur = _root;
		pNode parent = nullptr;
		if (_root == nullptr)
		{
			_root = new Node(data);
			return true;
		}
		while (cur)
		{
			parent = cur;
			if (cur->_data == data)
			{
				return false;
			}
			if (cur->_data > data)
				cur = cur->_left;
			else
				cur = cur->_right;
		}
		cur = new Node(data);
		if (parent->_data > data)
			parent->_left = cur;
		else
			parent->_right = cur;
		cur->_parent = parent;
		while (parent)
		{
			//更新平衡因子
			if (parent->_left == cur)
				--parent->_bf;
			else
				++parent->_bf;
			if (parent->_bf == 0)
				break;             //不需要调整
			else if (parent->_bf == 1 || parent->_bf == -1)
			{
				cur = parent;
				parent = parent->_parent;    //向上继续调整
			}
			else   //则需要调整
			{
				//左边比右边高  -----  右单旋
				if (parent->_bf == -2 || cur->_bf == -1)
				{
					RotateRight(parent);
				}
				//右边比左边高  -----  左单旋
				else if (parent->_bf == 2 || cur->_bf == 1)
				{
					RotateLeft(parent);
				}
				//左边的右边高  -----  先左单旋，后右单旋
				else if (parent->_bf == 2 || cur->_bf == -1)
				{
					RotateLeft(cur);
					RotateRight(parent);
				}
				//右边的左边高  -----  先右单旋，后左单旋
				else if (parent->_bf == -2 || cur->_bf == 1)
				{
					RotateRight(cur);
					RotateLeft(parent);
				}
				break;
			}
		}
	}
	void RotateLeft(pNode parent)          //左单旋
	{
		pNode subR = parent->_right;
		pNode subRL = subR->_left;
		subR->_left = parent;
		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;
		if (parent != _root)
		{
			if (parent->_parent->_left == parent)
				parent->_parent->_left = subR;
			else
				parent->_parent->_right = subR;
			subR->_parent = parent->_parent;
		}
		else
		{
			_root = subR;
			subR->_parent = nullptr;
		}
		parent->_parent = subR;
		subR->_bf = parent->_bf = 0;
	}
	void RotateRight(pNode parent)         //右单旋
	{
		pNode subL = parent->_left;
		pNode subLR = subL->_right;
		subL->_right = parent;
		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;
		if (parent != _root)
		{
			if (parent->_parent->_left == parent)
				parent->_parent->_left = subL;
			else
				parent->_parent->_right = subL;
			subL->_parent = parent->_parent;
		}
		else
		{
			_root = subL;
			subL->_parent = nullptr;
		}
		parent->_parent = subL;
		subL->_bf = parent->_bf = 0;
	}      
	bool IsBanlance(pNode root)           //判断树是否平衡
	{
		if (root == nullptr)
			return true;
		int leftH = Height(root->_left);
		int rightH = Height(root->_right);
		if (root->_bf != (rightH - leftH))
			return false;
		return abs(root->_bf) < 2
			&& IsBanlance(root->_left)
			&& IsBanlance(root->_right);
	}
	int Height(pNode root)
	{
		if (root == nullptr)
			return 0;
		int leftH = Height(root->_left);
		int rightH = Height(root->_right);
		return leftH > rightH ? leftH + 1 : rightH + 1;
	}
	bool _IsBanlance()
	{
		return IsBanlance(_root);
	}
	void Inoder(pNode root)
	{
		if (root == nullptr)
			return;
		Inoder(root->_left);
		cout << root->_data << " ";
		Inoder(root->_right);
	}
	void Print()
	{
		Inoder(_root);
		cout << endl;
	}
private:
	pNode _root;
};

void test()
{
	AVLTree<int> avl;
	int arr[] = { 3,2,1};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
		avl.Insert(arr[i]);
	avl.Print();
	cout << avl._IsBanlance() << endl;
}

int main()
{
	test();
	system("pause");
	return 0;
}