/**
 * List handles the functionality of the linked list such as adding
 * nodes, searching, and printing a list of all discovered identifiers in
 * order.
 * @Author Ryan Borgeson
 * @Date 11/8/2016
 **/
#include "list.h"



void InitList(LList * LinkedList) {
	// Set the initial linked list contents to NULL.
	LinkedList->Head = NULL;
	LinkedList->Tail = NULL;
}


void AddNode(LList * LinkedList, char * Identifier, int Line) {
	// Allocate memory for a node a queue.
	Node * n = malloc(sizeof * n);
	Queue * q = malloc(sizeof(Queue));
	
	// Initialize Queue
	InitQueue(&q);
	
	// Copy identifier to the node and initialize the queue
	// in the node.
	strncpy(n->Identifier, Identifier, MAX_IDENTIFIER);
	n->Line = q;
	n->Next = NULL;
	
	// If no nodes exist, create the first one.
	if (LinkedList->Head == NULL && LinkedList->Tail == NULL) {
		LinkedList->Head = n;
		LinkedList->Tail = n;
		
	} else {
		// Search every node to see if the identifier already exists.
		Node * s = SearchNodes(LinkedList, Identifier);
		
		// If none exist, create one.
		if (s == NULL) {
			Enqueue(n->Line, Line);
			LinkedList->Tail->Next = n;
			LinkedList->Tail = n;
				
		} else {
			// Otherwise, add another line number to the queue for the
			// selected node.
			Enqueue(s->Line, Line);
		}
	}
	
	// Finally, sort all the nodes in the linked list to ensure
	// they are in alphabetical order.
	SortLinkedList(LinkedList);
}

int CompareNodes (Node * a, Node * b) {
	// Compare both identifiers in each node to determine
	// how to sort.
    int Comparison = strcasecmp(a->Identifier, b->Identifier);
    return Comparison ? Comparison : -strcmp(a->Identifier, b->Identifier);
}

void SortLinkedList(LList * LinkedList) {
	// Grab the first and second identifiers in the linked list.
	Node * First = LinkedList->Head;
	Node * Second = First->Next;
	
	// Temperarily holds when flipping orders.
	Node Temp;
	
	while (First != NULL) {
		
		// Break if no second identifier exists.
		if (Second == NULL) break;
		
		// Compare the nodes and determine if the need to be flipped.
		if (CompareNodes(First, Second) > 0) {
			
			// Store the first identifier and switch the first identifier
			// with the second one.
			Temp = *First;
			strncpy(First->Identifier, Second->Identifier, MAX_IDENTIFIER);
			First->Line = Second->Line;
			
			// Place the temp into the second identifier.
			strncpy(Second->Identifier, Temp.Identifier, MAX_IDENTIFIER);
			Second->Line = Temp.Line;
		}
		
		// Continue for each node in the linked list.
		First = First->Next;
		Second = First->Next;
	}
}

Node * SearchNodes(LList * LinkedList, char * Identifier) {
	Node * Temp = LinkedList->Head;
	
	while (Temp != NULL) {
		// If a node exists with the same identifier, then
		// return that node.
		if (strcmp(Temp->Identifier, Identifier) == 0)
			return Temp;
		
		Temp = Temp->Next;
	}
	
	// If nothing exists return null.
	return NULL;
}

void ListNodes(LList * LinkedList, char * FileName) {
	FILE *f = fopen(FileName, "w");
	
	// Create a temperary node of the head.
	Node * Temp = LinkedList->Head;
	int Line; // Holds the line.
	
	// Loop through each node to display the identifier.
	while (Temp != NULL) {
		fprintf(f, "%-20s\t", Temp->Identifier);
		
		// Dequeue each line number off the line queue for this
		// identifier until none are left.
		while ((Line = Dequeue(Temp->Line)) != -1) {
			fprintf(f, "%d ", Line);
		}
		
		fprintf(f, "\n");
		
		// Continue to next identifier.
		Temp = Temp->Next;
	}
	
	fclose(f);
}