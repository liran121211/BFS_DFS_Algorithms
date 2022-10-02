#include "Queue.h"

LinkedList** createNeighborhoodList(size_t size) {
	LinkedList** neighborhood_list = (LinkedList**)malloc(sizeof(neighborhood_list) * size);
	if (neighborhood_list != NULL) {
		for (size_t i = 0; i < size; i++)
			neighborhood_list[i] = List();
		return neighborhood_list;
	}

	return NULL;
}

void addNeighbor(LinkedList** neighborhood_list, int vertex, int value) {
	addTail(neighborhood_list[vertex - 1], value - 1);
}

void printVertices(LinkedList** neighborhood_lists, int size) {
	if (neighborhood_lists == NULL)
		return;

	for (int i = 0; i < size; i++) {
		printf("|%d|==>", i + 1);
		printList(neighborhood_lists[i]);
	}
}
