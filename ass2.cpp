// Created by Aleksandr Golovin on 1/25/2018.
// Project Name: ass2
// File Name: ass2.cpp
// Copyright � 2018 Aleksandr Golovin. All rights reserved.

#include <iostream>
#include <sstream>
#include <vector>
#include <climits>

#include "binarysearchtree.h"
#include "binarynode.h"

using namespace std;

// The following functions are written by Yusuf Pisan pisan@uw.edu
// on 15 Jan 2018
void itemDisplay(string& anItem) {
	cout << anItem << " ";
}

string getString() {
	string str;
	cout << "Enter a string: ";
	cin >> str;
	return str;
}

vector<string> getStrings() {
	string longString;
	cout << "Enter multiple strings: ";
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	getline(cin, longString);
	stringstream ss;
	ss << longString;
	vector<string> v;
	string str;
	while (getline(ss, str, ' ')) {
		v.push_back(str);
	}
	return v;
}

void treeMenuString() {
	BinarySearchTree<string> bst;
	const string menu = "treeMenuString\n"
		"1. Add\n2. Search\n"
		"3. Inorder traverse\n"
		"4. Height & Number of nodes\n"
		"5. Rebalance\n"
		"6. Add Multiple\n"
		"7. Clear tree\n"
		"8. Create tree from sorted array\n"
		"10. Exit\n>> ";
	int choice;
	string str;
	cout << menu;
	while (true) {
		cin >> choice;
		switch (choice) {
		case 1:
			str = getString();
			cout << (bst.add(str) ? "" : "Not ") << "Added " << str << endl;
			break;
		case 2:
			str = getString();
			cout << (bst.contains(str) ? "" : "Not ") << "Found " << str << endl;
			break;
		case 3:
			bst.inorderTraverse(itemDisplay);
			cout << endl;
			break;
		case 4:
			cout << "Height: " << bst.getHeight() << endl;
			cout << "Number of nodes: " << bst.getNumberOfNodes() << endl;
			break;
		case 5:
			bst.rebalance();
			break;
		case 6:
			for (string str : getStrings())
				cout << (bst.add(str) ? "" : "Not ") << "Added " << str << endl;
			break;
		case 7:
			bst.clear();
			break;
		case 8: {
			bst.clear();
			vector<string> v{ getStrings() };
			bst.readTree(&v[0], v.size());
			break;
		}
		case 10: {
			bst.clear();
			return;
		}
		default:
			cout << "Bad input" << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		bst.displaySideways();
		cout << menu;
	}
}


void treeMenuInt() {
	BinarySearchTree<int> bst;
	const string menu = "treeMenuInt\n1. Add\n10. Exit\n>> ";
	int choice;
	int number;
	cout << menu;
	while (true) {
		cin >> choice;
		switch (choice) {
		case 1:
			cout << "Enter a number: ";
			cin >> number;
			cout << (bst.add(number) ? "" : "Not ") << "Added " << number << endl;
			break;
		case 10:
			bst.clear();
			return;
		default:
			cout << "Bad input" << endl;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(INT_MAX, '\n');
			}
		}
		bst.displaySideways();
		cout << menu;
	}
}

// end of Dr.Pisan's function declaration

