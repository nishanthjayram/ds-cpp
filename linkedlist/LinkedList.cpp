/*
    Implementation of singly linked list of integers. This implements the methods described
    in the header file.
    
	Author  :  Nishanth Jayram (https://github.com/njayram44)
	Date    :  December 25, 2020
*/

#include "LinkedList.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

// Default constructor sets head to NULL
LinkedList :: LinkedList()
{
	head = NULL;
}

// Inserts a new node at the head of the list.
// Input: Int - to be inserted into the list as a node
// Output: Void - only inserts new Node
void LinkedList :: insert(int x)
{
    Node *n = new Node; // Initialize new node to contain the data
    n->data = x; // Initialize data attribute
    n->next = head; // Add to the list at the front
    head = n;
}

// Finds a Node with the matching data, if it exists.
// Input: Data to be found
// Output: Node* a pointer to a Node containing the val, if it exists. Otherwise, returns NULL.
Node* LinkedList :: find(int x)
{
    Node *curr = head;
    while (curr != NULL)
    {
        // If the matching data is foumd, return a pointer to the Node that contains it.
        if (curr->data == x)
            return curr;
        curr = curr->next;
    }

    return NULL; // Data was not found throughout traversal, so return NULL
}

// Container method for sorting the list, starting from the head.
// Input: None
// Output: None - only sorts the list.
void LinkedList :: sort()
{
    sort(head);
}

// Sorts the list from starting Node through bubble sort.
// Input: Pointer to the Node to start from
// Output: Void - only mutates the list to run in order
void LinkedList :: sort(Node* start)
{
    bool isSwapped; // Flag to track whether a pass involved any swaps
    Node *a;
    Node *b = NULL;

    if (start == NULL) // If list empty or has singleton element, do nothing
        return;
    
    do
    {
        isSwapped = false; // No swaps yet
        a = start;

        while (a->next != b) // Traverse the list
        {
            if (a->data > a->next->data) // Check if Node a ranks higher than its successor
            {
                swap(a, a->next); // Swap the data of the nodes to sort them
                isSwapped = true; // A swap has been done, so this is now true
            }
            a = a->next;
        }
        b = a;
    } while (isSwapped); // Keep making passes until there are no more swaps to be done
}

// Helper function for sort() that swaps the data between two Nodes.
// Input: Nodes to swap data between
// Output: Void - only swaps data
void LinkedList :: swap(Node* a, Node* b)
{
    int temp = a->data;
    a->data = b->data;
    b->data = temp;
}

// Prints list in order
// Input: None
// Output: A string that has all elements of the list in order
string LinkedList :: print()
{
    string list_str = ""; // The string to contain the list
	Node *curr = head;
	
    while(curr->next != NULL){
        list_str = list_str + to_string(curr->data) + " -> "; // Append string with current Node's data
		curr = curr->next;
	}
    list_str = list_str + to_string(curr->data); // Append last element of the list

    return list_str;
}

// length(): Computes the length of the linked list
// Input: None
// Output: int - length of list
int LinkedList :: length()
{
    int length = 0;
    Node *curr = head;
    
    // Iterate through the list and update the length each time.
    while (curr != NULL) {
        length++;
        curr = curr->next;
    }

    return length;
}
