/*
	Implementation of balanced binary search tree of strings using the AVL algorithm.
	This is the header file that provides class/method definitions.

	Author  :  Nishanth Jayram (https://github.com/njayram44)
	Date    :  December 24, 2020 
*/

#ifndef AVL_H
#define AVL_H
#include <string>
using namespace std;

class Node
{
	public:
		string key; // Contains the data
		Node* left, *right, *parent; // Pointers to the children and parent
		int height; // Tracks the height of the node (distance from the root of its subtree)
		int subsize; // Tracks the subtree size (number of nodes below)
		
		Node()
		{
			left = right = parent = NULL; // By default, these are NULL
			height = 0; // These are both zero by default
			subsize = 1;
		}
		
		Node(string k)
		{
			key = k;
			left = right = parent = NULL;
			height = 0;
			subsize = 1;
		}
};

class AVL
{
	private:
		Node* root;
	
	public:
		// Constructor
		AVL();
		
		// Insert methods
		void insert(string); // Main method for inserting a new node containing given key, if feasible
		void insert(Node*, Node*); // Recursive helper function for inserting new node in given subtree
		
		// Find methods
		Node* find(string); // Main method for finding a node containing given key, if feasible
		Node* find(Node*, string); // Recursive helper function for finding node containing key in a given subtree
		
		// Range queries
		int range(string, string); // Main method for processing the range query between two input strings, if feasible
		int range(Node*, string, string); // Recursive helper function for calculating a range query
		int leq(Node*, string); // Recursive helper function for determining number of nodes "less than or equal" to given input
		int geq(Node*, string); // Recursive helper function for determining number of nodes "greater than or equal" to given input
		
		// Balance/rotations
		Node* leftRotate(Node*);
		Node* rightRotate(Node*);
		Node* fixBalance(Node*);
		
		// Accessors
		int getHeight(Node*); // Returns the height of a given node (-1 if NULL)
		int getBalance(Node*); // Returns the balance of a given node (0 if NULL)
		int getSubsize(Node*); // Returns the subtree size of a given node (0 if NULL)
		
		// Mutators
		void setHeight(Node*, int); // Modifies the height of a given node, if feasible
		void setSubsize(Node*, int); // Modifies the subtree size counter of a given node, if feasible
		void setParent(Node*, Node*); // Modifies the parent pointer of a given node, if feasible
		
		// Print methods
		string printPreOrder();
		string printPreOrder(Node* start);	
};
#endif
