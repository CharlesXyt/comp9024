#include "invertedIndex.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>


int order(invertnode *a) {
	if (a == NULL) {
		return 1;
	}
	int c;
	char *b;
	listnode *prev;
	listnode *first;
	listnode *curr;
	prev = a->urlList;
	if (prev->next == NULL) {
		return 1;
	}
	first = a->urlList->next;
	curr = a->urlList;
	while (curr != NULL) {
		while (first != NULL) {
			if (prev->count > first->count) {
				c = first->count;
				first->count = prev->count;
				prev->count = c;
				b = prev->url;
				prev->url = first->url;
				first->url = b;
			}
			first = first->next;
			prev = prev->next;
		}
		first = a->urlList->next;
		prev = a->urlList;
		curr = curr->next;
	}
	return order(a->left) && order(a->right);
}
