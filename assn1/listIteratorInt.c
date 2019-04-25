/*
listIteratorInt.c : list Iterator ADT implementation
Written by ....
Date: ....
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "listIteratorInt.h"

typedef struct Node {
	int value;
	struct Node *pre;
	struct Node *next;
} Node;

typedef struct IteratorIntRep {
	int flag;
	int cursor;
	Node *head;
	Node *cur;
	Node *tail;
} IteratorIntRep;



static Node *newNode(int it)
{
	Node *new;
	new = malloc(sizeof(Node));
	assert(new != NULL);
	new->value = it;
	new->pre = new->next = NULL;
	return new;
}



IteratorInt IteratorIntNew() {
	IteratorIntRep *new;
	new = malloc(sizeof(IteratorIntRep));
	assert(new != NULL);
	new->flag = -1;
	new->cursor = 0;
	new->head = new->cur = new->tail = NULL;
	return new; 
}

void reset(IteratorInt it) {
	it->cursor = 0;
	it->cur = it->head;
}


int add(IteratorInt it, int v) {
	Node* new;
	if (it->head == NULL) {
		new = newNode(v);
		it->head = it->tail = it->cur = new;
		it->cursor = 0;
		return 1;
	}
	new = newNode(v);
	new->next = it->cur->next;
	it->cur->next = new;
	new->pre = new->next->pre;
	new->next->pre = new;
	it->cur = it->cur->next;
	return 1;  
}


int hasNext(IteratorInt it) {
	if (it->cur != it->tail || it->cursor != 1) {
		return 1;
	}
	return 0;
}

int hasPrevious(IteratorInt it) {
	if (it->cur != it->head || it->cursor != 0) {
		return 1;
	}
	return 0;  // you need to change this...
}


int *next(IteratorInt it) {
	int n;
	n = hasNext(it);
	if (n == 1) {
		if (it->cur == it->tail) {
			it->cursor = 1;
			it->flag = 1;
			return it->value;
		}
		it->flag = 1;
		it->cur = it->cur->next;
		return it->cur->value;
	}
	else {
		return 0;
	}
}

int *previous(IteratorInt it) {
	int n;
	n = hasNext(it);
	if (n == 1) {
		if (it->cursor == 1) {
			it->cursor = 0;
			it->flag = 0;
			return it->cur->value;
		}
		it->cur = it->cur->pre;
		it->flag = 0;
		return it->cur->value;
	}
	return 0;
}


int deleteElm(IteratorInt it) {
	if (it->flag == 1) {
		Node *pro;
		pro = it->cur->pre;
		pro->pre->next = pro->next;
		pro->next->pre = pro->pre;
		free(pro);
		return 1;
	}
	if (it->flag == 0) {
		Node *pro;
		pro = it->cur->next;
		pro->pre->next = pro->next;
		pro->next->pre = pro->pre;
		free(pro);
		return 1;
	}
	return 0;  // you need to change this...
}


int set(IteratorInt it, int v) {
	if (it->flag == 1) {
		it->cur->pre->value = v;
		return 1;
	}
	if (it->flag == 0) {
		it->cur->next->value = v;
		return 1;
	}
	return 0;
}

int *findNext(IteratorInt it, int v) {
	int n;
	n = hasNext(it);
	Node *pro;
	pro = it->cur;
	if (n == 0) {
		return 0;
	}
	while (pro->value != v) {
		pro = pro->next;
		if (pro == NULL) {
			return 0;
		}
		if(pro->next == NULL) {
			it->cursor = 1;
			it->flag = 1;
			it->cur = pro;
			return 1;
		}
		it->flag = 1;
		it->cur = pro;
		return 1;
	}

	int *findPrevious(IteratorInt it, int v) {
		int n;
		n = hasPrevious(it);
		Node *pro;
		pro = it->cur->pre;
		if (n == 0) {
			return 0;
		}
		while (pro->value != v) {
			pro = pro->pre;
			if (pro == NULL) {
				return 0;
			}
			If(pro->pre == NULL) {
				it->cursor = 1;
				it->flag = 0;
				it->cur = pro;
				return 1;
			}
			it->flag = 0;
			it->cur = pro->next;
			return 1;
			// implement this function 
			return 0;
		}

		void freeIt(IteratorInt it) {
			assert(it != NULL);
			Node *cur, *pre;
			cur = it->head;
			while (cur != NULL) {
				pre = cur;
				cur = cur->next;
				free(pre);
			}
			free(it);
			// implement this function 
		}

		int main(void) {
			printf("hell0\n");
			return 0;
		}



