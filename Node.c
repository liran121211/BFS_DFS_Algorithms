#include "Node.h"

Node* makeNode(int new_val) {
	Node* new_node = (Node*)malloc(sizeof(Node));

	if (new_node != NULL) {
		new_node->next = NULL;
		new_node->val = new_val;
		return new_node;
	}

	return NULL;
}
