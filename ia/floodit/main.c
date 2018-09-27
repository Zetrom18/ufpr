#include "graph.h"
#include "floodit.h"

int main(int argc, char **argv){
//	if(DEBUG){
//		test_graph();
//	}

	int color;
	Graph game = read_file();

//	while(!game_over(game)){
//		scanf("%d", &color);
//		change_color(game, color);
//	}

	destroy_graph(game);

	puts("GAME OVER");

	return 0;
}