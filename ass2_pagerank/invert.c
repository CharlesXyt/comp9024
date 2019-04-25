//
//  invert.c
//  ass 2 b
//
//  Created by Yue Xiong on 31/1/18.
//  Copyright © 2018 Yue Xiong. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>



typedef struct Node{
    char    word[100];
    struct Node *next;
}Node;

typedef struct NodeRep {
    Node    *first;
    Node    *curr;
    Node    *last;
}NodeRep;

typedef struct ListNode{
    char    key[100];
    NodeRep *url;
    
    struct ListNode *next;
}ListNode;


typedef struct ListRep {
    int     nitems;
    ListNode *first;
    ListNode *curr;
    ListNode *last;
}ListRep;

Node *newNode(char *val) {
    Node *new;
    new = malloc(sizeof(Node));
    assert(new != NULL);
    strcpy(new->word, val);
    new->next = NULL;
    return new;
}

NodeRep *NodeStr() {
    struct NodeRep *L;
    L = malloc(sizeof (struct NodeRep));
    assert (L != NULL);
    L->first = NULL;
    L->last = NULL;
    L->curr = NULL;
    return L;
}

void insert(NodeRep *L, char *val){
    assert(L!= NULL);
    Node *addnew;
    addnew = malloc(sizeof(Node));
    assert(addnew != NULL);
    addnew = newNode(val);
    if (L->first == NULL && L->last == NULL) {
        L->curr = L->first = L->last = addnew;
    }
    else {
        L->last->next = addnew;
        L->curr = L->last = addnew;
    }
}


ListNode *newListNode(char *val)
{
    ListNode *new;
    new = malloc(sizeof(ListNode));
    assert(new != NULL);
    
    strcpy(new->key, val);  // for int, new->value = it;
    new->url = NULL;
    new->next = NULL;
    return new;
}


ListRep *ListStr() {
    struct ListRep *L;
    L = malloc(sizeof (struct ListRep));
    assert (L != NULL);
    L->first = NULL;
    L->last = NULL;
    L->curr = NULL;
    L->nitems = 0;
    return L;
}

void insertSetOrd(ListRep *L, char *val){
    assert(L!= NULL);
    ListNode *addnew;
    addnew = malloc(sizeof(ListNode));
    assert(addnew != NULL);
    addnew = newListNode(val);
    if (L->first == NULL && L->last == NULL) {
        L->curr = L->first = L->last = addnew;
    }
    else {
        L->last->next = addnew;
        L->curr = L->last = addnew;
    }
    L->nitems++;
}

void bubble_st(ListRep *L) {
    ListNode *p;
    ListNode *q;
    ListNode *temp;
	char a[100];
	NodeRep *b;
    for( p = L->first; p->next != NULL;p= p->next) {
        temp = p;
        for(q = p->next; q->next != NULL; q = q->next)
            if (strcmp(p->key,q->key)> 0){
				strcpy(a, q->key);
				strcpy(q->key, p->key);
				strcpy(p->key, a);
				b = q->url;
				q->url = p->url;
				p->url = b;
            }
    }
}

int main () {
    char line;
    char name[20];
    int c=0;
    FILE *f,*p;
    int k=0;
    int i;
	int j;
    if ((f = fopen ("collection.txt", "r")) == NULL) {
        printf("Error!\n");
        return (0);
    }
    while (fscanf(f,"%s",&line)!= EOF) {
        c++;
    }
    char  **b;
    char  **e;
	b = malloc(c * sizeof(char*));
	e = malloc(c * sizeof(char*));
	for (j = 0; j < c; j++) {
		b[j] = malloc(21 * sizeof(char));
		e[j] = malloc(21 * sizeof(char));
	}
    fseek(f,0,SEEK_SET);
    c = 0;
    while(fscanf(f,"%s",name)!=EOF){
		strcpy(b[c], name);
        strcpy(e[c],name);
        c += 1;
    }
    char degree[25];
    ListRep *L;
    L = ListStr();
    for(k=0;k<c;k++){
        char fl[100] = "";
        strcat(fl,strcat(b[k],".txt"));
        p = fopen(fl,"r");
        Node *new;
        new = newNode(e[k]);
        //printf("%s\n", new->word);
        while(fscanf(p,"%s",degree) != EOF){
            if (strcmp(degree,"Section-2")== 0){
                while (fscanf(p,"%s",degree) != EOF) {
                    if (strcmp(degree,"#end")== 0){
                        break;
                    }
                    else {
                        for(i=0;i<strlen(degree);i++){
                            if(degree[i]>='A'&& degree[i] <= 'Z') {
                                degree[i] += 32;
                            }
                            if (degree[i] == '.'|| degree[i] == ';'|| degree[i] == '?' || degree[i] == '!'){
                                degree[i] = '\0';
                            }
                        }
                    }
                    //printf("%s\n",degree);
                    //printf("%s\n",new->word);
                    if (L->nitems == 0){
                        
                        insertSetOrd(L, degree);
                        NodeRep *P;
                        P = NodeStr();
                        insert(P,e[k]);
                        L->curr->url = P;
                        //printf("%d\n",L->nitems);
                    }
                    else {
                        L->curr = L->first;
                        while (L->curr) {
                            if(strcmp(L->curr->key,degree) == 0){
                                NodeRep *P;
                                P = NodeStr();
                                P = L->curr->url ;
                                if (strcmp(L->curr->url->curr->word,e[k])==0) {
                                    break;
                                }
                                else {
                                insert(P,e[k]);
                                //printf("%d\n",L->nitems);
                                break;
                                }
                            }
                            else if(L->curr == L->last && strcmp(L->curr->key,degree) != 0) {
                                NodeRep *P;
                                P = NodeStr();
                                insertSetOrd(L, degree);
                                insert(P,e[k]);
                                L->curr->url = P;
                                //printf("%s\n",L->curr->url->curr->word);
                                break;
                            }
                            L->curr = L->curr->next;
                        }
                    }
                }
            }
        }
    }
    bubble_st(L);
    L->curr = L->first;
    //printf("%s\n",L->curr->url->curr->word);
    while(L->curr) {
        printf("%s ",L->curr->key);
        L->curr->url->curr = L->curr->url->first;
        while (L->curr->url->curr) {
            printf("%s ",L->curr->url->curr->word);
            L->curr->url->curr = L->curr->url->curr->next;
        }
        L->curr = L->curr->next;
        printf("\n");
    }
  
    FILE *l;
    l= fopen ("invertedIndex.txt", "w");
    L->curr = L->first;
    while(L->curr) {
        fprintf(l,"%s ",L->curr->key);
        L->curr->url->curr = L->curr->url->first;
        while (L->curr->url->curr) {
            fprintf(l,"%s ",L->curr->url->curr->word);
            L->curr->url->curr = L->curr->url->curr->next;
        }
        L->curr = L->curr->next;
        fprintf(l,"\n");
    }
	fclose(l);
	return 0;
}
                


