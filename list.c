#include <stdio.h>
#include "list.h"




void InitList(LList * LinkedList) {
	LinkedList->Head = NULL;
	LinkedList->Tail = NULL;
}


void AddNode(LList * LinkedList, char * Identifier, int Line) {
	Node * n = malloc(sizeof(Node));
	
	strncpy(n->Identifier, Identifier, MAX_IDENTIFIER);
	n->Line = Line;
	
	if (LinkedList->Head == NULL && LinkedList->Tail == NULL) {
		LinkedList->Head = n;
		LinkedList->Tail = n;
	} else {
		LinkedList->Tail->Next = n;
		LinkedList->Tail = n;
	}
}

void ListNodes(LList * LinkedList) {
	Node *tmp = LinkedList->Head;
	
	while (tmp != NULL) {
		printf("Node: %s\n", tmp->Identifier);
		tmp = tmp->Next;
	}
}