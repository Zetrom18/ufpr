struct island {
	int size;
	int color;
};

typedef struct island* Island;

Graph read_file();

void connect_game(Graph g);

int can_connect(Vertex v);

void merge_islands(Graph g, Vertex a, Vertex b);

void print_graph(Graph g);

int test_matrix_size(Graph g);

Graph change_color(Graph g, int c);

bool game_over(Graph g);
