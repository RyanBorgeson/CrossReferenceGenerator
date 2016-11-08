#include "queue.h"


void InitQueue(Queue * q) {
    q->Front = 0;
    q->Back = 5;
	
}

int Dequeue(Queue * q) {
    return q->LineQueue[ (q->Front)++ ];
}

void Enqueue(Queue * q, int Line) {
		printf("%i ", q->Back);
    if(q->Back < QUEUE_SIZE - 1) {
	//	q->Back++;
	//	q->LineQueue[ q->Back ] = Line;
	}
        
}

