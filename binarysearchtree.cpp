// Created by Aleksandr Golovin on 1/25/2018.
// Project Name: ass2
// File Name: binarysearchTree.cpp
// Copyright � 2018 Aleksandr Golovin. All rights reserved.
// Note: The definitions for the functions and comments were written by Aleksandr Golovin,
//		most of the function declarations were written by Dr. Pisan.

#include "binarysearchtree.h"

// Default constructor, empty tree
template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree() {
	// By default tree is empty
	rootPtr = nullptr;
}

// Destructor
template<class ItemType>
BinarySearchTree<ItemType>::~BinarySearchTree() {
	// Call clear
	clear();
}

// Constructor that initializes root to give item
template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const ItemType& rootItem) {
	// Root is set to new item
	rootPtr = new BinaryNode<ItemType>(rootItem);
}

// Copy Constructor
template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const BinarySearchTree<ItemType>& bst) {
	// Use helper function for a preorder deep copy
	rootPtr=preOrderDeepCopy(bst.rootPtr);
}

// Checks if root is pointing to nullptr and returns
template<class ItemType>
bool BinarySearchTree<ItemType>::isEmpty() const {
	// If rootPtr is null, tree is empty
	return (rootPtr == nullptr);
}

// Returns height of tree
template<class ItemType>
int BinarySearchTree<ItemType>::getHeight() const {
	// Call helper to count height
	return heightCount(rootPtr);
}

// Returns number of nodes in tree
template<class ItemType>
int BinarySearchTree<ItemType>::getNumberOfNodes() const {
	int count = 0;

	// If tree not empty
	if (rootPtr != nullptr)
	{
		// Use helper to count nodes
		preOrderCountNodes(rootPtr, count);
	}

	return count;
}

// Adds item to tree, if not present
template<class ItemType>
bool BinarySearchTree<ItemType>::add(const ItemType& item) {
	bool added = false;

	// If tree doesn't contain the item
	if (!contains(item))
	{
		// Temp to see if size changed
		int befSize = this->getNumberOfNodes();

		// Create a new item, use helper placeNode
		BinaryNode<ItemType> * temp = new BinaryNode<ItemType>(item);
		rootPtr = placeNode(rootPtr, temp);

		// If the new size is greater, item was added
		if (befSize < this->getNumberOfNodes())
		{
			added = true;
		}
	}

	return added;
}

// Clears tree
template<class ItemType>
void BinarySearchTree<ItemType>::clear() {
	// Call to helper function to clear tree in postorder
	clearPostOrder(rootPtr);
	rootPtr = nullptr;
}

// Checks if item is present in tree
template<class ItemType>
bool BinarySearchTree<ItemType>::contains(const ItemType& item) const {
	// Get pointer to node using helper findNode
	BinaryNode<ItemType>* found = findNode(rootPtr, item);

	// If pointer is null, item doesn't exist
	if (found == nullptr)
	{
		return false;
	}
	else
	{
		return true;
	}
}

// Places item in correct spot in tree
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::placeNode(BinaryNode<ItemType>* subTreePtr, BinaryNode<ItemType>* newNodePtr) {
	if (subTreePtr == nullptr)
	{
		return newNodePtr;
	}
	else
	{
		// Pointer to left and right children 
		BinaryNode<ItemType>*lptr = subTreePtr->getLeftChildPtr();
		BinaryNode<ItemType>*rptr = subTreePtr->getRightChildPtr();

		if (subTreePtr->getItem() > newNodePtr->getItem())
		{
			// Current item greater than new item
			// Put new item in left subtree
			lptr = placeNode(lptr, newNodePtr);
			subTreePtr->setLeftChildPtr(lptr);
		}
		else
		{
			// Current item less than new item
			// Put new item in right subtree
			rptr = placeNode(rptr, newNodePtr);
			subTreePtr->setRightChildPtr(rptr);
		}
		return subTreePtr;
	}
}  // end placeNode

