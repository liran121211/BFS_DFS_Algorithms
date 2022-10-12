#include "NeighborhoodList.h"
#include "Queue.h"
#define VERTICES_SIZE 6
#define INFINITE INT_MAX
#define WHITE 0
#define GRAY 1
#define BLACK 2
#define NILL -1

// GLOBAL VARIABLES
int d[VERTICES_SIZE]; // start time / distance
int f[VERTICES_SIZE]; // finish time
int pi[VERTICES_SIZE]; // ancestor vertex
int Color[VERTICES_SIZE]; // vertices colors
int time; // time counter for DFS algorithm
Queue* vertices_queue = NULL;

//Functions
void BFS(LinkedList** , Node* );
void DFS(LinkedList**);
void DFS_Visit(LinkedList**, Node*, int);
void printTable(int*, size_t, int*, size_t, int*, size_t, int*, size_t, int);
void deallocGraph(LinkedList**);

int main(int argc, char* argv) {
	LinkedList** vertex = createNeighborhoodList(VERTICES_SIZE);

	addNeighbor(vertex, 1, 2);
	addNeighbor(vertex, 1, 5);
	//
	addNeighbor(vertex, 2, 1);
	addNeighbor(vertex, 2, 5);
	addNeighbor(vertex, 2, 3);
	addNeighbor(vertex, 2, 4);
	//
	addNeighbor(vertex, 3, 2);
	addNeighbor(vertex, 3, 4);
	//addNeighbor(vertex, 3, 6);
	//
	addNeighbor(vertex, 4, 2);
	addNeighbor(vertex, 4, 5);
	addNeighbor(vertex, 4, 3);
	//
	addNeighbor(vertex, 5, 4);
	addNeighbor(vertex, 5, 1);
	addNeighbor(vertex, 5, 2);
	//addNeighbor(vertex, 5, 6);
	//
	addNeighbor(vertex, 6, 3);

	printVertices(vertex, VERTICES_SIZE);
	BFS(vertex, vertex[0]->arr->next);
	//DFS(vertex);
	deallocGraph(vertex);
	free(vertex);
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
		
		while(G[dequeued_val]->arr!=NULL){
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
	printTable(d, sizeof(d) / sizeof(int), f, sizeof(f) / sizeof(int), pi, sizeof(pi) / sizeof(int), Color, sizeof(Color) / sizeof(int), S->val);
	free(vertices_queue);
	free(head);
}

void DFS(LinkedList** G) {
	for (size_t u = 0; u < VERTICES_SIZE; u++) { // iterate all vertices
		pi[u] = NILL;
		Color[u] = WHITE;
	}

	time = 0;
	for (size_t u = 0; u < VERTICES_SIZE; u++)
		if (Color[u] == WHITE)
			DFS_Visit(G, G[u]->arr, u);

	printTable(d, sizeof(d) / sizeof(int), f, sizeof(f) / sizeof(int), pi, sizeof(pi) / sizeof(int), Color, sizeof(Color) / sizeof(int), NILL);
}

void DFS_Visit(LinkedList** G, Node* V, int u) {
	Color[u] = GRAY; // update current vertex val
	time += 1;
	d[u] = time;

	while (G[u]->arr != NULL) {
		if (Color[G[u]->arr->val] == WHITE) {
			pi[u] = G[u]->arr->val;
			DFS_Visit(G, G[u]->arr, G[u]->arr->val);
		}
		G[u]->arr = G[u]->arr->next;
	}
	Color[u] = BLACK;
	time += 1;
	f[u] = time;
}

void printTable(int* distances, size_t d_size, int* finish, size_t f_size, int* pi, size_t pi_size, int* colors, size_t colors_size, int source_vertex) {
	if (source_vertex != NILL)
		printf("\nStarting Vertex: %d\n", source_vertex + 1);

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

	if (source_vertex == NILL){
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
			printf("|NULL | ");
		else
			printf("|%-4d | ", pi[i]);
	}
	printf("\n");

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
	printf("----------------------------------------------------------\n");
	
	if (source_vertex == NILL)
		printf("Time: %d\n", time);
}

void deallocGraph(LinkedList** G) {
	if (G == NULL) // if Graph is NULL.
		return;

	for (size_t i = 0; i < VERTICES_SIZE; i++)
		deallocLinkedList(G[0]);
}
