#pragma once
#include<queue>

#include "Heap.h"

template<class W>
struct HuffmanTreeNode
{
	HuffmanTreeNode<W>* _left;
	HuffmanTreeNode<W>* _right;
	HuffmanTreeNode<W>* _parent;
	W _weight;         //权值

	HuffmanTreeNode(const W& w)
		:_left(NULL)
		,_right(NULL)
		,_parent(NULL)
		,_weight(w)
	{}
};

template<class W>
class HuffmanTree
{
	typedef HuffmanTreeNode<W> Node;
public:
	HuffmanTree()
		:_root(NULL)
	{}

	HuffmanTree(const W* a,size_t n,const W& invalid)
	{
		assert(NULL != a && n >= 0);
		_CreateHuffmanTree(a,n,invalid);
	}

	Node* GetRoot()
	{
		return _root;
	}

	//层序遍历
	void LevelTraverse()
	{
		queue<Node*> q;
		if(NULL != _root)
			q.push(_root);
		while(!q.empty())
		{
			Node* cur = q.front();
			q.pop();
			cout << cur->_weight << " ";

			if(NULL != cur->_left)
				q.push(cur->_left);
			if(NULL != cur->_right)
				q.push(cur->_right);
		}
		cout << endl;
	}

	~HuffmanTree()
	{
		_Destroy(_root);
	}

protected:

	void _CreateHuffmanTree(const W* a,size_t n,const W& invalid)
	{
		//内部类
		struct NodeCompare
		{
			bool operator()(Node* l,Node* r)
			{
				return l->_weight < r->_weight;
			}
		};

		//贪心算法：权值大的数路径短
		Heap<Node*,NodeCompare> minHeap;

		//构建huffman树：所有的数据入小堆
		for(size_t i = 0;i < n; ++i)
		{
			if(a[i] != invalid)
				minHeap.Push(new Node(a[i]));
		}

		//构建二叉树
		while(minHeap.Size() > 1)
		{
			Node* left = minHeap.Top();
			minHeap.Pop();
			Node* right = minHeap.Top();
			minHeap.Pop();

			Node* parent = new Node(left->_weight + right->_weight);
			parent->_left = left;
			left->_parent = parent;
			parent->_right = right;
			right->_parent = parent;

			minHeap.Push(parent);
		}
		_root = minHeap.Top();
	}

	void _Destroy(Node* root)
	{
		if(root == NULL)
			return;
		_Destroy(root->_left);
		_Destroy(root->_right);
		delete root;
	}
protected:
	//防拷贝
	HuffmanTree(const HuffmanTree&);
	HuffmanTree& operator=(const HuffmanTree&);
	Node* _root;
};

//////////////////////////////////////
////测试构建huffman树是否正确
//////////////////////////////////////
void TestHuffmanTree()
{
	int a[] = {32,2,5,19,20,6,8,3,5};
	HuffmanTree<int> huff(a,sizeof(a)/sizeof(a[0]),-1);
	huff.LevelTraverse();
}




