/*
	Implementation of balanced binary search tree of strings using the AVL algorithm.
	This implements the methods described in the header file.

	Author  :  Nishanth Jayram (https://github.com/njayram44)
	Date    :  December 24, 2020 
*/

#include "AVL.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>

// Default constructor
AVL :: AVL()
{
	root = NULL;
}

/* INSERT METHODS */
// Inserts a node containing the given input string into the tree, if feasible.
// Input: String - Key to insert into the tree
// Output: None
void AVL :: insert(string k)
{
	Node* to_insert = new Node(k); // Initialize a new node to contain the string
	if (root == NULL) // If the tree is empty, update the root to the node
		root = to_insert;
	else
	{
		insert(root, to_insert); // Call the recursive insert method
		root = fixBalance(root); // Fix the balance from the root
	}
}

// Recursive helper function for inserting a new node into the subtree starting
// from a given root.
// Input: Node pointer - Root of the subtree; Node pointer - Node to insert
// Output: None
void AVL :: insert(Node* start, Node* to_insert)
{
	if (start == NULL) // Should not technically happen, but return safely if subtree is empty
		return;
	if (to_insert->key < start->key) // Key we wish to insert is smaller than current, so go left
	{
		if (start->left == NULL) // Base case: The current node has no left child, so we insert
		{
			start->left = to_insert; // Insert the node as the left child
			setParent(to_insert, start); // Update parent pointer
			setHeight(start, 1); // Node added is a leaf, so update the current node's height to 1
			setSubsize(start, 2 + getSubsize(start->right)); // Subtree size becomes 2 (current + left) + size(right subtree)
			return;
		}
		else // Recursive case
		{
			insert(start->left, to_insert); // Recurse down the left subtree
			start->left = fixBalance(start->left); // Fix the balance as we recurse up
			int new_height = 1 + max(getHeight(start->left), getHeight(start->right)); // Update the height as we recurse up
			setHeight(start, new_height);
			setSubsize(start, 1 + getSubsize(start->left) + getSubsize(start->right)); // Update the subtree size as we recurse up
			return;
		}
	}
	else if (to_insert->key > start->key) // Key we wish to insert is larger than current, so go right
	{
		if (start->right == NULL) // Base case: The current node has no right child, so we insert
		{
			start->right = to_insert; // Insert the node as the right child
			setParent(to_insert, start); // Update parent pointer
			setHeight(start, 1); // Node added is a leaf, so update the current node's height to 1
			setSubsize(start, 2 + getSubsize(start->left)); // Subtree size becomes 2 (current + right) + size(left subtree)
			return;
		}
		else // Recursive case
		{
			insert(start->right, to_insert); // Recurse down the right subtree
			start->right = fixBalance(start->right); // Fix the balance as we recurse up
			int new_height = 1 + max(getHeight(start->left), getHeight(start->right)); // Update the height as we recurse up
			setHeight(start, new_height);
			setSubsize(start, 1 + getSubsize(start->left) + getSubsize(start->right)); // Update the subtree size as we recurse up
			return;
		}
	}
	else // Duplicate keys are not permitted, so we return
	{
		delete(to_insert); // Free memory associated with node
		return;
	}
}

/* FIND METHODS */
// Finds a node containing a given input string, if feasible.
// Input: String - key of interest
// Output: Node pointer - Node containing key, if it exists
Node* AVL :: find(string k)
{
	return find(root, k); // Call the recursive find function
}

// Recursive helper function for finding a node in a subtree rooted at a given node,
// if feasible.
// Input: Node pointer - Root of the subtree, String - key of interest
// Output: Node pointer - Node containing key, if it exists
Node* AVL :: find(Node* start, string k)
{
	if (start == NULL || start->key == k)
		return start;
	if (k < start->key)
		return find(start->left, k);
	else
		return find(start->right, k);
}

/* RANGE QUERIES */
// Returns the cardinality of the range of keys in [k1, k2], if feasible.
// Input: String - lower bound, String - upper bound
// Output: Int - Indicates number of keys in the range
int AVL :: range(string k1, string k2)
{
	return range(root, k1, k2); // Call the recursive helper function
}

