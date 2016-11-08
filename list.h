/**
 * List handles the functionality of the linked list such as adding
 * nodes, searching, and printing a list of all discovered identifiers in
 * order.
 * @Author Ryan Borgeson
 * @Date 11/8/2016
 **/
#include <stdio.h>
#include "queue.h"

#define MAX_IDENTIFIER 200

typedef struct Node {
	char Identifier[MAX_IDENTIFIER];
	Queue * Line;
	struct Node * Next;
} Node;

typedef struct LList {
	struct Node * Head;
	struct Node * Tail;
} LList;

/**
 * Initializs the linked list for both the head and tail.
 * @param LinkedList Linked List structure.
 **/
void InitList(LList * LinkedList);

/**
 * Adds a node to the linked list along with a line number.
 * Also, sorting and searching for existing identifiers is handled
 * within this method.
 * @param LinkedList The linked list.
 * @param Identifier The identifier to add.
 * @param Line The line number of the identifier.
 **/
void AddNode(LList * LinkedList, char * Identifier, int Line);

/**
 * Compares two nodes against each other to determine the correct
 * alphabetical order of the nodes based on their identifiers.
 * @param a The first node.
 * @param b The second node.
 * @return Returns negative if a > b and positive if b > a.
 **/
int CompareNodes (Node * a, Node * b);

/**
 * Sorts a linked list of nodes based on the identifiers.
 * Identifiers should appear in alphabetical order when scanning
 * through the linked list.
 * @param LinkedList Linked list to sort.
 **/
void SortLinkedList(LList * LinkedList);

/**
 * Searches through entire linked list and returns a node with
 * the specified identifier if one exists.
 * @param LinkedList The linked list.
 * @param Identifier The search criteria.
 * @return Returns an existing node or NULL.
 **/
Node * SearchNodes(LList * LinkedList, char * Identifier);

/**
 * List and prints all identifiers and their line numbers to
 * a text file.
 * @param LinkedList Linked list to print.
 * @param FileName Output file name.
 **/
void ListNodes(LList * LinkedList, char * FileName);