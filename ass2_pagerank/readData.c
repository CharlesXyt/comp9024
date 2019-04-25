
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "readData.h"


char *turn(char *str) {
	char *orign = str;
	int i;
	for (i = 0;i < strlen(str); i++)
		str[i] = tolower(str[i]);
	return orign;
}

listnode *newlistnode(char* a) {
	listnode *b;
	b = malloc(sizeof(listnode));
	assert(b != NULL);
	b->url = malloc(strlen(a) * sizeof(char));
	assert(b->url != NULL);
	strcpy(b->url, a);
	b->count = 1;
	b->next = NULL;
	return b;
}

invertnode *newinvertnode(char* word, char* url) {
	invertnode *a;
	a = malloc(sizeof(invertnode));
	assert(a != NULL);
	a->key = malloc(strlen(word) * sizeof(char));
	assert(a->key != NULL);
	strcpy(a->key, word);
	a->urlList = newlistnode(url);
	a->left = NULL;
	a->right = NULL;
	return a;
}

int add_in_urllist(listnode *a,char *b){
	listnode *curr;
	curr = a;
	while (curr->next != NULL) {
		if (!strcmp(curr->url, b)) {
			curr->count++;
			return 1;
		}
		curr = curr->next;
	}
	if (!strcmp(curr->url, b)) {
		curr->count++;
		return 1;
	}
	else {
		listnode *new;
		new = newlistnode(b);
		curr->next = new;
		return 1;
	}
	return 0;
}

int insert_word_in_invertlist(invertnode *a,char *word,char *url) {
	if (!strcmp(a->key,word)) {
		add_in_urllist(a->urlList,url);
		return 1;
		}
	if (strcmp(a->key, word) > 0) {
		if (a->left == NULL) {
			a->left = newinvertnode(word, url);
			return 1;
		}
		return insert_word_in_invertlist(a->left, word, url);
	}
	if (strcmp(a->key, word) < 0) {
		if (a->right == NULL) {
			a->right = newinvertnode(word, url);
			return 1;
		}
		return insert_word_in_invertlist(a->right, word, url);
	}
	return 0;
}





char **GetCollection() {
	FILE *fp;
	char **p;
	char str[10];
	int time = 1;
	fp = fopen("collection.txt", "r");
	int count = 0;
	while (fscanf(fp, "%s", str) != EOF) {
		count++;
	}
	fclose(fp);
	fp = fopen("collection.txt", "r");
	p = malloc((count + 1) * sizeof(char *));
	p[0] = malloc(20 * sizeof(char));
	sprintf(p[0], "%d", count);
	for (; time < (count + 1); time++) {
		p[time] = malloc(20 * sizeof(char));
		fscanf(fp, "%s", p[time]);
	}
	fclose(fp);
	return p;
}
void freeNode(Node *L) {
	if (L != NULL) {
		freeNode(L->next);
		free(L->v);
		free(L);
	}
}

Graph GetGraph(char **a) {
	Graph p;
	p = newGraph(a);
	int i;
	int j = 0;
	Node* first;
	FILE *fp;
	char str[20];
	char name[20];
	char txt[20];
	strcpy(txt, ".txt");
	char str1[20] = "Section-1";
	char str2[20] = "#end";
	for (i = 0; i < p->nV; i++) {
		strcpy(name, p->point[i]);
		strcat(name, txt);
		fp = fopen(name, "r");
		j = 0;
		while (true) {
			fscanf(fp, "%s", str);
			if (!strcmp(str, str1)) {
				while (true) {
					fscanf(fp, "%s", str);
					if (!strcmp(str, str2)) {
						break;
					}
					Node *new;
					new = malloc(sizeof(Node));
					assert(new != NULL);
					new->v = malloc(20 * sizeof(char));
					strcpy(new->v, str);
					new->next = NULL;
					if (j == 0) {
						p->edges[i] = new;
						first = p->edges[i];
					}
					else {
						first->next = new;
						first = first->next;
					}
					j++;
				}
				break;
			}
		}
		fclose(fp);
	}
	return p;
}


invertnode *GetinvertedList(char** a) {
	invertnode *p;
	int i;
	int j = 0;
	int m;
	int n;
	char name[20];
	char txt[20];
	char *str;
	char ori[20];
	strcpy(txt, ".txt");
	char str1[20] = "Section-2";
	char str2[20] = "#end";
	FILE *fp;
	for (i = 1; i <= atoi(a[0]); i++) {
		strcpy(name, a[i]);
		strcat(name, txt);
		fp = fopen(name, "r");
		while (true) {
			fscanf(fp, "%s", ori);
			if (!strcmp(ori, str1)) {
				while (true) {
					fscanf(fp, "%s", ori);
					str = turn(ori);
					if (!strcmp(str, str2)) {
						break;
					}
					for (m = n = 0; n < strlen(str); n++) {
						if (!ispunct(str[n])) {
							str[m++] = str[n];
						}
					}
					str[m] = '\0';
					if (j == 0) {
						p = newinvertnode(str, a[i]);
					}
					else {
						insert_word_in_invertlist(p, str, a[i]);
					}
					j = 1;
				}
				break;
			}
		}
		fclose(fp);
	}
	return p;
}

