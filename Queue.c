#include "Queue.h"

// function to create a queue
// of given capacity.
// It initializes size of queue as 0
struct Queue* createQueue(size_t capacity)
{
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));

    if (queue == NULL)
        return NULL;

    queue->capacity = capacity;
    queue->front = queue->size = 0;

    // This is important, see the enqueue
    queue->rear = capacity - 1;
    queue->array = List();
    return queue;
}

// Queue is full when size becomes
// equal to the capacity
int isFull(struct Queue* queue)
{
    return (queue->size == queue->capacity);
}

// Queue is empty when size is 0
int isEmpty(struct Queue* queue)
{
    return (queue->size == 0);
}

// Function to add an item to the queue.
// It changes rear and size
void enqueue(Queue* queue, int item)
{
    if (isFull(queue)) {
        printf("Queue capacity exceeded.\n");
        return;
    }

    queue->rear = (queue->rear + 1)% queue->capacity;
    addTail(queue->array, item);
    queue->size = queue->size + 1;
    printf("[%d] enqueued to queue\n", item + 1);
}

// Function to remove an item from queue.
// It changes front and size
int dequeue(Queue* queue)
{
    if (isEmpty(queue)) {
        printf("Queue is empty.\n");
        return EMPTY;
    }

    int item = getHead(queue->array)->val;
    queue->front = (queue->front + 1) % queue->capacity;
    removeHead(queue->array);
    queue->size = queue->size - 1;
    printf("[%d] dequeued from queue\n", item + 1);

    return item;
}

// Function to get front of queue
int front(struct Queue* queue)
{
    if (isEmpty(queue))
        return EMPTY;
    return getHead(queue->array)->val;
}

// Function to get rear of queue
int rear(struct Queue* queue)
{
    if (isEmpty(queue))
        return EMPTY;
    return getTail(queue->array)->val;
}