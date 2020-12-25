/*
    Implementation of singly linked list of integers. This is the header file that provides
    class/method definitions.
    
	Author  :  Nishanth Jayram (https://github.com/njayram44)
	Date    :  December 25, 2020
*/

#ifndef LIST_H
#define LIST_H
using namespace std;

// Node struct to hold the data
struct Node
{
    int data; // Contains the actual data
    Node *next; // Pointer to the next Node in the list
};

class LinkedList
{
    private:
        Node *head; // Head of the linked list
        void sort(Node* start); // Sorts the list from a given starting Node.
        void swap(Node* a, Node* b); // Swaps the data between two Nodes.
    
    public:
        LinkedList(); // Default constructor
        void insert(int x); // Insert data into the list
        Node* find(int x); // Find given data in the list (if it exists), and return pointer to Node containing it
        string print(); // Returns a string of the list elements
        int length(); // Returns length of the linked list
        void sort(); // Sorts the entire list - first by decreasing rank, then by increasing lexicographic order.
};

#endif