
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
	n->Line = q;
	n->Next = NULL;
	
	if (LinkedList->Head == NULL && LinkedList->Tail == NULL) {
		
		LinkedList->Head = n;
		LinkedList->Tail = n;
		LinkedList->Head->Line->LineQueue[0] = Line;
		LinkedList->Head->Line->Back = -1;
		LinkedList->Head->Line->Front = 0;
		
	} else {
		Node * s = SearchNodes(LinkedList, Identifier);
		
		if (s == NULL) {
			Enqueue(n->Line, Line);
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

void ListNodes(LList * LinkedList, char * FileName) {
	FILE *f = fopen(FileName, "w");
	
	Node * tmp = LinkedList->Head;
	
	while (tmp != NULL) {
		fprintf(f, "%-20s\t", tmp->Identifier);
		
		int Last;
				
		while ((Last = Dequeue(tmp->Line)) != -1) {
			fprintf(f, "%d ", Last);
		}
		
		fprintf(f, "\n");
		
		tmp = tmp->Next;
	}
	
	fclose(f);
}