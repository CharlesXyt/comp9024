// Linked list implementation ... COMP9024 17s2
#include "list.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
	char*         v;
	struct Node  *next;
} Node;

Node *makeNode(char* n) {
	Node* new = malloc(sizeof(Node));
	assert(new != NULL);
	new->v = malloc(20 * sizeof(char));
	strcpy(new->v, n);
	new->next = NULL;
	return new;
}

List insertLL(List L, char* n) {
	if (inLL(L, n))
		return L;
	// add new node at the beginning
	Node *new = makeNode(n);
	new->next = L;
	return new;
}

List deleteLL(List L, char* n) {
	if (L == NULL)
		return L;
	if (L->v == n)
		return L->next;
	L->next = deleteLL(L->next, n);
	return L;
}

bool inLL(List L, char* n) {
	if (L == NULL)
		return false;
	if (strcmp(L->v, n))
		return true;
	return inLL(L->next, n);
}

void showLL(List L) {
	if (L == NULL)
		putchar('\n');
	else {
		printf("%s ", L->v);
		showLL(L->next);
	}
}

void freeLL(List L) {
	if (L != NULL) {
		freeLL(L->next);
		free(L->v);
		free(L);
	}
}