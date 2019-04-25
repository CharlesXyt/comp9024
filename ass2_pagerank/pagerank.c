#include "pagerank.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

typedef struct ranknode {
	char* url;
	float rank;
	int deg;
	struct ranknode *next;
}ranknode;

ranknode *makenode(char*a,Graph g) {
	ranknode *p = malloc(sizeof(ranknode));
	p->url = malloc(strlen(a) * sizeof(char));
	strcpy(p->url, a);
	p->rank = (float)1.0 / g->nV;
	p->next = NULL;
	p->deg = 0;
	return p;
}

float outdeg(List a) {
	float i = 0;
	while (a != NULL) {
		i++;
		a = a->next;
	}
	return i;
}
int contain(List a,char *b) {
	while (a != NULL) {
		if (!strcmp(a->v, b)) {
			return 1;
		}
		a = a->next;
	}
	return 0;
}

float sumpg(ranknode *a,Graph g,ranknode *head) {
	float sum = 0;
	List h = g->edges[0];
	int i =0;
	char *m;
	m = a->url;
	while (head !=NULL) {
		if (contain(h,m)) {
			sum = sum + (head->rank) / outdeg(h);
		}
		head = head->next;
		i++;
		h = g->edges[i];
	}
	return sum;
}


ranknode *calculatePageRank(Graph g, float d, float dpr, int maxI) {
	int i = 0;
	int j;
	float diff = dpr;
	ranknode *new;
	ranknode *first;
	float rank;
	float diff_mid = 0;
	new = makenode(g->point[0], g);
	first = new;
	new->deg = (int)outdeg(g->edges[0]);
	for (j = 1; j < g->nV; j++) {
		new->next = makenode(g->point[j], g); 
		new->next->deg = (int)outdeg(g->edges[j]);
		new = new->next;
	}
	while (i < maxI&&diff >= dpr) {
		diff = 0;
		ranknode *curr = first;
		while (curr != NULL) {
			rank = (1 - d) / (g->nV) + d * sumpg(curr, g, first);
			diff_mid = (float)(rank - curr->rank);
			if (diff_mid < 0)
				diff_mid *= -1;
			curr->rank = rank;
			curr = curr->next;
			diff += diff_mid;
		}
		i++;
	}
	return first;
}

int ordernode(ranknode *a) {
	ranknode *curr;
	ranknode *first;
	float i;
	char *j;
	int k;
	if (a->next == NULL) {
		return 1;
	}
	first = a;
	curr = first;
	while (curr != NULL) {
		a = first;
		while (a->next != NULL) {
			if (a->rank < a->next->rank) {
				i = a->next->rank;
				a->next->rank = a->rank;
				a->rank = i;
				j = a->next->url;
				a->next->url = a->url;
				a->url = j;
				k = a->next->deg;
				a->next->deg = a->deg;
				a->deg = k;
			}
			a = a->next;
		}
		curr = curr->next;
	}
	return 1;
}

int main(int argc, char *argv[]) {
	Graph p;
	char **a;
	ranknode *r;
	FILE *fp;
	a = GetCollection();
	p = GetGraph(a);
	r = calculatePageRank(p,atof(argv[1]), atof(argv[2]), atof(argv[3]));
	ordernode(r);
	fp = fopen("pagerankList.txt", "w");
	assert(fp != NULL);
	ranknode *first = r;
	while (r != NULL) {
		fprintf(fp, "%s, %d, %.7f\n", r->url, r->deg, r->rank);
		r = r->next;
	}
	fclose(fp);
	freeGraph(p);
	int i;
	for (i = 0; i < atoi(a[0]) + 1; i++) {
		free(a[i]);
	}
	free(a);
	ranknode *prev = first;
	while (prev->next != NULL) {
		first = prev->next;
		free(prev);
		prev = first;
	}
	free(prev);
	return 1;
}