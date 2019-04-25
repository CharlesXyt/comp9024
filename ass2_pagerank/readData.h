#include <stdbool.h>
#include "Graph.h"

typedef struct Node {
	char*         v;
	struct Node  *next;
} Node;

typedef struct GraphRep {
	List *edges;  // array of lists
	int   nV;     // #vertices
	int   nE;     // #edges
	char **point;
} GraphRep;

typedef struct listnode {
	char* url;
	int   count;
	struct listnode *next;
}listnode;

typedef struct invertnode {
	char* key;
	listnode* urlList;
    struct invertnode *left;
	struct invertnode *right;
}invertnode;


char **GetCollection(void);
Graph GetGraph(char **a);
invertnode *GetinvertedList(char**);
void freeNode(Node *);