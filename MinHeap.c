#include "MinHeap.h"

int parent(size_t i) {
	return (i - 1) / 2;
}

int left(size_t i) {
	return (2 * i + 1);
}

int right(size_t i) {
	return (2 * i + 2);
}

Node* getMin(MinHeap* heap) {
	return &heap->harr[0];
}

void swap(Node* x, Node* y)
{
	int temp_val = x->val;
	int temp_weight = x->weight;
	x->val = y->val;
	x->weight = y->weight;
	y->val = temp_val;
	y->weight = temp_weight;
}

void MinHeapify(MinHeap* heap, int i) {
	int l = left(i);
	int r = right(i);
	int smallest = i;
	if (l < heap->heap_size && heap->harr[l].weight < heap->harr[i].weight)
		smallest = l;

	if (r < heap->heap_size && heap->harr[r].weight < heap->harr[smallest].weight)
		smallest = r;

	if (smallest != i) {
		swap(&heap->harr[i], &heap->harr[smallest]);
		MinHeapify(heap, smallest);
	}
}

void deleteKey(MinHeap* heap, int i)
{
	decreaseKey(heap, i, INT_MIN);
	extractMin(heap);
}

Node* extractMin(MinHeap* heap) {
	if (heap->heap_size <= 0)
		return NULL;
	if (heap->heap_size == 1) {
		heap->heap_size--;
		return &heap->harr[0];
	}

	// Store the minimum value, and remove it from heap
	Node root = heap->harr[0];
	heap->harr[0] = heap->harr[heap->heap_size - 1];
	heap->heap_size--;
	MinHeapify(heap, 0);

	return &root;
}

void decreaseKey(MinHeap* heap, int i, int new_val) {
	heap->harr[i].weight = new_val;
	while (i != 0 && heap->harr[parent(i)].weight > heap->harr[i].weight) {
		swap(&heap->harr[i], &heap->harr[parent(i)]);
		i = parent(i);
	}
}

void insertKey(MinHeap* heap, int v, int d) {
	if (heap->heap_size == heap->capacity) {
		printf("\nOverflow: Could not insertKey");
		return;
	}

	Node temp;
	temp.val = v; // vertex index
	temp.weight = d; // vertex distance
	temp.next = NULL;

	// First insert the new key at the end
	heap->heap_size++;
	int i = heap->heap_size - 1;
	heap->harr[i] = temp;

	// Fix the min heap property if it is violated
	while (i != 0 && heap->harr[parent(i)].weight > heap->harr[i].weight)
	{
		swap(&heap->harr[i], &heap->harr[parent(i)]);
		i = parent(i);
	}
}

MinHeap* makeMinHeap(size_t cap) {
	MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));

	if (heap == NULL)
		return NULL;

	heap->heap_size = 0;
	heap->capacity = cap;
	heap->harr = (Node*)malloc(sizeof(Node) * cap);

	if (heap->harr == NULL)
		return NULL;

	return heap;
}

void deallocMinHeap(MinHeap* heap) {
	free(heap->harr);
	free(heap);
}
