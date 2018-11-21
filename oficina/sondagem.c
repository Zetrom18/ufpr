#include<stdio.h>
#include<stdlib.h>

// recebe por redirecionamento: ./sondagem < mapa.txt 
// aloca, le, analisa e imprime dados 3D

// para passagem do arquivo por parâmetro: ./sondagem mapa.txt
// int main(int argc, char *argv[])

int main()
{
   int ***sonda;   // dados em 3D tipo int 
   int tx,ty,tp;  // armazenar limites da sondagem
   int x,y,p;     // contadores para deslocamentos
   
   scanf("%d %d %d",&tx,&ty,&tp); // leitura os limites
 
   sonda=(int ***) malloc(sizeof(int **)*tx);  // aloca array para limite em X

   if (sonda == NULL)
   {
     printf("Erro1: limite incorreto ou muito elevado para sondagem\n");
     printf("Verifique formato do arq.txt ou use-o como parâmetro para o programa\n");
     printf("Para sondagens com alta resolucao ou profundidade use: fopen/fread/fseek no arq.txt\n");
     return -1;
   }

   // aloca array 2D de apontadores para sondagem em [X][Y]
   for (x=0;x<tx;x++)
    sonda[x]=(int **) malloc(sizeof(int *)*ty);

   // aloca array 3D para sondagem em [X][Y][P]
   for (x=0;x<tx;x++)
     for (y=0;y<ty;y++)
       sonda[x][y]=(int *) malloc(sizeof(int)*tp);

   // leitura dos dados
   for (p=0;p<tp;p++)
    for (x=0;x<tx;x++)
     for (y=0;y<ty;y++)
      scanf("%d", &sonda[x][y][p]);

   // separa area de sondagem em profundidades e imprime
   printf("Imprimindo sondagem[%d][%d][%d]\n", tx,ty,tp);
   for (p=0;p<tp;p++){
    printf("profundidade %d:\n",p);
    for (x=0;x<tx;x++){
     for (y=0;y<ty;y++){
        printf("%d ", sonda[x][y][p]);
     }
     printf("\n");
    }
   }

   // libera memoria do array 3D
   for (x=0;x<tx;x++)
     for (y=0;y<ty;y++)
       free(sonda[x][y]);
   for (x=0;x<tx;x++)
    free(sonda[x]);
   free(sonda);
   
   return 0;
}
