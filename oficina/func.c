#include "matriz.h"

int*** monta (int d1,int d2,int d3){
	int ***m3;
	int x, y, p;
	m3= (int***) malloc(sizeof(int**)*d1);
	if (!m3){
		puts("erro ao alocar");
		return NULL;
	}
	for (x=0;x<d1;x++){
		m3[x]= (int**) malloc(sizeof(int*)*d2);
		if (!m3[x]){
			puts("erro ao alocar");
			return NULL;
		}
	}
	for (x=0;x<d1;x++)
		for (y=0;y<d2;y++){
			m3[x][y]= (int*) malloc(sizeof(int)*d3);
			if (!m3[x][y]){
				puts("erro ao alocar");
				return NULL;
			}
		}
	for (p=0;p<d3;p++)
		for (x=0;x<d1;x++)
			for (y=0;y<d2;y++)
				scanf("%d", &m3[x][y][p]);
	return (m3);
}

///////////////////////////////////////////Questão 1/////////////////////////////////////////////

void profund (int ***m3,int d1,int d2,int d3){
	int aux,i,j;
	ponto q;
	q.prof=-1;
	for (i=0;i<d1;i++)
		for (j=0;j<d2;j++)
			for (aux=0;aux<d3;aux++)
				if (m3[i][j][aux]!=0){
					if (q.prof<aux){
						q.prof=aux-1;
						q.x=i;
						q.y=j;
					}
					aux=d3;
				}
	if (q.prof==-1)
		printf("Área explorada de %d Km² é puramente água.\n", d1*d2);
	else
		printf("Área explorada de %d Km² com maior profundidade na coordenada: %d x %d\n", d1*d2, q.x, q.y);
}

///////////////////////////////////////////Questão 2/////////////////////////////////////////////

void enumera(int ***m3,int d1,int d2, int d3,comp *v1){
	int i,j,k;
	int aux,boo=0;
	for (aux=0;aux<255;aux++){
		v1[aux].elem=0;
		v1[aux].quant=0;
	}
	for (i=0;i<d1;i++)
		for (j=0;j<d2;j++)
			for (k=0;k<d3;k++)
				if (m3[i][j][k]!=0){
					for (aux=0;v1[aux].elem!=0;aux++)
						if (m3[i][j][k]==v1[aux].elem){
							v1[aux].quant++;
							boo=1;
							aux=254;
						}
					if (boo==0){
						v1[aux].elem=m3[i][j][k];
						v1[aux].quant=1;
					}
					boo=0;
				}
	for (aux=0;v1[aux].elem!=0;aux++);
	printf("Compostos distintos identificados: %d (", aux);
	for (boo=0;boo<aux-2;boo++){
		printswitch(v1[boo].elem);
		printf(", ");
	}
	printswitch(v1[boo].elem);
	printf(" e ");
	printswitch(v1[boo+1].elem);
	printf(")\n");
}

void printswitch (int x){
	switch (x){
	case 1:
		printf("gás-natural");
		break;
	case 2:
		printf("petróleo");
		break;
	case 3:
		printf("carvão");
		break;
	case 4:
		printf("xisto");
		break;
	case 5:
		printf("rocha");
		break;
	case 6:
		printf("urânio");
		break;
	case 7:
		printf("sílica");
		break;
	case 8:
		printf("ouro");
		break;
	case 9:
		printf("diamante");
		break;
	case 10:
		printf("cristal");
		break;
	default:
		printf("composto desconhecido");
		break;
	}
}

///////////////////////////////////////////Questão 3/////////////////////////////////////////////

void plana (int ***m3,int d1,int d2, int d3){
	int x,y,p;
	int xi,yj,aux;
	int tam=0,i=0,j=0;
	int **m2;
	m2= (int **) malloc(sizeof(int *)*d1);
	if (!m2){
		puts("erro ao alocar");
		return;
	}
	for (x=0;x<d1;x++)
		m2[x]= (int *) malloc(sizeof(int)*d2);
		if (!m2[x]){
			puts("erro ao alocar");
			return;
		}
	for (x=0;x<d1;x++)
		for (y=0;y<d2;y++)
			for (p=0;p<d3;p++){
				for (xi=0;xi<d1;xi++)
					for (yj=0;yj<d2;yj++)
						m2[xi][yj]=0;
				marca(m3,m2,x,y,p,d1,d2,d3);
				aux=plana_cont(m2,d1,d2);
				if (aux>tam){
					tam=aux;
					coord(m2,&i,&j,d1,d2);
				}
			}
	printf("Maior área plana do mar: %d km² (coordenadas centrais %d x %d)\n", tam, i, j);
	for (x=0;x<d1;x++)
		free(m2[x]);
	free(m2);
	return;
}

