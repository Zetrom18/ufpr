#include <stdio.h>
#include <stdlib.h>

main (){
	int ***m3, d1, d2, d3;
	int x, y, p, aux;
	int *vetor, **matriz;
	scanf("%d %d %d", &d1, &d2, &d3);
	m3= (int***) malloc(sizeof(int**)*d1);
	for (x=0;x<d1;x++){
		m3[x]= (int**) malloc(sizeof(int*)*d2);
		for (y=0;y<d2;y++)
			m3[x][y]= (int*) malloc(sizeof(int)*d3);
	}
	for (p=0;p<d3;p++)
		for (x=0;x<d1;x++)
			for (y=0;y<d2;y++){
				scanf("%d", &aux);
				m3[x][y][p]=aux;
			}
	for (p=0;p<d3;p++){
		for (x=0;x<d1;x++){
			for (y=0;y<d2;y++)
				printf("%d ", m3[x][y][p]);
			puts("");
		}
		puts("---------");
	}
}
