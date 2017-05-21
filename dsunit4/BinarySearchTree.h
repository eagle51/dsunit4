#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H
#include "dsexception.h"
#include <algorithm>
using namespace std;

template<typename Comparable>
class BinarySearchTree
{
public:
	BinarySearchTree() : root{ nullptr }
	{
	}
	/**
	 * Copy constructor
	*/
	BinarySearchTree(const BinarySearchTree & rhs) :root{ nullptr }
	{
		root = clone(rhs.root);
	}

	/**
	 * Move constructor
	*/
	BinarySearchTree(BinarySearchTree && rhs) :root{ rhs.root }
	{
		rhs.root = nullptr;
	}

	/**
	 * Destructor for the tree
	*/
	~BinarySearchTree()
	{
		makeEmpty();
	}

	/**
	* Find the smallest item in the tree.
	* Throw UnderflowException if empty.
	*/
	const Comparable & findMin() const
	{
		if (isEmpty())
			throw UnderflowException{};
		return findMin(root)->element;
	}

	/**
	* Find the largest item in the tree.
	* Throw UnderflowException if empty.
	*/
	const Comparable & findMax() const
	{
		if (isEmpty())
			throw UnderflowException{};
		return findMax(root)->element;
	}

	/**
	* Returns true if x is found in the tree.
	*/
	bool contains(const Comparable & x) const
	{
		return contains(x, root);
	}

	/**
	* Test if the tree is logically empty.
	* Return true if empty, false otherwise.
	*/
	bool isEmpty() const
	{
		return root == nullptr;
	}

	/**
	* Print the tree contents in sorted order.
	*/
	void printTree(ostream & out = cout) const
	{
		if (isEmpty())
			out << "Empty tree" << endl;
		else
			printTree(root, out);
	}

	/**
	* Make the tree logically empty.
	*/
	void makeEmpty()
	{
		makeEmpty(root);
	}

	/**
	* Insert x into the tree; duplicates are ignored.
	*/
	void insert(const Comparable & x)
	{
		insert(x, root);
	}

	/**
	* Insert x into the tree; duplicates are ignored.
	*/
	void insert(Comparable && x)
	{
		insert(std::move(x), root);
	}

	/**
	* Remove x from the tree. Nothing is done if x is not found.
	*/
	void remove(const Comparable & x)
	{
		remove(x, root);
	}

	/**
	 * Copy assignment
	*/
	BinarySearchTree & operator=(const BinarySearchTree & rhs)
	{
		BinarySearchTree copy = rhs;
		std::swap(*this, copy);
		return *this;
	}
	BinarySearchTree & operator=(BinarySearchTree && rhs)
	{
		std::swap(root, rhs.root);
		return *this;
	}

private:
	struct BinaryNode
	{
		Comparable element;
		BinaryNode *left;
		BinaryNode *right;

		BinaryNode(const Comparable & theElement, BinaryNode *lt, BinaryNode *rt)
			: element{ theElement }, left{ lt }, right{ rt } {}
		BinaryNode(Comparable && theElement, BinaryNode  *lt, BinaryNode *rt)
			:element{ std::move(theElement) }, left{ lt }, right{ rt } {}
	};

	BinaryNode *root;

	/**
	 * 向子树插入元素的内部方法
	 * x是要插入的项
	 * t为该子树的根节点
	 * 置子树的新根
	*/
	void insert(const Comparable & x, BinaryNode * & t)
	{
		if (t == nullptr)
			t = new BinaryNode{ x, nullptr, nullptr };
		else if (x < t->element)
			insert(x, t->left);
		else if (t->element < x)
			insert(x, t->right);
		else
			;
	}
	void insert(Comparable && x, BinaryNode * & t)
	{
		if (t == nullptr)
			t = new BinaryNode{ std::move(x),nullptr,nulptr };
		else if (x < t->element)
			insert(std::move(x), t->left);
		else if (t->element < x)
			insert(std::move(t), t->right);
		else
			; //重复，什么都不做
	}

	/**
	 * 从一棵子树删除一项的内部方法
	 * 参数x是要被删除的项
	 * 参数t为该子树的根节点
	 * 置该子树的新的根
	*/
	void remove(const Comparable & x, BinaryNode * & t)
	{
		if (t == nullptr)
			return;//没找到项；什么也不做
		if (x < t->element)
			remove(x, t->left);
		else if (t->element < x)
			remove(x, t->right);
		else if (t->left != nullptr && t->right != nullptr)
		{
			t->element = findMin(t->right)->element;
			remove(t->element, t->right);
		}
		else
		{
			BinaryNode *oldNode = t;
			t = (t->left != nullptr) ? t->left : t->right;
			delete oldNode;
		}
	}

	/**
	 * 找出子树t中最小项的内部方法
	 * 返回包含最小项的节点
	*/
	BinaryNode * findMin(BinaryNode * t) const
	{
		if (t == nullptr)
			return nullptr;
		if (t->left == nullptr)
			return t;
		return findMin(t->left);
	}


	/**
	 * 找出子树t上最大项的内部方法
	 * 返回包含最大项的节点
	*/
	BinaryNode * findMax(BinaryNode * t)const
	{
		if (t != nullptr)
			while (t->right != nullptr)
				t = t->right;
		return t;//如果t=nullptr，则返回的t也是ptr。
	}

	/**
	 * 检测一项是否在子树上的内部方法
	 * x是要查找的项
	 * t是作为子树的根的节点
	*/
	bool contains(const Comparable & x, BinaryNode * t) const
	{
		if (t == nullptr)
			return false;
		else if (x < t->element)
			return contains(x, t->left);
		else if (t->element < x)
			return contains(x, t->right);
		else
			return true;
	}

	void makeEmpty(BinaryNode * & t)
	{
		if (t != nullptr)
		{
			makeEmpty(t->left);
			makeEmpty(t->right);
			delete t;
		}
		t = nullptr;
	}

	/**
	* Internal method to print a subtree rooted at t in sorted order.
	*/
	void printTree(BinaryNode * t, ostream & out) const
	{
		if (t != nullptr)
		{
			printTree(t->left, out);
			out << t->element << endl;
			printTree(t->right, out);
		}
	}

	/**
	* Internal method to clone subtree.
	*/
	BinaryNode * clone(BinaryNode *t) const
	{
		if (t == nullptr)
			return nullptr;
		else
			return new BinaryNode{ t -> element,clone(t->left),clone(t->right) };
	}
};

#endif // !BINARY_SEARCH_TREE_H