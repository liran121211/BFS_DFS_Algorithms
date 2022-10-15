#pragma once
#include "Node.h"


//Struct
typedef struct MinHeap
{
	int heap_size;
	int capacity;
	Node* harr;
} MinHeap;


//Functions
MinHeap* makeMinHeap(size_t);
void swap(Node*, Node*); // Prototype of a utility function to swap two integers
void MinHeapify(MinHeap*, int); // to heapify a subtree with the root at given index
void decreaseKey(MinHeap*, int, int); // Decreases key value of key at index i to new_val
void deleteKey(MinHeap*, int); // Deletes a key stored at index i
void insertKey(MinHeap*, int, int); // Inserts a new key 'k'
int parent(size_t); // to get index of parent node at index i
int left(size_t); // to get index of left child of node at index i
int right(size_t); // to get index of right child of node at index i
Node* extractMin(MinHeap*); // to extract the root which is the minimum element
Node* getMin(MinHeap*); // Returns the minimum key (key at root) from min heap
void deallocMinHeap(MinHeap*); // deallocate MinHeap memory
