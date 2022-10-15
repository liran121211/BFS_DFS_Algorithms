#include"LinkedList.h"

LinkedList* List() {
	LinkedList* new_list = (LinkedList*)malloc(sizeof(LinkedList));
	if (new_list != NULL) {
		new_list->size = 0;
		new_list->arr = NULL;
	}
	return new_list;
}


void addTail(LinkedList* list, int val, int weight) {
	if (list == NULL)
		return;

	Node* head = list->arr; // save head pointer

	if (list->arr == NULL) {
		list->arr = makeNode(val, weight);
		list->size++;
		return;
	}

	while (list->arr->next != NULL)
		list->arr = list->arr->next;

	list->arr->next = makeNode(val, weight);
	list->size++;
	list->arr = head; // return to head of the list.
}

Node* getTail(LinkedList* list) {
	Node* head = list->arr; // save head pointer
	Node* result = NULL;


	while (list->arr->next != NULL)
		list->arr = list->arr->next;

	result = list->arr;
	list->arr = head;

	return result;
}

Node* getHead(LinkedList* list) {
	return list->arr;
}


void printList(LinkedList* list) {
	if (list->arr == NULL)
		printf("Empty List...\n");
	else {
		Node* head = list->arr;
		while (list->arr != NULL) {
			if (list->arr->next != NULL)
				printf("[Value:%d|Weight:%d]-->", list->arr->val + 1, list->arr->weight);
			else
				printf("[Value:%d|Weight:%d]", list->arr->val + 1, list->arr->weight);
			list->arr = list->arr->next;
		}
		printf("\n");
		list->arr = head; // return to head of the list.
	}
}

void removeTail(LinkedList* list) {
	Node* removable_node = NULL; // keep node for deallocation.

	if (list == NULL) // if list is NULL.
		return;

	if (list->arr == NULL) // if list is empty.
		return;

	Node* head = list->arr;

	if (list->arr->next == NULL) { // if only 1 node to delete
		removable_node = list->arr;
		list->arr = NULL;
		list->size--;
		free(removable_node);
		return;
	}

	while (list->arr->next->next != NULL) // iterate till last node
		list->arr = list->arr->next;

	removable_node = list->arr->next;
	list->arr->next = NULL;
	list->arr = head;
	list->size--;
	free(removable_node);
}

void removeHead(LinkedList* list) {
	Node* removable_node = NULL; // keep node for deallocation.

	if (list == NULL) // if list is NULL.
		return;

	if (list->arr == NULL) // if list is empty.
		return;

	if (list->arr->next == NULL) {
		list->arr = NULL;
		list->size--;
	}
	else {
		removable_node = list->arr;
		list->arr = list->arr->next;
		list->size--;
		free(removable_node); // free allocated node.
	}
}
void deallocLinkedList(LinkedList* list) {
	if (list == NULL) // if list is NULL.
		return;

	while (list->size != 0) { // keep deleting node utill list is empty.
		removeTail(list);
	}
}

Node* findNode(LinkedList* list, int val) {
	Node* temp = list->arr;

	while (temp != NULL) {
		if (temp->val == val)
			return temp;
		temp = temp->next;
	}

	return NULL;
}

void ModifyNode(LinkedList* list, int index, int new_val) {
	if(findNode(list, index)!= NULL)
		findNode(list, index)->val = new_val;
}