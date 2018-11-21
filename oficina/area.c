// ./area < area.txt

#include <stdio.h>

#define N 5 // define area do mapa
#define compostoT 1 // composto para busca
#define compostoP 2 // marcador para preenchimentos conexos
 
int mapa[N][N];
int dx[4]={0,1,0,-1}; // deslocamento em X
int dy[4]={1,0,-1,0}; // deslocamento em Y

// preenchimento por flooding
// recebe coordenada e marcador
void conexo(int, int, int);

int main ()
{
   int x,y;
   int area=0;
   int c = compostoP;  // marcador inicializado
   
   for(x=0;x<N;x++)
     for(y=0;y<N;y++)
        scanf("%d",&mapa[x][y]);
 
   for(x=0;x<N;x++)
     for(y=0;y<N;y++)
        if(mapa[x][y] == compostoT){
           conexo(x,y,c); // preenche area conexa com marcador
           c++; // altera marcador para preencher area desconexas
   }

   for(x=0;x<N;x++)
     for(y=0;y<N;y++)
        if(mapa[x][y] == compostoP)
          area++;

    printf("area superior no mapa com composto tipo 1 = %d\n", area);
    return 0;
}

void conexo(int x, int y, int nt)
{
    // verifica se a busca esta dentro dos limites do mapa
    if(x < 0 || y < 0 || x >= N || y >= N)
      return;

    // durante a busca recursiva ignora os nao compostosT  
    if(mapa[x][y] != compostoT) 
      return;

    // preenche area conexa de compostoT por compostoP 
    mapa[x][y] = nt;
   
    // para verificar caminho de preenchimento
    //    printf("[%d][%d] marcado com %d\n",x,y,nt);

    // busca recursiva com deslocamentos: dir,baixo,esq,cima
    for (int i=0; i<4; i++)
      conexo(x+dx[i],y+dy[i],nt); 
}
