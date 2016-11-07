#include "queue.h"


void InitQueue(Queue * q) {
    q->Front = 0;
    q->Back = -1;
}

int Dequeue(Queue * q) {
    return q->Queue[ (q->Front)++ ];
}

void Enqueue(Queue * q, int Line) {
    if(q->Back < QUEUE_SIZE - 1)
        q->Queue[ ++(q->Back) ] = Line;
}

