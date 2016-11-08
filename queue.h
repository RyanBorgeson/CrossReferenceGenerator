/**
 * Queue provides methods for inserting, removing,
 * and initializing queues that will hold line numbers for each
 * identifier.
 * @Author Ryan Borgeson
 * @Date 11/8/2016
 **/
 #define QUEUE_SIZE 100

/* Queue structure definition. */
typedef struct Queue {
    int LineQueue[QUEUE_SIZE];
    int Front;
    int Back;
} Queue;


/**
 * Initializes a queue by setting the values for the front
 * and back of the queue.
 * @param q The queue to initialize.
 **/
void InitQueue(Queue * q);

/**
 * Dequeues or removes a queued line number from the queue
 * and returns it.
 * @param q The queue to dequeue.
 * @return Returns the first line number in the queue.
 **/
int Dequeue(Queue * q);

/**
 * Enqueue add additional line numbers to a specific queue.
 * @param q The queue to add to.
 * @param Line The line number to add to the back of the queue.
 **/
void Enqueue(Queue * q, int Line);