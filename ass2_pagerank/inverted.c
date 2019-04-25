#include "invertedIndex.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>







void output(invertnode*a, FILE *fp) {
	fprintf(fp, "%s ", a->key);
	listnode *curr;
	curr = a->urlList;
	while (curr->next != NULL) {
		fprintf(fp, "%s ", curr->url);
		curr = curr->next;
	}
	fprintf(fp, "%s\n", curr->url);
}


void printinvert(invertnode*a, FILE*fp) {
	if (a == NULL) {
		return;
	}
	printinvert(a->left, fp);
	output(a, fp);
	printinvert(a->right, fp);
}

int main(void) {
	char** a;
	a = GetCollection();
	invertnode *p;
	p = GetinvertedList(a);
	order(p);
	FILE *fp;
	fp = fopen("invertedIndex.txt", "w");
	printinvert(p, fp);
	fclose(fp);
	int i;
	for (i = 0; i < atoi(a[0]) + 1; i++) {
		free(a[i]);
	}
	free(a);
	freeinvertlist(p);
	return 1;
}

