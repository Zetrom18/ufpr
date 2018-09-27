#include "graph.h"
#include "floodit.h"

Graph read_file(){
	int i,j;
	int n, m, c;
	int* matrix;    // Given problems experienced, the color matrix is in reality a vector
	Island cont;
	Graph g;

	fscanf(stdin, "%d %d %d", &n, &m, &c);

	printf("Linhas: %d\nColunas: %d\nColors: %d\n", n, m, c);

	matrix = (int *)malloc(sizeof(int)*n*m);
	assert(matrix);

	for(i=0; i<n; i++){
		for(j=0; j<m; j++){
			fscanf(stdin, "%d", &matrix[i*n+j]);
		}
	}

	assert(matrix[n*m-1]);

//	for(i=0; i<n; i++){
//		for(j=0; j<m; j++){
//			printf("%d ", matrix[i*n+j]);
//		}
//		puts("");
//	}

	g = create_graph(n*m);

	for(i=0; i<n; i++){
		for(j=0; j<m; j++){
			cont = malloc(sizeof(Island));
			assert(cont);

			cont->size = 1;
			cont->color = matrix[i*n+j];

			g->vertex_list[i*m+j]->content = cont;

			if(i-1>=0){
				create_edge(g, g->vertex_list[(i-1)*m+j], g->vertex_list[i*m+j]);
			}
			if(j-1>=0){
				create_edge(g, g->vertex_list[i*m+(j-1)], g->vertex_list[i*m+j]);
			}
			if(i-1>=0 && j-1>=0){
				create_edge(g, g->vertex_list[(i-1)*m+(j-1)], g->vertex_list[i*m+j]);
			}
			if(i-1>=0 && j+1>=0 && j+1<m){
				create_edge(g, g->vertex_list[(i-1)*m+(j+1)], g->vertex_list[i*m+j]);
			}
		}
	}

	assert(test_matrix_size(g)==n*m);

	connect_game(g);

	assert(test_matrix_size(g)==n*m);

//	print_graph(g);

	return g;
}

void connect_game(Graph g){
	int i,j;

	for(i=0; i<g->n; i++){
		j=can_connect(g->vertex_list[i]);
		while(j >= 0){
			merge_islands(g, g->vertex_list[i], g->vertex_list[i]->nbh[j]);
			j=can_connect(g->vertex_list[i]);
		}
	}

	print_graph(g);
}

int can_connect(Vertex v){
	int i;

	for(i=0; i<v->n; i++){
		if(((Island)v->content)->color==((Island)v->nbh[i]->content)->color){
			return i;
		}
	}
	return -1;
}

void merge_islands(Graph g, Vertex a, Vertex b){
	int i;

	assert(((Island)a->content)->color == ((Island)b->content)->color);

	for(i=0; i<b->n; i++){
		if(!edge_exists(a, b->nbh[i])){
			create_edge(g, a, b->nbh[i]);
		}
	}

	for(i=0; i<g->n; i++){
		if(g->vertex_list[i]!=a && edge_exists(g->vertex_list[i], b) && !edge_exists(g->vertex_list[i], a)){
			create_edge(g, g->vertex_list[i], a);
		}
	}

	((Island)a->content)->size = ((Island)a->content)->size + ((Island)b->content)->size;

	destroy_vertex(g, b);

}

void print_graph(Graph g){
	int i,j;

	printf("\nGraph depth: %d\n", g->h);
	for(i=0; i<g->n; i++){
		printf("Island %d:\n\tDepth: %d\n\tSize: %d\n\tColor: %d\n\tNeighbors:\n", i, g->vertex_list[i]->depth, ((Island)g->vertex_list[i]->content)->size, ((Island)g->vertex_list[i]->content)->color);
		for(j=0; j<g->vertex_list[i]->n; j++){
			printf("\t\tDepth: %d\n\t\tSize: %d\n\t\tColor: %d\n", g->vertex_list[i]->nbh[j]->depth, ((Island)g->vertex_list[i]->nbh[j]->content)->size, ((Island)g->vertex_list[i]->nbh[j]->content)->color);
		}
	}
}

int test_matrix_size(Graph g){
	int i, sum=0;

	for(i=0; i<g->n; i++){
		sum += ((Island)g->vertex_list[i]->content)->size;
	}

	return sum;
}

Graph change_color(Graph g, int c){
	assert(c!=((Island)g->vertex_list[0]->content)->color);

	((Island)g->vertex_list[0]->content)->color = c;

	connect_game(g);

	return g;
}

bool game_over(Graph g){
	if(((Island)g->vertex_list[0]->content)->size==test_matrix_size(g)){
		destroy_graph(g);
		return true;
	}

	return false;
}







