#pragma once
#include"LinkedList.h"
#define FIXED_WEIGHT 1

//Structs
typedef struct Queue {
    int front, rear, size;
    unsigned capacity;
    LinkedList* array;
}Queue;

//Functions
struct Queue* createQueue(size_t);
int isFull(struct Queue* );
int isEmpty(struct Queue* );
void enqueue(struct Queue* , int );
int dequeue(struct Queue*);
int front(struct Queue*);
int rear(struct Queue* );