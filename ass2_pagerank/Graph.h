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


Graph newGraph(char**);  					//make new graph
void  insertEdge(Graph, Edge);  			//insert edges into graph
void  removeEdge(Graph, Edge);				//remove edge from graph
bool  adjacent(Graph, Vertex, Vertex);		//judge vertex if they are adjacent 
void  showGraph(Graph);
void  freeGraph(Graph); 					//free space