int main() {
	
	cout << "Running test written by Aleksandr Golovin \n" << endl;
	BinarySearchTree<string> bst5, bst1;


	// Test for checking for empty tree
	cout << "Test for checking for empty tree" << endl;
	cout << (bst5.isEmpty() ? "OK" : "ERR") << ": bst5 is empty" << endl;
	cout << endl;

	// Test getting height and node count on empty tree
	cout << "Test getting height and node count on empty tree" << endl;
	cout<<((bst5.getHeight()==0) ? "OK" : "ERR") << ": bst5 height when empty" << endl;
	cout << ((bst5.getNumberOfNodes() == 0) ? "OK" : "ERR") << ": bst5 number of nodes when empty" << endl;
	cout << endl;

	// Create a unbalanced tree with height 6
	cout << "Create a unbalanced tree with height 6" << endl;
	cout << (bst5.add("a") ? "" : "Not ") << "Added a" << endl;
	cout << (bst5.add("b") ? "" : "Not ") << "Added b" << endl;
	cout << (bst5.add("c") ? "" : "Not ") << "Added c" << endl;
	cout << (bst5.add("d") ? "" : "Not ") << "Added d" << endl;
	cout << (bst5.add("e") ? "" : "Not ") << "Added e" << endl;
	cout << (bst5.add("f") ? "" : "Not ") << "Added f" << endl;
	cout << ((bst5.getNumberOfNodes() == 6) ? "OK" : "ERR") << ": bst5 number of nodes when 6 items added" << endl;
	cout << ((bst5.getHeight() == 6) ? "OK" : "ERR") << ": bst5 height when unbalanced" << endl;
	bst5.displaySideways();
	cout << endl;

	// Testing for empty tree after items have been added
	cout << "Testing for empty tree after items have been added" << endl;
	cout << ( bst5.isEmpty() ? "ERR" : "OK") << ": bst5 has elements" << endl;
	cout << endl;

	// Test rebalance function
	cout << "Test rebalance function" << endl;
	bst5.rebalance();
	cout << ((bst5.getHeight() == 3) ? "OK" : "ERR") << ": bst5 height when rebalanced" << endl;
	cout << ((bst5.getNumberOfNodes() == 6) ? "OK" : "ERR") << ": bst5 number of nodes after rebalance" << endl;
	bst5.displaySideways();
	cout << endl;

	// Searching for exisiting and non-existing item
	cout << "Searching for exisiting and non-existing item" << endl;
	cout << (bst5.contains("z") ? "ERR" : "OK") << ": bst5 does not contain z" << endl;
	cout << (bst5.contains("a") ? "OK" : "ERR") << ": bst5 contains a" << endl;
	cout << endl;

	// Adding a single element and searching for it
	cout << "Adding a single element and searching for it" << endl;
	cout << (bst5.add("z") ? "" : "Not ") << "Added z" << endl;
	cout << (bst5.contains("z") ? "OK" : "ERR") << ": bst5 does contain z after add" << endl;
	bst5.displaySideways();
	cout << endl;

	// Test copy constructor
	cout << "Test copy constructor" << endl;
	BinarySearchTree<string> bst6(bst5);
	cout << ((bst5.getHeight() == bst6.getHeight()) ? "OK" : "ERR") << ": bst6 and bst5 have the same height" << endl;
	cout << ((bst5.getNumberOfNodes() == bst6.getNumberOfNodes()) ? "OK" : "ERR") << ": bst6 and bst5 have same number of nodes" << endl;
	bst6.displaySideways();
	cout << endl;

	// Test == operator
	cout << "Test == operator" << endl;
	cout << ((bst5 == bst6) ? "OK" : "ERR") << ": bst5 and bst6 are the same" << endl;
	cout << ((bst5 == bst1) ? "ERR" : "OK") << ": bst5 and bst1 are not the same" << endl;
	cout << endl;

	// Test != operator
	cout << "Test != operator" << endl;
	cout << ((bst5 != bst6) ? "ERR" : "OK") << ": bst5 and bst6 are the same" << endl;
	cout << ((bst5 != bst1) ? "OK" : "ERR") << ": bst5 and bst1 are not the same" << endl;
	cout << endl;

	// Test clear
	cout << "Test clear" << endl;
	bst5.clear();
	cout << ((bst5.getNumberOfNodes() == 0) ? "OK" : "ERR") << ": bst5 should have no nodes after clear" << endl;
	cout << ((bst5.getHeight() == 0) ? "OK" : "ERR") << ": bst5 should not have a height after clear" << endl;
	cout << ((bst5.isEmpty()) ? "OK" : "ERR") << ": bst5 should be empty" << endl;
	cout << endl;

	// Test inorder traversal
	cout << "Test inorder traversal" << endl;
	cout << "Inorder traversal of bst6 (has nodes) is: "; 
	bst6.inorderTraverse(itemDisplay);
	cout << endl;
	cout << "Inorder traversal on empty tree is: ";
	bst5.inorderTraverse(itemDisplay);
	cout << endl;
	cout << endl;

	// Test adding an item that already exists
	cout << "Test adding an item that already exists" << endl;
	cout << (bst6.add("a") ? "" : "Not ") << "Added a because it already exists" << endl;
	cout << endl;

	// Test constructor with one item
	cout << "Test constructor with one item" << endl;
	BinarySearchTree<string> bst7("a");
	cout << ((bst7.getNumberOfNodes() == 1) ? "OK" : "ERR") << ": bst7 number of nodes when using constructor for 1 item" << endl;
	cout << ((bst7.getHeight() == 1) ? "OK" : "ERR") << ": bst7 height when using constructor for 1 item" << endl;
	cout << (bst7.contains("a") ? "OK" : "ERR") << ": bst7 does contain a after constructed" << endl;
	cout << endl;

	// Test building tree from array
	cout << "Test building tree from empty array" << endl;
	string ar[3];
	bst5.readTree(ar,0);
	cout << ((bst5.getNumberOfNodes() == 0) ? "OK" : "ERR") << ": bst5 should have no nodes when using an empty array" << endl;
	cout << ((bst5.getHeight() == 0) ? "OK" : "ERR") << ": bst5 should not have a height when using an empty array" << endl;
	cout << ((bst5.isEmpty()) ? "OK" : "ERR") << ": bst5 should be empty" << endl;
	cout << endl;

	cout << "Test building tree from an array with elements" << endl;
	ar[0] = "a";
	ar[1] = "b";
	ar[2] = "c";
	bst5.readTree(ar, 3);
	cout << ((bst5.getNumberOfNodes() == 3) ? "OK" : "ERR") << ": bst5 should have 3 nodes when using an array with 3 items" << endl;
	cout << ((bst5.getHeight() == 2) ? "OK" : "ERR") << ": bst5 should have a height of two" << endl;
	cout << ((bst5.isEmpty()) ? "ERR" : "OK") << ": bst5 not should be empty" << endl;

	return 0;
}
