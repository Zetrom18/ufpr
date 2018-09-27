#include "graph.h"

void create_vertex(Graph g, void* content){
	Vertex v;

	while(g->n >= g->n_max){
	/* Realloc if needed */

		g->n_max = g->n_max*2;

		g->vertex_list = realloc(g->vertex_list, sizeof(Vertex) * g->n_max);
		assert(g->vertex_list);
	}

	v = (Vertex) malloc(sizeof(struct vertex));
	assert(v);

	v->n = 0;
	v->size = 2;
	v->depth = 0;
	v->content = content;
	v->nbh = (Vertex*) malloc(sizeof(Vertex) * v->size);
	assert(v->nbh);

	g->vertex_list[g->n] = v;
	g->n++;
}

Graph create_graph(int n){
	int i;
	Graph g;

	g = (Graph) malloc(sizeof(struct graph));
	assert(g);

	g->m = 0;
	g->h = 0;
	g->n_max = (n+1) * 2;

	g->vertex_list = (Vertex*) malloc(sizeof(Vertex) * g->n_max);
	assert(g->vertex_list);

	for(i=0; i<n; i++){
		create_vertex(g, NULL);
	}

	return g;
}

void destroy_graph(Graph g){

	while(g->n > 0){
		destroy_vertex(g, g->vertex_list[0]);
	}

	free(g->vertex_list);
	free(g);
}

int vertex_count(Graph g){
	return g->n;
}

int edge_count(Graph g){
	return g->m;
}

bool edge_exists(Vertex a, Vertex b){
	int i;

	if (a->n == 0){
		return false;
	}

	for(i=0; i<a->n; i++){
		if(a->nbh[i]==b){
			return true;
		}
	}

	return false;
}

void create_edge(Graph g, Vertex a, Vertex b){
	while(a->n >= a->size){
	/* Realloc if needed */

		a->size = a->size*2;

		a->nbh = realloc(a->nbh, sizeof(Vertex) * a->size);
		assert(a->nbh);
	}

	set_vertex_depth(g, b, a->depth+1);

	a->nbh[a->n] = b;
	a->n++;
	g->m++;
}

void remove_from_vertex_list(Vertex* array, int index, int size){
	int i;

	for(i=index; i<size; i++){
		if(i+1 < size){
			array[i] = array[i+1];
		}else{
			array[i] = NULL;
		}
	}
}

void destroy_edge(Graph g, Vertex a, Vertex b){
	int i;
	bool found = false;

	for(i=0; i<a->n; i++){
		if(a->nbh[i]==b){
			found = true;
			break;
		}
	}

	if(found){
		remove_from_vertex_list(a->nbh, i, a->n);
		a->n--;
		g->m--;
		for(i=0; i<g->n; i++){
			if(edge_exists(g->vertex_list[i], b)){
				set_vertex_depth(g, b, g->vertex_list[i]->depth+1);
			}
		}
	}
}

Vertex pop_vertex(Graph g, Vertex a){
	int i,j;

	while(a->n > 0){
		destroy_edge(g, a, a->nbh[0]);
	}

	for(i=0; i<g->n; i++){
		for(j=0; j<g->vertex_list[i]->n; j++){
			if(g->vertex_list[i]->nbh[j]==a){
				destroy_edge(g, g->vertex_list[i], a);
			}
		}
	}

	for(i=0; i<g->n; i++){
		if(g->vertex_list[i]==a){
			remove_from_vertex_list(g->vertex_list, i, g->n);
			g->n--;
			break;
		}
	}

	return a;
}

void* destroy_vertex(Graph g, Vertex a){
	Vertex aux = pop_vertex(g, a);
	void* content = aux->content;

	free(aux->nbh);
	free(aux);

	return content;
}

void add_vertex(Graph g, Vertex a){
	while(g->n >= g->n_max){
	/* Realloc if needed */

		g->n_max = g->n_max*2;

		g->vertex_list = realloc(g->vertex_list, sizeof(Vertex) * g->n_max);
		assert(g->vertex_list);
	}

	g->vertex_list[g->n] = a;

	g->n++;
}

Graph copy_graph(Graph g){
	int i,j;
	void* cAux;
	Graph gAux = create_graph(0);

	for(i=0; i<g->n; i++){
		if(g->vertex_list[i]->content != NULL){
			cAux = malloc(sizeof(g->vertex_list[i]));
			cAux = g->vertex_list[i]->content;
		}else{
			cAux = NULL;
		}

		create_vertex(gAux, cAux);
	}

	for(i=0; i<gAux->n; i++){
		for(j=0; j<gAux->vertex_list[i]->n; j++){
			create_edge(gAux, gAux->vertex_list[i], gAux->vertex_list[i]->nbh[j]);
		}
	}

	return gAux;
}

void set_vertex_depth(Graph g, Vertex v, int d){
	int i;

	if(v->depth==0 || d < v->depth){
		v->depth = d;

		set_graph_depth(g);

		for(i=0; i<v->n; i++){
			set_vertex_depth(g, v->nbh[i], d+1);
		}
	}
}

void set_graph_depth(Graph g){
	int i;

	g->h = 0;

	for(i=0; i<g->n; i++){
		if(g->h<g->vertex_list[i]->depth){
			g->h = g->vertex_list[i]->depth;
		}
	}
}













