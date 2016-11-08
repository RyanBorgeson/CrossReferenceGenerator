/**
 * Queue provides methods for inserting, removing,
 * and initializing queues that will hold line numbers for each
 * identifier.
 * @Author Ryan Borgeson
 * @Date 11/8/2016
 **/
#include "queue.h"


void InitQueue(Queue * q) {
	// Setup initial values for back and front
	// of the queue.
    q->Front = 0;
    q->Back = -1;
}

int Dequeue(Queue * q) {
	q->Front++;
	
	// Return the next element in the queue. If no elements are left,
	// return a -1.
    return (q->Front > q->Back) ? -1 : q->LineQueue[q->Front - 1];
}

void Enqueue(Queue * q, int Line) {
	// Add another line number to the specified queue.
    if(q->Back < QUEUE_SIZE - 1) {
		q->LineQueue[q->Back] = Line;
		q->Back++;
	}
}