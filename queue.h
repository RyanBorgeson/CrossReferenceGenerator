#define QUEUE_SIZE 100


typedef struct Queue {
    int LineQueue[QUEUE_SIZE];
    int Front;
    int Back;
} Queue;