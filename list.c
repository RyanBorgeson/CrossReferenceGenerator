
#include "list.h"


Node * SearchNodes();

void InitList(LList * LinkedList) {
	LinkedList->Head = NULL;
	LinkedList->Tail = NULL;
}


void AddNode(LList * LinkedList, char * Identifier, int Line) {
	Node * n = malloc(sizeof * n);
	Queue * q = malloc(sizeof(Queue));
	
	
	
	// Initialize Queue
	InitQueue(&q);
	
	strncpy(n->Identifier, Identifier, MAX_IDENTIFIER);

	
	Enqueue(q, Line);
	n->Line = q;
	n->Next = NULL;
	
	if (LinkedList->Head == NULL && LinkedList->Tail == NULL) {
		LinkedList->Head = n;
		LinkedList->Tail = n;
	} else {
		Node * s = SearchNodes(LinkedList, Identifier);
		
		if (s == NULL) {
			LinkedList->Tail->Next = n;
			LinkedList->Tail = n;
		} else {
			Enqueue(s->Line, Line);
		}
	}
}

Node * SearchNodes(LList * LinkedList, char * Identifier) {
	Node * tmp = LinkedList->Head;
	
	while (tmp != NULL) {
		if (strcmp(tmp->Identifier, Identifier) == 0)
			return tmp;
		
		tmp = tmp->Next;
	}
	return NULL;
}

void ListNodes(LList * LinkedList) {
	Node *tmp = LinkedList->Head;
	
	while (tmp != NULL) {
		printf("Node: %s\t\t", tmp->Identifier);
		
		int i;
		for (i = tmp->Line->Front; i < tmp->Line->Back; i++) {
			printf("%i ", tmp->Line->LineQueue[i]);
		}
		printf("\n");
		
		tmp = tmp->Next;
	}
}