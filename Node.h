#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/**
* Node is a struct of pointer-val to pointer-val
**/
typedef struct Node {
	int val;
	struct Node* next;
} Node;

//Functions
Node* makeNode(int);

