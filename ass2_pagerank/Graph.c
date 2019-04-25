// Graph ADT
// Adjacency Matrix Representation ... COMP9024 17s2
#include "Graph.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



typedef struct GraphRep {
	List *edges;  // array of lists
	int   nV;     // #vertices
	int   nE;     // #edges
	char **point;
} GraphRep;


Graph newGraph(char **a) {
	assert(atoi(a[0]) >= 0);
	int i;
	int j;
	Graph g = malloc(sizeof(GraphRep));
	assert(g != NULL);
	g->nV = atoi(a[0]);
	g->nE = 0;
	// allocate memory for array of lists
	g->edges = malloc(g->nV * sizeof(List));
	assert(g->edges != NULL);
	for (i = 0; i < g->nV; i++)
		g->edges[i] = NULL;
	g->point = malloc(g->nV * sizeof(char *));
	for (j = 0; j < g->nV; j++) {
		g->point[j] = malloc(20 * sizeof(char));
		strcpy(g->point[j], a[j + 1]);
	}
	return g;
}

// check if vertex is valid in a graph
bool validV(Graph g, Vertex v) {
	int i;
	if (g == NULL) {
		return false;
	}
	for (i = 0; i < g->nV; i++) {
		if (!strcmp(v, g->point[i])) {
			return true;
		}
	}
	return false;
}

void insertEdge(Graph g, Edge e) {
	assert(g != NULL && validV(g, e.v) && validV(g, e.w));
	int i;
	int j;
	for (i = 0; i < g->nV; i++) {
		if (!strcmp(g->point[i], e.v)) {
			break;
		}
	}
	for (j = 0; j < g->nV; j++) {
		if (!strcmp(g->point[j], e.w)) {
			break;
		}
	}
	if (!inLL(g->edges[i], e.w)) {   // edge e not in graph
		g->edges[i] = insertLL(g->edges[i], e.w);
		g->edges[j] = insertLL(g->edges[j], e.v);
		g->nE++;
	}
}

void removeEdge(Graph g, Edge e) {
	assert(g != NULL && validV(g, e.v) && validV(g, e.w));
	int i;
	int j;
	for (i = 0; i < g->nV; i++) {
		if (!strcmp(g->point[i], e.v)) {
			break;
		}
	}
	for (j = 0; j < g->nV; j++) {
		if (!strcmp(g->point[j], e.w)) {
			break;
		}
	}
	if (inLL(g->edges[i], e.w)) {   // edge e in graph
		g->edges[i] = deleteLL(g->edges[i], e.w);
		g->edges[j] = deleteLL(g->edges[j], e.v);
		g->nE--;
	}
}

bool adjacent(Graph g, Vertex v, Vertex w) {
	assert(g != NULL && validV(g, v));
	int i;
	for (i = 0; i < g->nV; i++) {
		if (!strcmp(g->point[i], v)) {
			break;
		}
	}
	return inLL(g->edges[i], w);
}

void showGraph(Graph g) {
	assert(g != NULL);
	int i;
	printf("Number of vertices: %d\n", g->nV);
	printf("Number of edges: %d\n", g->nE);
	for (i = 0; i < g->nV; i++) {
		printf("%s - ", g->point[i]);
		showLL(g->edges[i]);
	}
}

void freeGraph(Graph g) {
	assert(g != NULL);
	int i;
	int j;
	for (i = 0; i < g->nV; i++)
		freeLL(g->edges[i]);
	for (j = 0; j < g->nV; j++) {
		free(g->point[j]);
	}
	free(g->point);
	free(g);
}