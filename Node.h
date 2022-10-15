#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC

/**
* Node is a struct of pointer-val to pointer-val
**/
typedef struct Node {
	int val;
	int weight;
	struct Node* next;
} Node;

//Functions
Node* makeNode(int, int);

