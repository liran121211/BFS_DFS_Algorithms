#include "LinkedList.h"
#include "NeighborhoodList.h"

#define INFINITE INT_MAX
#define WHITE 0
#define GRAY 1
#define BLACK 2
#define NILL -1

//Functions
void BFS(LinkedList**, Node*);
void DFS(LinkedList**);
void DFS_Visit(LinkedList**, Node*, int);
void printTable(int*, size_t, int*, size_t, int*, size_t, int*, size_t, int, char*);
void deallocGraph(LinkedList**);
int run(char*);