void coord (int **m2,int *x,int *y,int d1,int d2){
	int a,b;
	int xi=d1,xf=0;
	int yi=d2,yf=0;
	for (a=0;a<d1;a++)
		for (b=0;b<d2;b++){
			if ((xi>a)&&(m2[a][b]==1))
				xi=a;
			if ((xf<a)&&(m2[a][b]==1))
				xf=a;
			if ((yi>b)&&(m2[a][b]==1))
				yi=b;
			if ((yf<b)&&(m2[a][b]==1))
				yf=b;
		}
	*x=(xi+xf)/2;
	*y=(yi+yf)/2;
	return;
}

void marca (int ***m3,int **m2,int a,int b,int c,int d1,int d2,int d3){
	if ((a==d1)||(b==d2)||(c==d3))
		return;
	if ((m3[a][b][c]==0)||(m3[a][b][c-1]!=0))
		return;
	m2[a][b]=1;
	if ((a-1>0)&&(m2[a-1][b]!=1))
		marca(m3,m2,(a-1),b,c,d1,d2,d3);
	if ((b-1>0)&&(m2[a][b-1]!=1))
		marca(m3,m2,a,(b-1),c,d1,d2,d3);
	if ((a+1<d1)&&(m2[a+1][b]!=1))
		marca(m3,m2,(a+1),b,c,d1,d2,d3);
	if ((b+1<d2)&&(m2[a][b+1]!=1))
		marca(m3,m2,a,(b+1),c,d1,d2,d3);
	return;
}

int plana_cont (int **m2,int d1,int d2){
	int a,b,aux=0;
	for (a=0;a<d1;a++)
		for (b=0;b<d2;b++)
			if (m2[a][b]==1)
				aux++;
	return (aux);
}

///////////////////////////////////////////Questão 4/////////////////////////////////////////////

void maior_volume (comp *v1){
	int aux;
	for (aux=0;v1[aux].elem!=0;aux++){
		if (v1[aux].quant>v1[0].quant){
			troca(v1[aux].elem,v1[0].elem);
			troca(v1[aux].quant,v1[0].quant);
		}
		else if (v1[aux].quant>v1[1].quant){
			troca(v1[aux].elem,v1[1].elem);
			troca(v1[aux].quant,v1[1].quant);
		}
		else if (v1[aux].quant>v1[2].quant){
			troca(v1[aux].elem,v1[2].elem);
			troca(v1[aux].quant,v1[2].quant);
		}
	}
	if (aux==0){
		puts("Área explorada é puramente água.");
		return;
	}
	if (aux==1){
		printf("Apenas um composto foi encontrado: ");
		printswitch(v1[0].elem);
		puts("");
		return;
	}
	if (aux==2){
		troca(v1[0].elem,v1[1].elem);
		troca(v1[0].quant,v1[1].quant);

		printf("Os 2 compostos encontrados em ordem crescente: ");
		printswitch(v1[0].elem);
		printf(" e ");
		printswitch(v1[1].elem);
		puts("");
		return;
	}
	troca(v1[0].elem,v1[2].elem);
	troca(v1[0].quant,v1[2].quant);
	printf("Os 3 compostos com maior volume em ordem crescente: ");
	printswitch(v1[0].elem);
	printf(", ");
	printswitch(v1[1].elem);
	printf(" e ");
	printswitch(v1[2].elem);
	puts("");
	return;
}

void troca (int a,int b){
	int aux;
	aux=a;
	a=b;
	b=aux;
	return;
}

///////////////////////////////////////////Questão 5/////////////////////////////////////////////

void espessura (int ***m3,int d1,int d2,int d3){
	int aux=0;
	int a,b,c;
	ponto q;
	q.prof=0;
	for (a=0;a<d1;a++)
		for (b=0;b<d2;b++)
			for (c=0;c<d3;c++)
				if (m3[a][b][c]==2){
					for (;m3[a][b][c]==2;c++)
						aux++;
					if (q.prof<aux){
						q.x=a;
						q.y=b;
						q.prof=aux;
					}
					aux=0;
				}
	printf("Coordenada com a maior espessura de uma camada contínua de petróleo: %d x %d com %d000 metros\n", q.x, q.y, q.prof);
}

///////////////////////////////////////////Questão 6/////////////////////////////////////////////

void area (int ***m3,int d1,int d2,int d3){
	int aux,deep,a=0;
	int x,y,p;
	int **m2;
	m2= (int **) malloc(sizeof(int *)*d1);
	if (!m2){
		puts("erro ao alocar");
		return;
	}
	for (x=0;x<d1;x++)
		m2[x]= (int *) malloc(sizeof(int)*d2);
		if (!m2[x]){
			puts("erro ao alocar");
			return;
		}
	for (p=0;p<d3;p++){
		for (x=0;x<d1;x++)
			for (y=0;y<d2;y++)
				m2[x][y]=0;
		for (x=0;x<d1;x++)
			for (y=0;y<d2;y++)
				if (m3[x][y][p]==2)
					m2[x][y]=1;
		aux=area_cont(m2,d1,d2);
		if (a<aux){
			a=aux;
			deep=p;
		}
	}
	printf("Profundidade com maior área conexa de petróleo: %d000 metros\n", deep);
	for (x=0;x<d1;x++)
		free(m2[x]);
	free(m2);
	return;
}

