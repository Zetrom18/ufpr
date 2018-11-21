#include "matriz.h"

int main(){
	int ***m=NULL;
	int x, y, p;
	int a, b, c;
	comp v[255];
	scanf("%d %d %d", &x, &y, &p);
	m=monta(x,y,p);
	if (!m)
		return;
	profund(m,x,y,p);			//questao 1
	enumera(m,x,y,p,v);		//questao 2
	plana(m,x,y,p);				//questao 3
	maior_volume(v);			//questao 4
	espessura(m,x,y,p);		//questao 5
	area(m,x,y,p);				//questao 6
	petr_conex(m,x,y,p);	//questao 7 e 8
	maior_vol(m,x,y,p,v);	//questao 9
}