// Recursive helper function for processing range queries within a subtree
// rooted at a given node.
// Input: Node pointer - Root of the subtree, String - lower bound, String - upper bound
// Output: Int - Indicates number of keys in the range
int AVL :: range(Node* start, string k1, string k2)
{
	if (start == NULL) // Base case: There are no further nodes to recurse on, so return.
		return 0;
	if (k2 < start->key) // k2 < start->key => k1 < start->key, so go left
		return range(start->left, k1, k2);
	if (k1 > start->key) // k1 > start->key => k2 > start->key, so go right
		return range(start->right, k1, k2);
	
	// k1 <= start->key <= k2, so find all nodes greater than k1 in the left subtree and all nodes
	// smaller than k2 in the right subtree.
	return 1 + geq(start->left, k1) + leq(start->right, k2);
}

// Returns the number of nodes "less than or equal to" a given input, throughout a subtree
// rooted at a given input node.
// Input: Node pointer - Root of the subtree to search; String - key of interest
// Output: Int - Indicates number of nodes with keys smaller than input
int AVL :: leq(Node* start, string k)
{
	if (start == NULL) // Base case: There are no further nodes to recurse on, so return
		return 0;
	if (start->key == k) // If the keys are equal, simply return the size of the left subtree + start
		return 1 + getSubsize(start->left);
	else if (start->key > k) // If the current key is larger, we go left
		return leq(start->left, k);
	else // If the current key is smaller, return the size of the left subtree + start and recurse right
		return 1 + getSubsize(start->left) + leq(start->right, k);
}

// Returns the number of nodes "greater than or equal to" a given input, throughout a subtree
// rooted at a given input node.
// Input: Node pointer - Root of the subtree to search; String - key of interest
// Output: Int - Indicates number of nodes with keys greater than input
int AVL :: geq(Node* start, string k)
{
	if (start == NULL) // Base case: There are no further nodes to recurse on, so return
		return 0;
	if (start->key == k) // If the keyes are equal, simply return the size of the right subtree + start
		return 1 + getSubsize(start->right);
	else if (start->key < k) // If the current key is smaller, we go right
		return geq(start->right, k);
	else // If the current key is larger, return the size of the right subtree + start and recurse left
		return 1 + getSubsize(start->right) + geq(start->left, k);
}

/* BALANCE/ROTATIONS */
// Fix the balance of the subtree rooted at a given node as needed.
// Input: Node pointer - Root of the subtree to fix
// Output: None
Node* AVL :: fixBalance(Node* n)
{
	int bal = getBalance(n); // Obtain the balance factor of the subtree
	if (bal > 1) // LEFT: The subtree is left-heavy
	{
		if (getBalance(n->left) >= 1) // LEFT: The left subtree of the current subtree is left-heavy, so single-rotate
			return rightRotate(n);
		else // RIGHT: The left subtree of the current subtree is right-heavy, so double-rotate
		{
			n->left = leftRotate(n->left); // First left-rotate the left subtree
			return rightRotate(n); // Now right-rotate the current subtree
		}
	}
	else if (bal < -1) // RIGHT: The subtree is right-heavy
	{
		if (getBalance(n->right) <= -1) // RIGHT: The right subtree of the current subtree is right-heavy, so single-rotate
			return leftRotate(n);
		else // LEFT: The right subtree of the current subtree is left-heavy, so double-rotate
		{
			n->right = rightRotate(n->right); // First right-rotate the right subtree
			return leftRotate(n); // Now left-rotate the current subtree
		}
	}
	return n; // If no balance modifications are made, simply return the node
}

// Performs a left rotation on the subtree rooted at x.
// Input: Node pointer - Root of subtree to perform rotation on
// Output: Node pointer - New root of subtree
Node* AVL :: leftRotate(Node* x)
{
	// Obtain pointers to the necessary nodes prior to rotation.
	// assumes x is non-NULL and x's right child is non-NULL
	Node* y = x->right;
	Node* t2 = y->left;
	
	// If x is the root node, we preemptively update it to the new root y.
	if (x == root)
		root = y;

	/* STEP 1: Make y's parent to be x's parent, x's parent to be y,
	 * and t2's parent to be x. */
	setParent(y, x->parent);
	setParent(x, y);
	setParent(t2, x);
	
	/* STEP 2: Make x's right subtree to be t2 and y's left child to be x. */
	x->right = t2;
	y->left = x;
	
	/* STEP 3: Update the heights of x and y. */
	setHeight(x, max(getHeight(x->left), getHeight(x->right)) + 1);
	setHeight(y, max(getHeight(y->left), getHeight(y->right)) + 1);
	
	/* STEP 4: Update the subtree sizes of x and y. */
	setSubsize(y, getSubsize(x));
	setSubsize(x, getSubsize(x->left) + getSubsize(x->right) + 1);

	// Return the new root.
	return y;
}

