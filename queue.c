#include "queue.h"


void InitQueue(Queue * q) {
    q->Front = 0;
    q->Back = -1;
}

int Dequeue(Queue * q) {
	q->Front++;
    return (q->Front > q->Back) ? -1 : q->LineQueue[q->Front - 1];
}

void Enqueue(Queue * q, int Line) {
    if(q->Back < QUEUE_SIZE - 1) {
		q->LineQueue[q->Back] = Line;
		q->Back++;
	}
}