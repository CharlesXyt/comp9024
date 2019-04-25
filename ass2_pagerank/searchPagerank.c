#include "readData.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>



typedef struct searchnode {
	Node **url;
	char **words;
}searchnode;

typedef struct pagenode {
	char *url;
	int count;
	float pagerank;
	struct pagenode* next;
}pagenode;

Node *creatNode(char* n) {
	Node* new = malloc(sizeof(Node));
	assert(new != NULL);
	new->v = malloc(20 * sizeof(char));
	strcpy(new->v, n);
	new->next = NULL;
	return new;
}

int judgeurl(char *a) {
	int i;
	for (i = 0; i < (int)strlen(a); i++) {
		if (isdigit(a[i]))
			return 1;
	}
	return 0;
}


searchnode *readurl(int m, char **str) {
	searchnode *p;
	int sign;
	int i;
	Node *t;
	p = malloc(sizeof(searchnode));
	p->url = malloc(m * sizeof(Node *));
	p->words = malloc(m * sizeof(char*));
	for (i = 0; i < m; i++) {
		p->words[i] = malloc(strlen(str[i]) * sizeof(char));
		strcpy(p->words[i], str[i]);
	}
	FILE *fp;
	char str1[20];
	fp = fopen("invertedIndex.txt", "r");
	sign = fscanf(fp, "%s", str1);
	while (true) {
		if (sign == -1) {
			break;
		}
		for (i = 0; i < m; i++) {
			if (!strcmp(p->words[i], str1)) {
				p->url[i] = creatNode(str1);
				t = p->url[i];
				while (true) {
					sign = fscanf(fp, "%s", str1);
					if (sign == -1) {
						break;
					}
					if (judgeurl(str1)) {
						t->next = creatNode(str1);
						t = t->next;
					}
					else {
						break;
					}
				}

			}
		}
		sign = fscanf(fp, "%s", str1);
	}
	return p;
}

pagenode *readrank() {
	int flag;
	pagenode *a;
	FILE *fp;
	char str[20];
	fp = fopen("pagerankList.txt", "r");
	a = malloc(sizeof(struct pagenode));
	pagenode *curr;
	fscanf(fp, "%s", str);
	str[strlen(str)-1] = '\0';
	a->url = malloc((int)strlen(str) * sizeof(char));
	strcpy(a->url, str);
	fscanf(fp, "%s", str);
	fscanf(fp, "%s", str);
	a->pagerank = atof(str);
	a->next = NULL;
	a->count = 0;
	curr = a;
	while (true) {
		flag = fscanf(fp, "%s", str);
		if (flag == -1)
			break;
		curr->next = malloc(sizeof(struct pagenode));
		curr->next->url = malloc((int)strlen(str) * sizeof(char));
		str[strlen(str) - 1] = '\0';
		strcpy(curr->next->url, str);
		fscanf(fp, "%s", str);
		fscanf(fp, "%s", str);
		curr->next->pagerank = atof(str);
		curr->next->count = 0;
		curr = curr->next;
	}
	curr->next = NULL;
	return a;
}

int calcu(char *url,pagenode *a) {
	while (a != NULL) {
		if (!strcmp(a->url, url)) {
			a->count++;
			return 1;
		}
		a = a->next;
	}
	return 0;
}

void ordernode(pagenode *a){
	pagenode *curr;
	pagenode *first;
	curr = a;
	first = a;
	char *m;
	int n;
	float l;
	while (a!= NULL) {
		curr = first;
		while (curr->next != NULL) {
			if ((curr->next->count > curr->count)|| (curr->next->count == curr->count && curr->next->pagerank > curr->pagerank)) {
				m = curr->next->url;
				curr->next->url = curr->url;
				curr->url = m;

				n = curr->next->count;
				curr->next->count = curr->count;
				curr->count = n;

				l = curr->next->pagerank;
				curr->next->pagerank = curr->pagerank;
				curr->pagerank = l;
			}
			curr = curr->next;
		}
		a = a->next;
	}
}
void freePgnode(pagenode *L) {
	if (L != NULL) {
		freePgnode(L->next);
		free(L);
	}
}


int main(int argc,char *argv[]) {
	searchnode *p;
	int i;
	Node *curr;
	char **str1;
	str1 = malloc((argc-1) * sizeof(char *));
	for (i = 0; i < argc-1; i++) {
		str1[i] = malloc(strlen(argv[i+1]) * sizeof(char));
		strcpy(str1[i], argv[i + 1]);
	}
	p = readurl(argc-1, str1);
	pagenode *a;
	a = readrank();
	for (i = 0; i < argc-1; i++) {
		curr = p->url[i]->next;
		while (curr != NULL) {
			if (calcu(curr->v, a)) {
				curr = curr->next;
			}
			else {
				printf("%s\n", "error");
			}
		}
	}
	ordernode(a);
	while (a->count > 0) {
		printf("%s\n", a->url);
		a = a->next;
	}
	for (i = 0; i < argc-1; i++) {
		free(p->words[i]);
		freeNode(p->url[i]);
	}
	free(p);
	freePgnode(a);
	return 1;
}