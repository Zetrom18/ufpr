// ./mapa < mapa1.txt
// ./mapa < mapa2.txt

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// definicoes
#define TAM_MAX 1000

// protótipo de funcoes
void le_tamanhos(int *,int *, int *);
int*** inicializa_mapa(int, int, int);
void imprime_mapa(int ***, int, int, int);
void libera_mapa(int ***, int, int);

// recebe mapa, seus limites, o tipo e uma profundidade
// retorna area de composto tipo nesta profundidade
//int area(int ***mapa, int tx, int ty, int tp, int t, int p); 

int main(int argc, char *argv[])
{
   int ***img=NULL;
   int tx,ty,tp; // armazena tamanho do mapa

   le_tamanhos(&tx,&ty,&tp);
   img = inicializa_mapa(tx,ty,tp);
   if (img == NULL)
   {
      printf("Erro!\n");
      return -1;
   }
   imprime_mapa(img,tx,ty,tp);
   libera_mapa(img,tx,ty);
  
   return 0;
}

void le_tamanhos(int *x,int *y, int *p)
{
   scanf("%d %d %d",x,y,p);
}

int*** inicializa_mapa(int tx, int ty, int tp)
{

   int ***img;
   int x,y,p; // contadores 3D

   img=(int ***) malloc(sizeof(int **)*tx);
   if (img == NULL)
   {
      printf("Erro no malloc funcao inicializa!\n");
      return NULL;
   }

   for (x=0;x<tx;x++)
    img[x]=(int **) malloc(sizeof(int *)*ty);

   for (x=0;x<tx;x++)
     for (y=0;y<ty;y++)
       img[x][y]=(int *) malloc(sizeof(int)*tp);

   for (p=0;p<tp;p++)
    for (x=0;x<tx;x++)
     for (y=0;y<ty;y++)
      scanf("%d", &img[x][y][p]);

   return (img);
}

void imprime_mapa(int ***img, int tx, int ty, int tp)
{
   int x,y,p; // contadores 3D

   printf("Imprimindo mapa[%d][%d][%d]\n", tx,ty,tp);
   for (p=0;p<tp;p++){
    printf("profundidade %d:\n",p);
    for (x=0;x<tx;x++){
     for (y=0;y<ty;y++){
        printf("%d ", img[x][y][p]);
     }
     printf("\n");
    }
   }
}

void libera_mapa(int ***img, int tx, int ty)
{
   int x,y; // contadores 3D

   for (x=0;x<tx;x++)
     for (y=0;y<ty;y++)
       free(img[x][y]);

   for (x=0;x<tx;x++)
    free(img[x]);

   free(img);
}