// Searchs tree for a given item
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType>* subTreePtr, const ItemType& target) const {
	BinaryNode<ItemType>* tempPtr = subTreePtr;

	if (subTreePtr == nullptr)
	{
		return nullptr;
	}
	// If current item same as target
	else if (subTreePtr->getItem() == target)
	{
		return subTreePtr;
	}
	else if (subTreePtr->getItem() > target)
	{
		// Target is less than current, search for node in left subtree
		tempPtr = findNode(subTreePtr->getLeftChildPtr(), target);
	}
	else
	{
		// Target greater than current, search right subtree
		tempPtr = findNode(subTreePtr->getRightChildPtr(), target);
	}
	
	return tempPtr;
}  // end findNode

// Traverses tree inorder
template<class ItemType>
void BinarySearchTree<ItemType>::inorderTraverse(void visit(ItemType&)) const {
	// Call helper
	inOrderTrav(rootPtr, visit);
}  // end inorder

// Rebalances tree
template<class ItemType>
void BinarySearchTree<ItemType>::rebalance() {
	// Get the number of nodes in bst
	int numOfNodes = this->getNumberOfNodes();

	// Create an array with the size of bst
	ItemType * ar = new ItemType[numOfNodes];

	// Fill array inorder, using helper
	int count = 0;
	fillArInOrder(rootPtr, ar, count);

	// Build the tree
	readTree(ar, numOfNodes);

	// Delete array
	delete[]ar;
	ar = nullptr;
}

// Given an array, build a balanced tree
template<class ItemType>
bool BinarySearchTree<ItemType>::readTree(ItemType arr[], int n) {
	// Clear current bst
	clear();

	// For status of build
	bool built = false;

	// Build tree using helper function
	rootPtr = buildTree(arr, 0, n);

	// If the number of nodes same as array size
	// tree built successfully
	if (this->getNumberOfNodes() == n)
	{
		built = true;
	}
	return built;
}

// Displays tree side ways
template<class ItemType>
void BinarySearchTree<ItemType>::displaySideways() const {
	sideways(rootPtr, 0);
}

// Helper to display tree sideways
template<class ItemType>
void BinarySearchTree<ItemType>::sideways(BinaryNode<ItemType>* current, int level) const {
	if (current != NULL) {
		level++;
		sideways(current->getRightChildPtr(), level);

		// indent for readability, 4 spaces per depth level
		for (int i = level; i >= 0; i--) {
			cout << "    ";
		}

		cout << current->getItem() << endl;        // display information of object
		sideways(current->getLeftChildPtr(), level);
	}
}

// Helper, counts nodes in tree
template<class ItemType>
void BinarySearchTree<ItemType>::preOrderCountNodes(BinaryNode<ItemType>* current, int & count) const {
	if (current == nullptr)
	{
		return;
	}

	count += 1;

	// Count nodes in left subtree
	preOrderCountNodes(current->getLeftChildPtr(), count);

	// Count nodes in right subtree
	preOrderCountNodes(current->getRightChildPtr(), count);
}

// Helper, clear tree
template<class ItemType>
void BinarySearchTree<ItemType>::clearPostOrder(BinaryNode<ItemType>* current) {
	if (current == nullptr)
	{
		return;
	}

	// Clear left subtree
	clearPostOrder(current->getLeftChildPtr());

	// Clear right subtree
	clearPostOrder(current->getRightChildPtr());

	// Delete the item
	delete current;
	current = nullptr;
}

// Helper, creates deep copy of tree
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::preOrderDeepCopy( BinaryNode<ItemType>* toCopy) {
	if (toCopy == nullptr)
	{
		return nullptr;

	}
	
	// Add item to tree
	ItemType item = toCopy->getItem();
	BinaryNode<ItemType>* root= new BinaryNode<ItemType>(item);

	// Set left subtree
	root->setLeftChildPtr(preOrderDeepCopy(toCopy->getLeftChildPtr()));

	// Set right subtree
	root->setRightChildPtr(preOrderDeepCopy(toCopy->getRightChildPtr()));

	return root;
}

