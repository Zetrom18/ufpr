#include <stdio.h>
#include <stdlib.h>

typedef struct comp {
	int elem;
	int quant;
} comp;

typedef struct ponto {
	int prof;
	int x;
	int y;
} ponto;

int*** monta (int, int, int);
void profund (int ***,int, int, int);
void enumera(int ***, int, int, int, comp *);
void printswitch (int);
void plana (int ***, int, int, int);
void coord (int **, int *, int *, int, int);
void marca (int ***, int **, int, int, int, int, int, int);
int plana_cont (int **, int, int);
void maior_volume (comp *);
void troca (int, int);
void espessura (int ***, int, int, int);
void area (int ***, int, int, int);
int area_cont (int **, int, int);
void petr_conex (int ***, int, int, int);
void conexo (int ***, int, int, int, int ***, int, int, int, int *, int *, int *, int, int);
void cone_rec (int ***, int, int, int, int ***, int, int, int, int, int);
