#include "graph.h"

#define TEST_SIZE (37)

void test_graph(){
    Graph g;
    int i;
    int j;

    g = create_graph(TEST_SIZE);

    assert(vertex_count(g) == TEST_SIZE);

    /* check it's empty */
    for(i = 0; i < TEST_SIZE; i++) {
        for(j = 0; j < TEST_SIZE; j++) {
            assert(edge_exists(g->vertex_list[i], g->vertex_list[j]) == 0);
        }
    }

    /* check edge count */
    assert(edge_count(g) == 0);

    /* fill in the diagonal */
    for(i = 0; i < TEST_SIZE; i++) {
        create_edge(g, g->vertex_list[i], g->vertex_list[i]);
    }

    /* check */
    assert(edge_count(g) == TEST_SIZE);

    for(i = 0; i < TEST_SIZE; i++) {
        for(j = 0; j < TEST_SIZE; j++) {
            assert(edge_exists(g->vertex_list[i], g->vertex_list[j]) == (i == j));
        }
    }

    /* fill in all the entries */
    for(i = 0; i < TEST_SIZE; i++) {
        for(j = 0; j < TEST_SIZE; j++) {
            if(i != j) create_edge(g, g->vertex_list[i], g->vertex_list[j]);
        }
    }

    /* test they are all there */
    assert(edge_count(g) == TEST_SIZE * TEST_SIZE);

    for(i = 0; i < TEST_SIZE; i++) {
        for(j = 0; j < TEST_SIZE; j++) {
            assert(edge_exists(g->vertex_list[i], g->vertex_list[j]) == 1);
        }
    }

    /* check removing first and last vertices */
    destroy_vertex(g, g->vertex_list[0]);
    destroy_vertex(g, g->vertex_list[vertex_count(g)-1]);

    /* test they are all there */
    assert(edge_count(g) == (TEST_SIZE -2) * (TEST_SIZE -2));

    for(i = 0; i < (TEST_SIZE -2); i++) {
        for(j = 0; j < (TEST_SIZE -2); j++) {
            assert(edge_exists(g->vertex_list[i], g->vertex_list[j]) == 1);
        }
    }

    /* free it */
    destroy_graph(g);

}
