#include "NeighborhoodList.h"
#include "Queue.h"
#define VERTICES_SIZE 5
#define INFINITE INT_MAX
#define WHITE 0
#define GRAY 1
#define BLACK 2
#define NILL -1

// GLOBAL VARIABLES
int d[VERTICES_SIZE];
int pi[VERTICES_SIZE];
int Color[VERTICES_SIZE];
Queue* vertices_queue = NULL;

//Functions
void BFS(LinkedList** , Node* );
void printTable(int*, size_t, int*, size_t, int*, size_t, int);

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
	//
	addNeighbor(vertex, 4, 2);
	addNeighbor(vertex, 4, 5);
	addNeighbor(vertex, 4, 3);
	//
	addNeighbor(vertex, 5, 4);
	addNeighbor(vertex, 5, 1);
	addNeighbor(vertex, 5, 2);


	printVertices(vertex, VERTICES_SIZE);
	BFS(vertex, vertex[0]->arr->next);
	
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

	enqueue(vertices_queue, S->val);
	while (!isEmpty(vertices_queue)) {
		int dequeued_val = dequeue(vertices_queue);
		Node* head = G[dequeued_val]->arr; // save head pointer
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
	printTable(d, sizeof(d) / sizeof(int), pi, sizeof(pi) / sizeof(int), Color, sizeof(Color) / sizeof(int), S->val);
	free(vertices_queue);
}

void printTable(int* distances, size_t d_size, int* pi, size_t pi_size, int* colors, size_t colors_size, int source_vertex) {
	printf("----------------------------\n");
	printf("Source Vertex: %d\n", source_vertex + 1);
	printf("|Vertices  ");
	for (size_t i = 0; i < VERTICES_SIZE; i++)// columns names (vertices).
		printf("| %d | ", i + 1);
	printf("\n");

	printf("|Distances ");
	for (size_t i = 0; i < d_size; i++) { // distances values.
		if (distances[i] == INFINITE)
			printf("| INF | ");
		else
			printf("| %d | ", distances[i]);
		}
		printf("\n");

		printf("|Pi \t   ");
		for (size_t i = 0; i < pi_size; i++) { // pi values.
			if (pi[i] == NILL)
				printf("| NULL | ");
			else
				printf("| %d | ", pi[i]);
		}
		printf("\n");

		printf("|Colors    ");
		for (size_t i = 0; i < colors_size; i++) { // colors values.
			if (colors[i] == WHITE)
				printf("| WHITE | ");
			if (colors[i] == GRAY)
				printf("| GRAY | ");
			if (colors[i] == BLACK)
				printf("| BLACK | ");
		}
		printf("\n");
		printf("----------------------------\n");
		exit(EXIT_SUCCESS);
}
