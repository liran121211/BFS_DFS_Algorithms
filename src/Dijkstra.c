#include "Dijkstra.h"
#define VERTICES_SIZE 5

int d[VERTICES_SIZE]; // accumulated distance
int pi[VERTICES_SIZE]; // ancestor of vertex
LinkedList* s; // spanning tree
MinHeap* Q; // vertices group

/**
* G - lists of linked list (Graph).
* S - initial vertex to start from (Node).
**/
Dijkstra(LinkedList** G, Node* S) {
	for (size_t v = 0; v < VERTICES_SIZE; v++) { // Init arrays to inital values.
		d[v] = INFINITE;
		pi[v] = NILL;
	}

	d[S->val - 1] = 0; // set distance from initial vertex to zero.
	s = List(); // init spanning tree linked list.

	Q = makeMinHeap(VERTICES_SIZE);
	for (size_t v = 0; v < VERTICES_SIZE; v++) // Build Heap
		insertKey(Q, v, d[v]);

	// Iterate on all vertices to find minimal path.
	while (Q->heap_size > 0) {
		Node* u = extractMin(Q); // get min value Node and remove it from Heap.
		s->arr = u; // save extracted min Node to spanning tree.
		Node* v = G[u->val]->arr; // make code cleaner.
		Node* head = G[u->val]->arr;

		// find mininal neighbor of (u) vertex. 
		while (v != NULL) {
			Relax(u, v, v->weight);
			v = v->next;
		}
		s->arr = s->arr->next; // update spanning tree list.
		v = head;

		if (Q->heap_size == 0) { // free allocated pointers.
			free(u);
			free(head);
		}
	}
	printTable(d, sizeof(d) / sizeof(int), NULL, NILL, pi, sizeof(pi) / sizeof(int), NULL, NILL, S->val, "Dijkstra");

}

/**
* u - current minimal path Node.
* v - current neighbor of (u) vertex (Node).
*  w - weight of (u,v) Edge.
**/
void Relax(Node* u, Node* v, int w) {
	if (d[v->val] > d[u->val] + w) {
		d[v->val] = d[u->val] + w;
		pi[v->val] = u->val;
		decreaseKey(Q, v->val, w); // update new Node value (weight) in Heap.
		MinHeapify(Q, 0); // rearrange MinHeap.
	}
}

int main(int argc, char* argv[]) {
	MinHeap* m_heap = makeMinHeap(VERTICES_SIZE);
	LinkedList** vertex = createNeighborhoodList(VERTICES_SIZE);

	addNeighbor(vertex, 1, 2, 10); /*(s)*/
	addNeighbor(vertex, 1, 3, 5); /*(s)*/
	//
	addNeighbor(vertex, 2, 4, 1); /*(a)*/
	addNeighbor(vertex, 2, 3, 2); /*(a)*/
	//
	addNeighbor(vertex, 3, 2, 3); /*(b)*/
	addNeighbor(vertex, 3, 4, 9); /*(b)*/
	addNeighbor(vertex, 3, 5, 2); /*(b)*/
	//
	addNeighbor(vertex, 4, 5, 4); /*(c)*/
	//
	addNeighbor(vertex, 5, 4, 6); /*(d)*/
	addNeighbor(vertex, 5, 1, 7); /*(d)*/
	printVertices(vertex, VERTICES_SIZE); // print Graph scheme.

	Dijkstra(vertex, vertex[0]->arr);

	deallocMinHeap(m_heap);
	deallocGraph(vertex); // free allocated memory.
	free(s); // free allocated spanning tree.
	free(Q); // free allocated MinHeap.

	return EXIT_SUCCESS;
}