int area_cont (int **m2,int d1,int d2){
	int cont=0;
	int a,b;
	for (a=0;a<d1;a++)
		if (m2[a][0]==1)
			cont++;
	for (b=1;b<d2;b++)
		if (m2[0][b]==1)
			cont++;
	for (a=1;a<d1;a++)
		for (b=1;b<d2;b++)
			if (((m2[a-1][b]==1)||(m2[a][b-1]==1))&&(m2[a][b]==1))
				cont++;
	return (cont);
}

/////////////////////////////////////Questão 7 e 8///////////////////////////////////////////////

void petr_conex (int ***m3,int d1,int d2,int d3){
	ponto q,aux;
	int tinta=1;
	int a,b,c;
	int x,y,p;
	int ***maux=NULL;
	aux.x=0;
	aux.y=0;
	aux.prof=0;
	maux=monta(d1,d2,d3);
	for (a=0;a<d1;a++)
		for (b=0;b<d2;b++)
			for (c=0;c<d3;c++)
				maux[a][b][c]=0;
	for (a=0;a<d1;a++)
		for (b=0;b<d2;b++)
			for (c=0;c<d3;c++)
				if (m3[a][b][c]==2){
					conexo(m3,d1,d2,d3,maux,a,b,c,&aux.x,&aux.y,&aux.prof,tinta,2);
					tinta++;
					if (aux.prof>q.prof){
						q.x=aux.x;
						q.y=aux.y;
						q.prof=aux.prof;
					}
					aux.x=0;
					aux.y=0;
					aux.prof=0;
				}
	for (a=0;a<d1;a++)
		for (b=0;b<d2;b++)
			for (c=0;c<d3;c++)
				if (m3[a][b][c]==2)
					aux.prof++;
	q.prof=aux.prof;
	printf("Maior volume de petróleo em região conexa: %d000 metros cúbicos\n", q.prof);
	printf("Coordenada %d x %d tem a maior espessura da região conexa de petróleo com %d000 metros cúbicos\n", q.x, q.y, q.prof);
	for (x=0;x<d1;x++)
		for (y=0;y<d2;y++)
			free(maux[x][y]);
	for (x=0;x<d1;x++)
		free(maux[x]);
	free(maux);
}

void conexo (int ***m3,int d1,int d2,int d3,int ***maux,int a,int b,int c,int *i,int *j,int *k,int tinta,int cops){
	int deep=0;
	int x,y,z;
	ponto aux;
	aux.prof=0;
	cone_rec(m3,d1,d2,d3,maux,a,b,c,tinta,cops);
	for (x=a;x<d1;x++)
		for (y=b;y<d2;y++){
			for (z=c;z<d3;z++)
				if (maux[x][y][z]==tinta)
					deep++;
			if (deep>aux.prof){
				aux.x=x;
				aux.y=y;
				aux.prof=deep;
			}
		}
	*i=aux.x;
	*j=aux.y;
	*k=aux.prof;
}

void cone_rec (int ***m3,int d1,int d2,int d3,int ***maux,int a,int b,int c,int tinta,int cops){
	int i;
	int dx[6]={0,0,0,1,0,-1};
	int dy[6]={0,0,1,0,-1,0};
	int dz[6]={1,-1,0,0,0,0};
	if((a<0)||(b<0)||(c<0)||(a>=d1)||(b>=d2)||(c>=d3))
		return;
	if((m3[a][b][c]!=cops)||(maux[a][b][c]==tinta))
		return;
	maux[a][b][c]=tinta;
	for (i=0;i<6;i++)
		cone_rec(m3,d1,d2,d3,maux,a+dx[i],b+dy[i],c+dz[i],tinta,cops);
}

///////////////////////////////////////////Questão 9/////////////////////////////////////////////

void maior_vol (int ***m3,int d1,int d2,int d3,comp *v1){
	int i,j,aux=0,xua=0;
	int lixo1,lixo2,lixo3,tinta=1;
	int a,b,c;
	int ***maux=NULL;
	maux=monta(d1,d2,d3);
	for (c=0;c<d3;c++)
		for (a=0;a<d1;a++)
			for (b=0;b<d2;b++)
				maux[a][b][c]=0;
	for (i=0;v1[i].elem!=0;i++){
		for (c=0;c<d3;c++)
			for (a=0;a<d1;a++)
				for (b=0;b<d2;b++){
					conexo(m3,d1,d2,d3,maux,a,b,c,&lixo1,&lixo2,&lixo3,tinta,v1[i].elem);
					tinta++;
					if(lixo3>xua)
						xua=lixo3;
					lixo3=0;
				}
		if(xua>aux){
			aux=xua;
			j=i;
		}
	}
	printf("Dentre os %d compostos encontrados na área, ", i);
	printswitch(v1[j].elem);
	puts(" é o composto que tem o maior volume conexo.");
	for (a=0;a<d1;a++)
		for (b=0;b<d2;b++)
			free(maux[a][b]);
	for (a=0;a<d1;a++)
		free(maux[a]);
	free(maux);
}
