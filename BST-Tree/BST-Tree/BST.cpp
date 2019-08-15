#include<cstdlib>
#include<iostream>
using namespace std;
template <class T>
struct BSTNode
{
	T _data;
	BSTNode<T> * _left;
	BSTNode<T> * _right;
	BSTNode(const T& data = T())
		:_left(nullptr)
		,_right(nullptr)
		,_data(data)
	{}
};
template<class T>
class BstTree
{
public:
	typedef BSTNode<T> Node;
	typedef BSTNode<T>* PNode;
	//Ĭ�Ϲ���
	BstTree()     
		:_root(nullptr)
	{}
    // ��������
	BstTree(const BstTree<T>& bst)
	{
		_root = Copy(bst._root);
	}
	//����
	~BstTree() { destory(_root); }
	//=����
	BstTree<T>& operator=(const BstTree<T> &bst)
	{
		if (this != &bst)  //_root != bst._root
		{
			if (_root)
			{
				destory(_root);
				_root = Copy(bst._root);
			}
		}
		return *this;
	}
	PNode Copy(PNode root)
	{
		if (root == nullptr)
			return root;
		PNode newNode = new Node(root->_data);
		newNode->_left = Copy(root->_left);
		newNode->_right = Copy(root->_right);
		return newNode;
	}
	
	void destory(PNode root)
	{
		if (root == nullptr)
			return;
		destory(root->_left);
		destory(root->_right);
		delete root;
		root = nullptr;
	}
	bool Insert(const T& data)            //����Ԫ��
	{
		if (_root == nullptr)
		{
			_root = new Node(data);
			return true;
		}
		PNode cur = _root;
		PNode parent = nullptr;
		while (cur)
		{
			parent = cur;
				if (cur->_data == data)
					return false;
				else if (cur->_data > data)
					cur = cur->_left;
				else
					cur = cur->_right;
		}
		//����ڵ�
		cur = new Node(data);
		//�жϲ����λ��
		if (parent->_data > data)
			parent->_left = cur;
		else
			parent->_right = cur;
		return true;
	}
	PNode Find(const T& data)         //����Ԫ��
	{
		if (_root == nullptr)
			return nullptr;
		PNode cur = _root;
		while (cur)
		{
			if (cur->_data == data)
				return cur;
			if (cur->_data > data)
				cur = cur->_left;
			else
				cur = cur->_right;
		}
		return nullptr;
	}
	bool Erase(const T& data)            //ɾ��Ԫ��
	{
		PNode cur = _root;
		PNode parent = cur;
		while (cur)
		{
			if (cur->_data == data)
				break;
			parent = cur;
		    if (cur->_data > data)
				cur = cur->_left;
			else
				cur = cur->_right;
		}
		if (cur == nullptr)
			return false;
		//ɾ������Ҷ�ӽڵ�
		if (cur->_left == nullptr && cur->_right == nullptr)
		{
			if (cur != _root)
			{
				if (parent->_left == cur)
					parent->_left = nullptr;
				else
					parent->_right = nullptr;
			}
			else
						_root = nullptr;
			delete cur;
			cur = nullptr;
		}
		//���Һ���
		else if (cur->_right == nullptr)
		{
			if (cur != nullptr)
			{
				if (parent->_left == cur)
					parent->_left = cur->_left;
				else
					parent->_right = cur->_left;
			}
			else
				_root = nullptr;
			delete cur;
			cur = nullptr;
		}
		//������
		else if (cur->_left == nullptr)
		{
			if (cur != nullptr)
			{
				if (parent->_left == cur)
					parent->_left = cur->_right;
				else
					parent->_right = cur->_right;
			}
			else
				_root = nullptr;
			delete cur;
			cur = nullptr;
		}
		else
		{
			//Ѱ�����������ĵ�  or Ѱ����������С�ĵ�
			PNode MaxNode = cur->_left;
			parent = cur;
			while (MaxNode->_right)
			{
				parent = MaxNode;
				MaxNode = MaxNode->_right;
			}
			cur->_data = MaxNode->_data;
			if (parent->_left == MaxNode)
				parent->_left = MaxNode->_left;
			else
				parent->_right = MaxNode->_left;
			delete MaxNode;
			MaxNode = nullptr;
		}
		return true;
	}
	void Inoder(PNode root)
	{
		if (root == nullptr)
			return;
		Inoder(root->_left);
		cout << root->_data << " ";
		Inoder(root->_right);
	}
	void print()
	{
		Inoder(_root);
		cout<<endl;
	}
private:
	PNode _root;
};


void test1()
{
	BstTree<int>bst;
	bst.Insert(5);
	bst.Insert(3);
	bst.Insert(7);
	bst.Insert(1);
	bst.Insert(4);
	bst.Insert(6);
	bst.Insert(8);
	bst.Insert(0);
	bst.Insert(2);
	bst.Insert(9);
	bst.print();
	bst.Erase(9);
	bst.print();
	bst.Erase(7);
	bst.print();
	bst.Erase(0);
	bst.print();
}
void test2()
{
	BstTree<int> bst2;
	bst2.Insert(100);
	bst2.Insert(200);
	bst2.Insert(300);
	bst2.print();
	BstTree<int> bst3;
	bst3.Insert(1);
	bst3.Insert(2);
	bst3.Insert(3);
	bst3.print();
	bst3 = bst2;
	bst3.print();
}
int main()
{
	//test1();
	test2();
	system("pause");
	return 0;
}