// Helper, compares items in two trees
template<class ItemType>
bool BinarySearchTree<ItemType>::preOrderComparsion(const BinaryNode<ItemType>* root,const BinaryNode<ItemType>* rhs) const {
	bool retVal;

	// If both pointer are nullptrs
	if (root == nullptr && rhs == nullptr)
	{
		retVal = true;
	}
	// If items not equal
	else if (root->getItem() != rhs->getItem())
	{
		retVal = false;
	}
	else
	{
		// Check left subtree
		retVal= preOrderComparsion(root->getLeftChildPtr(), rhs->getLeftChildPtr());

		// Check right subtree
		retVal= preOrderComparsion(root->getRightChildPtr(), rhs->getRightChildPtr());
	}

	return retVal;
}

// Helper, fills array using inorder traversal of tree
template<class ItemType>
void BinarySearchTree<ItemType>::fillArInOrder(const BinaryNode<ItemType>* root, ItemType ar[], int & index) {
	if (root == nullptr)
	{
		return;
	}

	// Traverse left subtree
	fillArInOrder(root->getLeftChildPtr(), ar, index);

	// Add item to array
	ItemType item = root->getItem();
	ar[index] = item;
	index++;

	// Traverse right subtree
	fillArInOrder(root->getRightChildPtr(), ar, index);
}

// Helper, inorder traversal, uses given function
template<class ItemType>
void BinarySearchTree<ItemType>::inOrderTrav(const BinaryNode<ItemType>* root, void visit(ItemType&)) const {
	if (root == nullptr)
	{
		return;
	}

	// Traverse left subtree
	inOrderTrav(root->getLeftChildPtr(), visit);

	// Visit the item
	ItemType item = root->getItem();
	visit(item);

	// Traverse right subtree
	inOrderTrav(root->getRightChildPtr(), visit);
}

// Helper, counts height of tree
template<class ItemType>
int BinarySearchTree<ItemType>::heightCount(BinaryNode<ItemType>* root)const {
	if (root == nullptr)
	{
		return 0;
	}
	else
	{
		// Get height of left subtree
		int lh = heightCount(root->getLeftChildPtr());

		// Get height of right subtree
		int rh = heightCount(root->getRightChildPtr());

		// If left subtree height greater than right subtree
		// return left subtree height + 1
		if (lh > rh)
			return(lh + 1);
		else 
			return(rh + 1);
	}
}

// Helper, buld a tree given an array
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::buildTree(ItemType ar[], int lbound, int ubound) {
	if (lbound >= ubound) return nullptr;

	// Calculate the middle of array
	int m = lbound + (ubound - lbound) / 2;

	// Set root equal to item in middle of array
	BinaryNode<ItemType>*root = new BinaryNode<ItemType>(ar[m]);

	// Set left child to left part of array
	root->setLeftChildPtr(buildTree(ar, lbound, m));

	// Set right child to right part of array
	root->setRightChildPtr(buildTree(ar, m+1, ubound));

	return root;
}

// Checks it two tree are the same
template<class ItemType>
bool BinarySearchTree<ItemType>::operator==(const BinarySearchTree<ItemType>& other) const {
	// Check number of nodes
	if (this->getNumberOfNodes() != other.getNumberOfNodes())
	{
		return false;
	}
	else
	{
		// Number of nodes the same, call helper for preorder recursive comparison
		return preOrderComparsion(this->rootPtr, other.rootPtr);
	}
}

// Checks it two trees are not the same
template<class ItemType>
bool BinarySearchTree<ItemType>::operator!=(const BinarySearchTree<ItemType>& other) const {
	// Call to operator ==, return opposite
	return !(*this == other);
}
