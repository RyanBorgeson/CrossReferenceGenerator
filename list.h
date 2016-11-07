#define MAX_IDENTIFIER 200

typedef struct Node {
	char Identifier[MAX_IDENTIFIER];
	int Line;
	struct Node * Next;
} Node;

typedef struct LList {
	struct Node * Head;
	struct Node * Tail;
} LList;


void TestList();