#include "BinarySearchTree.h"

/** contains
*	Internal method to test if an item is in a subtree.
*	x is the item to search for
*	t is the node that roots the subtree
*/
template <typename Comparable>
bool BinarySearchTree<Comparable>::contains(const Comparable& x, BinaryNode* t) const {
	if (t == nullptr) return false;
	else if (x < t->element) return contains(x, t->left);
	else if (t->element < x) return contains(x, t->right); // Comparable only require the < operation, the > should not be used!
	else return true;
}

/** findMin
*	Internal method to find the smallest item in a subtree t.
*	Return the node containing the smallest item.
*/
template <typename Comparable>
BinarySearchTree<Comparable>::BinaryNode* BinarySearchTree<Comparable>::findMin(BinarySearchTree<Comparable>::BinaryNode* t) const {
	if (t == nullptr)
		return nullptr;
	if (t->left == nullptr)
		return t;
	return findMin(t->left);
}

/** findMax
*	Internal method to find the largest item in a subtree t.
*	Return the node containing the smallest item.
*/
template <typename Comparable>
BinarySearchTree<Comparable>::BinaryNode* BinarySearchTree<Comparable>::findMax(BinarySearchTree<Comparable>::BinaryNode* t) const {
	if (t == nullptr)
		return nullptr;
	while (t->right != nullptr)
		t = t->right;
	return t;
}

/** insert: copy version
*	Internal method to insert into a subtree
*	x is the item to insert
*	t is the node that roots the subtree
*	Set the new root of the subtree.
*/
template <typename Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable& x, BinaryNode*& t) {
	if (t == nullptr)
		t = new BinaryNode(x, nullptr, nullptr); // In this occasion, t points to a new tree, so t must be a reference.
	if (x < t->element)
		insert(x, t->left);
	if (t->element < x)
		insert(x, t->right);
	else
		; // duplicated occasion.
}

/** insert: move version
*	Internal method to insert into a subtree
*	x is the item to insert
*	t is the node that roots the subtree
*	Set the new root of the subtree.
*/
template <typename Comparable>
void BinarySearchTree<Comparable>::insert(Comparable&& x, BinaryNode*& t) {
	if (t == nullptr)
		t = new BinaryNode(std::move(x), nullptr, nullptr); // In this occasion, t points to a new tree, so t must be a reference.
	if (x < t->element)
		insert(std::move(x), t->left);
	if (t->element < x)
		insert(std::move(x), t->right);
	else
		; // duplicated occasion.
}

/** remove:
*	Internal method to remove from a subtree.
*	x is the item to remove
*	t is the node that roots the subtree
*	Set the new root of the subtree.
*/
template <typename Comparable>
void BinarySearchTree<Comparable>::remove(const Comparable& x, BinaryNode*& t) {
	if (t == nullptr)
		return;
	if (x < t->element)
		remove(x, t->left);
	if (t->element < x)
		remove(x, t->right);
	else if (t->left != nullptr && t->right != nullptr) {// two children
		t->element = findMin(t->right)->element;
		remove(t->element, t->right);
	}
	else {
		BinaryNode* oldNode = t;
		t = (t->left != nullptr) ? t->left : t->right;
		delete oldNode;
	}
}