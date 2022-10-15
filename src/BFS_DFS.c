#include "Queue.h"
#include "BFS_DFS.h"
#define VERTICES_SIZE 6

// GLOBAL VARIABLES
int d[VERTICES_SIZE]; // start time / distance
int f[VERTICES_SIZE]; // finish time
int pi[VERTICES_SIZE]; // ancestor vertex
int Color[VERTICES_SIZE]; // vertices colors
int time; // time counter for DFS algorithm
Queue* vertices_queue = NULL;

int run(char* mode) {
	LinkedList** vertex = createNeighborhoodList(VERTICES_SIZE);

	addNeighbor(vertex, 1, 2, FIXED_WEIGHT);
	addNeighbor(vertex, 1, 5, FIXED_WEIGHT);
	//
	addNeighbor(vertex, 2, 1, FIXED_WEIGHT);
	addNeighbor(vertex, 2, 5, FIXED_WEIGHT);
	addNeighbor(vertex, 2, 3, FIXED_WEIGHT);
	addNeighbor(vertex, 2, 4, FIXED_WEIGHT);
	//
	addNeighbor(vertex, 3, 2, FIXED_WEIGHT);
	addNeighbor(vertex, 3, 4, FIXED_WEIGHT);
	//addNeighbor(vertex, 3, 6, FIXED_WEIGHT);
	//
	addNeighbor(vertex, 4, 2, FIXED_WEIGHT);
	addNeighbor(vertex, 4, 5, FIXED_WEIGHT);
	addNeighbor(vertex, 4, 3, FIXED_WEIGHT);
	//
	addNeighbor(vertex, 5, 4, FIXED_WEIGHT);
	addNeighbor(vertex, 5, 1, FIXED_WEIGHT);
	addNeighbor(vertex, 5, 2, FIXED_WEIGHT);
	//
	addNeighbor(vertex, 6, 3, FIXED_WEIGHT);

	printVertices(vertex, VERTICES_SIZE); // print Graph scheme

	if (strcmp(mode, "BFS") == 0)
		BFS(vertex, vertex[0]->arr->next);
	else if (strcmp(mode, "DFS") == 0)
		DFS(vertex);
	else
		exit(EXIT_FAILURE);

	deallocGraph(vertex); // free allocated memory
	free(vertex); // free allocated memory

	return EXIT_SUCCESS;
}

void BFS(LinkedList** G, Node* S) {

	for (size_t v = 0; v < VERTICES_SIZE; v++) {
		d[v] = INFINITE;
		pi[v] = NILL;
		Color[v] = WHITE;
	}

	// init first vertex
	d[S->val] = 0;
	Color[S->val] = GRAY;
	vertices_queue = createQueue(VERTICES_SIZE);
	Node* head = NULL;

	enqueue(vertices_queue, S->val);
	while (!isEmpty(vertices_queue)) {
		int dequeued_val = dequeue(vertices_queue);
		head = G[dequeued_val]->arr; // save head pointer

		while (G[dequeued_val]->arr != NULL) {
			int child = G[dequeued_val]->arr->val;
			if (Color[child] == WHITE) {
				if (d[child] == INFINITE) // check if value is infinite, if so change to zero and count.
					d[child] = 0;

				d[child] = d[dequeued_val] + 1;
				pi[child] = dequeued_val;
				Color[child] = GRAY;
				enqueue(vertices_queue, child);
			}
			G[dequeued_val]->arr = G[dequeued_val]->arr->next;
		}
		G[dequeued_val]->arr = head;
		Color[dequeued_val] = BLACK;
	}
	printTable(d, sizeof(d) / sizeof(int), f, sizeof(f) / sizeof(int), pi, sizeof(pi) / sizeof(int), Color, sizeof(Color) / sizeof(int), S->val, "BFS");
	free(vertices_queue);
	free(head);
}

void DFS(LinkedList** G) {
	for (size_t u = 0; u < VERTICES_SIZE; u++) { // iterate all vertices
		Color[u] = WHITE;
		pi[u] = NILL;
	}

	time = 0;
	for (size_t u = 0; u < VERTICES_SIZE; u++)
		if (Color[u] == WHITE)
			DFS_Visit(G, G[u]->arr, u);

	printTable(d, sizeof(d) / sizeof(int), f, sizeof(f) / sizeof(int), pi, sizeof(pi) / sizeof(int), Color, sizeof(Color) / sizeof(int), NILL, "DFS");
}

/**
* G - lists of linked list (Graph).
* u - current vertex (Node).
*  v_num = vertex value (int).
**/
void DFS_Visit(LinkedList** G, Node* u, int v_num) {
	if (G == NULL || u == NULL)
		return;

	Color[v_num] = GRAY; // update current vertex val.
	time++;
	d[v_num] = time;

	while (u != NULL) {
		if (Color[u->val] == WHITE) {
			pi[u->val] = u->val;
			DFS_Visit(G, G[u->val]->arr, u->val);
		}
		u = u->next;
	}

	Color[v_num] = BLACK;
	time += 1;
	f[v_num] = time;
}

void printTable(int* distances, size_t d_size, int* finish, size_t f_size, int* pi, size_t pi_size, int* colors, size_t colors_size, int source_vertex, char* mode) {
	if (strcmp(mode, "DFS") == 0)
		printf("\nStarting Vertex: %d\n", source_vertex + 1);
	else
		printf("\nStarting Vertex: %d\n", source_vertex);

	printf("\n|Vertex    ");
	for (size_t i = 0; i < VERTICES_SIZE; i++)// columns names (vertices).
		printf("|%-4d | ", i + 1);
	printf("\n");

	printf("----------------------------------------------------------\n");
	printf("|Distances ");
	for (size_t i = 0; i < d_size; i++) { // distances values.
		if (distances[i] == INFINITE)
			printf("|INF  | ");
		else
			printf("|%-4d | ", distances[i]);
	}
	printf("\n");

	if (strcmp(mode, "DFS") == 0) {
		printf("|Finish    ");
		for (size_t i = 0; i < d_size; i++) { // distances values.
			if (finish[i] == INFINITE)
				printf("|INF  | ");
			else
				printf("|%-4d | ", finish[i]);
		}
		printf("\n");
	}

	printf("|Pi \t   ");
	for (size_t i = 0; i < pi_size; i++) { // pi values.
		if (pi[i] == NILL)
			printf("|NILL | ");
		else
			printf("|%-4d | ", pi[i]);
	}
	printf("\n");

	if (strcmp(mode, "DFS") == 0 || strcmp(mode, "BFS") == 0) {
		printf("|Colors    ");
		for (size_t i = 0; i < colors_size; i++) { // colors values.
			if (colors[i] == WHITE)
				printf("|W    | ");
			if (colors[i] == GRAY)
				printf("|G    | ");
			if (colors[i] == BLACK)
				printf("|B    | ");
		}
		printf("\n");
	}
	printf("----------------------------------------------------------\n");

	if (strcmp(mode, "DFS") == 0) 
		printf("Time: %d\n", time);
}

	void deallocGraph(LinkedList * *G) {
		if (G == NULL) // if Graph is NULL.
			return;

		for (size_t i = 0; i < VERTICES_SIZE; i++)
			deallocLinkedList(G[0]);

		free(G);
	}
