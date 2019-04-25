// Graph ADT interface ... COMP9024 17s2
#include <stdbool.h>
#include "list.h"


typedef struct GraphRep *Graph;

// vertices are ints
typedef char* Vertex;
typedef struct Edge{
	Vertex v;
	Vertex w;
} Edge;
// edges are pairs of vertices (end-points)


Graph newGraph(char**);
void  insertEdge(Graph, Edge);
void  removeEdge(Graph, Edge);
bool  adjacent(Graph, Vertex, Vertex);
void  showGraph(Graph);
void  freeGraph(Graph); 