// Performs a right rotation on the subtree rooted at y.
// Input: Node pointer - Root of subtree to perform rotation on
// Output: Node pointer - New root of subtree
Node* AVL :: rightRotate(Node* y)
{		
	// Obtain pointers to the necessary nodes prior to rotation.
	Node* x = y->left;
	Node* t2 = x->right;
	
	// If y is the root node, we preemptively update root to the to-be new root x.
	if (y == root)
		root = x;
	
	/* STEP 1: Make x's parent to be y's parent, y's parent to be x,
	 * and t2's parent to be y. */
	setParent(x, y->parent);
	setParent(y, x);
	setParent(t2, y);
	
	/* STEP 2: Make y's left subtree to be t2 and x's right child to be y. */
	y->left = t2;
	x->right = y;
	
	/* STEP 3: Update the heights of x and y. */
	setHeight(y, max(getHeight(y->left), getHeight(y->right)) + 1);
	setHeight(x, max(getHeight(x->left), getHeight(x->right)) + 1);
	
	/* STEP 4: Update the subtree sizes of x and y. */
	setSubsize(x, getSubsize(y));
	setSubsize(y, getSubsize(y->left) + getSubsize(y->right) + 1);
	
	// Return the new root.
	return x;
}

/* ACCESSORS */
// Returns the height at the given node, if feasible.
// Input: Node pointer - Node of interest
// Output: Int - Height of the node
int AVL :: getHeight(Node* n)
{
	if (n == NULL)
			return -1;
	return n->height;
}

// Returns the balance factor at the given node, if feasible.
// Input: Node pointer - Node of interest
// Output: Int - Balance factor of the node
int AVL :: getBalance(Node* n)
{
	if (n == NULL)
		return 0;
	return getHeight(n->left) - getHeight(n->right);
}

// Returns the subtree size of the given node, if feasible.
// Input: Node pointer - Node of interest
// Output: Int - Balance factor of the node
int AVL :: getSubsize(Node* n)
{
	if (n == NULL)
		return 0;
	return n->subsize;
}

/* MUTATORS */
// Modifies the height attribute of a given node, if feasible.
// Input: Node pointer - Node of interest
// Output: None
void AVL :: setHeight(Node* n, int h)
{
	if (n == NULL || h < 0)
		return;
	n->height = h;
}

// Modifies the subtree size attribute of a given node, if feasible.
// Input: Node pointer - Node of interest
// Output: None
void AVL :: setSubsize(Node* n, int s)
{
	if (n == NULL || s < 0)
		return;
	n->subsize = s;
}

// Modifies the parent pointer of a given node, if feasible.
// Input: Node pointer - Node of interest, Node pointer - Parent node
// Output: None
void AVL :: setParent(Node* n, Node* p)
{
	if (n == NULL)
		return;
	n->parent = p;
}

/* PRINT METHODS */
// Returns a string listing the nodes of the tree in preorder form.
// Input: None
// Output: String - Preorder representation of AVL tree
string AVL :: printPreOrder()
{
    return printPreOrder(root); // Call the recursive helper function
}

// Recursive helper function for printing a preorder representation of
// the subtree rooted at a given node
// Input: Node pointer - Root of the subtree
// Output: Preorder traversal of the subtree rooted at given node
string AVL :: printPreOrder(Node* start)    
{
    if(start == NULL) // Base case: Return an empty string
        return "";
    string leftpart = printPreOrder(start->left); // Obtain the left part
    string rightpart = printPreOrder(start->right); // Obtain the right part
    string output = start->key + "(h = " + to_string(getHeight(start)) + // Prints <KEY> (<HEIGHT>, <SUBSIZE>)
			", s = " + to_string(getSubsize(start)) + ")";
    if(leftpart.length() != 0) // If the left part is non-empty, append
        output = output + leftpart;
    if(rightpart.length() != 0) // If the right part is non-empty, append
        output = output + rightpart;
    return output;
}