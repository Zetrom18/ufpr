#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#define DEBUG true

struct vertex {
	int n;                          // Number of neighbours
	int size;                       // Maximum number of neighbours possible
	int depth;                      // Vertex depth in the graph
	struct vertex** nbh;            // Corresponding neighbourhood
	void* content;                  // Vertices content
};

struct graph {
	int n;                          // Number of vertices
	int m;                          // Number of edges
	int h;                          // Graph height (depth of the deepest vertex)
	int n_max;                      // Maximum number of vertices possible
	struct vertex** vertex_list;    // List containing all vertices
};

// Definition for easier use of pointers
typedef struct graph* Graph;
typedef struct vertex* Vertex;

// Creation
/* Given an already created Graph g, allocs a new vertex containing */
void create_vertex(Graph g, void* content);

void create_edge(Graph g, Vertex a, Vertex b);

Graph create_graph(int n);

// Utility
void test();

bool edge_exists(Vertex a, Vertex b);

int edge_count(Graph g);

int vertex_count(Graph g);

Vertex pop_vertex(Graph g, Vertex a);

void add_vertex(Graph g, Vertex a);

Graph copy_graph(Graph g);

void set_vertex_depth(Graph g, Vertex v, int d);

void set_graph_depth(Graph g);

// Destruction
void destroy_edge(Graph g, Vertex a, Vertex b);

void* destroy_vertex(Graph g, Vertex a);

void destroy_graph(Graph g);

