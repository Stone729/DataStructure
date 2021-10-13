#include <iostream>

/**
* BinarySearchTree:
* 1. 构造函数 + Big5（拷贝构造函数&运算符、移动构造函数&运算符、析构函数）；
* 2. 数据操作接口（增、删、改、查）：
*	1. 增：insert
*	2. 刪：remove, makeEmpty
	3. 改：clone
*	4. 查：findMax, findMin, contains, isEmpty, printTree
*/


template <typename Comparable> // Comparable must define operator<
class BinarySearchTree {
public:
	BinarySearchTree(); // Default Constructor is always a must
	// Big 5:
	BinarySearchTree(const BinarySearchTree& rhs); // Copy Constructor
	BinarySearchTree& operator=(const BinarySearchTree& rhs); // Copy Assignment Operator
	BinarySearchTree(BinarySearchTree&& rhs); // Move Constructor
	BinarySearchTree& operator=(BinarySearchTree&& rhs); // Move Assignment Operator
	~BinarySearchTree(); // Destructor

	// Some Query Methods
	// Find the min and the max element
	const Comparable& findMin() const {
		return findMin(root)->element;
	}
	const Comparable& findMax() const {
		return findMax(root)->element;
	}
	// Find the specific element
	bool contains(const Comparable& x) const {
		return contains(x, root);
	}
	// Test empty container
	bool isEmpty() const;
	// Print all elements
	void printTree(std::ostream& out = std::cout) const;

	// Some Modification Methods:
	// Empty container
	void makeEmpty();
	// Insert elements
	void insert(const Comparable& x) { // Copy Version
		insert(x, root);
	}
	void insert(Comparable&& x); { // Move Version
		insert(x, root);
	}
	// remove elements
	void remove(const Comparable& x) {
		remove(x, root);
	}

private:
	// Internal Data Structures and Atom Operations
	struct BinaryNode {
		Comparable element;
		BinaryNode* left;
		BinaryNode* right;
		
		BinaryNode(const Comparable& theElement, BinaryNode *lt, BinaryNode* rt)
			: element{ theElement }, left{ lt }, right{ rt } {}

		BinaryNode(Comparable&& theElement, BinaryNode* lt, BinaryNode* rt)
			: element{ theElement }, left{ lf }, right{ rt } {}
	};

	BinaryNode* root; // root of the tree
	// Why insert() and remove() needs reference of the pointer?
	// insert & remove will change the pointer's value (pointing to the subtree ).
	// Copy Version
	void insert(const Comparable& x, BinaryNode*& t) {
		if (t == nullptr)
			root = new BinaryNode(x, nullptr, nullptr);
		else if (x < t->element)
			insert(x, t->left);
		else if (t->element < x)
			insert(x, t->right);
		else
			; // Duplicate; do nothing
	}
	// Move Version
	void insert(Comparable&& x, BinaryNode*& t) {
		if (t == nullptr)
			root = new BinaryNode(x, nullptr, nullptr);
		else if (x < t->element)
			insert(x, t->right);
		else if (t->element < x)
			insert(x, t->right);
		else
			; // Duplicate; do nothing
	}
	// 
	void remove(const Comparable& x, BinaryNode*& t) {
		if (t == nullptr)
			return;
		if (x < t->element)
			remove(x, t->left);
		else if (t->element < x)
			remove(x, t->right);
		else if (t->left != nullptr && t->right != nullptr) // Two children
		{
			t->element = findMin(t->right)->element;
			remove(t->element, t->right);
		}
		else
		{
			BinaryNode* oldNode = t;
			t = (t->left != nullptr) ? t->left : t->right;
			delete oldNode;
		}
	}

	// Some implementation of public interfaces
	BinaryNode* findMin(BinaryNode* t) const {
		if (t->left == nullptr)
			return t;
		else
			return findMin(t->left);
	}
	BinaryNode* findMax(BinaryNode* t) const {
		if (t->right == nullptr)
			return t;
		else
			return findMax(t->right);
	}
	bool contains(const Comparable& x, BinaryNode* t) const {
		if (t == nullptr)
			return false;
		if (x < t->element)
			contains(x, t->left);
		if (t->element < x) // must uses "<", because the ">" may be undefined.
			contains(x, t->right);
		else
			return true; // "==" may also undefined. "if a < b & b < a are all false, a == b"
	}
	// need to create a new tree, so the parameter must be a reference of a pointer
	void makeEmpty(BinaryNode*& t) {

	}
	void printTree(BinaryNode* t, std::ostream& out) const;
	BinaryNode* clone(BinaryNode* t) const;

};