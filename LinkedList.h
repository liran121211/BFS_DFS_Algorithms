#pragma once
#include"Node.h"
#define EMPTY -1

/**
* Linked List struct represent array like type of Nodes struct.
* size - array current size.
*  arr - linked Nodes struct.
**/
typedef struct LinkedList {
	unsigned int size;
	struct Node* arr;
} LinkedList;

//Functions
LinkedList* List();
void addTail(LinkedList*, int);
void printList(LinkedList*);
Node* getHead(LinkedList*);
Node* getTail(LinkedList*);
void removeTail(LinkedList*);
void removeHead(LinkedList*);
void deallocLinkedList(LinkedList*);


