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
	first = a->urlList;
	curr = a->urlList;
	while (first != NULL) {
		while (curr->next != NULL) {
			if (strcmp(curr->url, curr->next->url) > 0) {
				c = curr->next->count;
				curr->next->count = curr->count;
				curr->count = c;
				b = curr->next->url;
				curr->next->url = curr->url;
				curr->url = b;
			}
			curr = curr->next;
		}
		first = first->next;
		curr = prev;
	}
	return order(a->left) && order(a->right);
}															//order the url for each word in ascending order

void freeinvertlist(invertnode *a) {
	if (a != NULL) {
		freeinvertlist(a->left);
		freeinvertlist(a->right);
		listnode *prev = a->urlList;
		while (prev->next != NULL) {
			a->urlList = a->urlList->next;
			free(prev);
			prev = a->urlList;
		}
		free(prev);
		free(a);
	}
}															//free the space for the invertnode