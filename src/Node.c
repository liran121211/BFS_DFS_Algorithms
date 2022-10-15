#include "Node.h"

Node* makeNode(int new_val, int weight) {
	Node* new_node = (Node*)malloc(sizeof(Node));

	if (new_node == NULL)
		return NULL;

	new_node->next = NULL;
	new_node->val = new_val;
	new_node->weight = weight;
	return new_node;
}
