#include <stdio.h>

#include <stdlib.h>
#include <graphviz/cgraph.h>
#include <string.h>

#include "grafo.h"
#include "lista.h"

//------------------------------------------------------------------------------
// (apontador para) estrutura de dados para representar um grafo
// 
// o grafo pode ser direcionado ou não
// 
// o grafo tem um nome, que é uma "string"

//struct grafo {};

//------------------------------------------------------------------------------
// desaloca toda a memória usada em *g
// 
// devolve 1 em caso de sucesso,
//         ou 
//         0, caso contrário


//	A estrutura do grafo armazena as listas de vértices e arestas, e as propriedades nome, direcionado e ponderado.
struct grafo
{
    lista vertices;		//lista de vertices do grafo
    int direcionado;	//define se o grafo é ou não direcionado
    lista arestas;		//lista de arestas do grafo
    char *nome;			//nome do grafo
    int ponderado;		//define se o grafo é ou não ponderado
};

//	A estrutura vertice armazena as informações de um vértice do grafo, tais como nome e graus.

typedef struct vertice *vertice;

struct vertice
{
    char *nome;					//nome do vertice
    unsigned int grau_saida;	//grau de saida do vertice (Arcos com tail apontando para este vertice)
    unsigned int grau_entrada;	//grau de entrada do vertice (Arcos com head apontado para este vertice)
    lista vizinhanca_entrada;	//lista de arestas de entrada
    unsigned int grau;			//grau do vertice
    lista vizinhanca_saida;		//lista de arestas de saida
};

//	A estrutura aresta armazena nome dos vértices das pontas, direção e peso
typedef struct aresta *aresta;

struct aresta
{
    vertice head, tail;	//apontadores para os vertices das pontas
    long int peso;		//string que define o peso de uma aresta
    int eh_arco;		//define se a aresta em questão é ou não um arco (direcionada)
};

//	Funções gerais para obter informações das estruturas de dados.

int destroi_aresta(void *p)
{
    aresta a = p;
    free(a);
    return 1;
}


int destroi_vertice(void *p)
{
    vertice v = p;
    destroi_lista(v->vizinhanca_entrada, NULL);
    destroi_lista(v->vizinhanca_saida, NULL);
    free(v->nome);
    free(v);
    return 1;
}

//retorna o nome de um grafo ou NULL
char *nome_grafo(grafo g)
{
    if (g) return g->nome;
    return NULL;
}
//retorna se o grafo é direcionado ou 0 caso o grafo não exista
int direcionado(grafo g)
{
    if (g) return g->direcionado;
    return 0;
}
//retorna se o grafo é ponderado ou 0 caso o grafo não exista
int ponderado(grafo g)
{
    if (g) return g->ponderado;
    return 0;
}
//retorna o nome do vertice ou NULL caso o vertice não exista.
char *nome_vertice(vertice v)
{
    if (v) return v->nome;
    return NULL;
}


int destroi_grafo(grafo g) {
    grafo h = g;
    if (!destroi_lista(h->vertices, destroi_vertice))
    {
        printf("Falha ao remover os elementos da lista de vértices");
        return 0;
    }
    if (!destroi_lista(h->arestas, destroi_aresta))
    {
        printf("Falha ao remover os elementos da lista de arestas");
        return 0;
    }
    free(h->nome);
    free(h);
    return 1;
}

//	Busca um vertice pelo nome, na lista de vertices de um grafo. Caso não encontre retorna NULL.
vertice busca_vertice(grafo g, char* nome)
{
    vertice v;
    for (no n=primeiro_no(g->vertices); n; n=proximo_no(n))
    {
        v = conteudo(n);
        if (!strcmp(v->nome, nome))
            return v;
    }
    return NULL;
}

//	Verifica se uma aresta existe na lista de vertices de um grafo, comparando todo o conteudo.
int busca_aresta(grafo g, aresta a)
{
    aresta x;
    int i=1;
    for (no n=primeiro_no(g->arestas); n; n=proximo_no(n), ++i)
    {
        x = conteudo(n);
        if (x->head == a->head && x->tail == a->tail)
            return i;
    }
    return 0;
}

//	Insere uma nova aresta na lista de arestas de um grafo.
void insere_aresta(grafo g, Agedge_t *a)
{
    aresta x = malloc(sizeof(struct aresta));
    char *peso = agget(a, (char *)"peso");

    if (peso==NULL || peso[0]=='\0')
        x->peso=0;
    else x->peso = atol(peso);

    if (g->direcionado)
        x->eh_arco = 1;

    x->head = busca_vertice(g, agnameof( aghead(a) ));
    x->tail = busca_vertice(g, agnameof( agtail(a) ));

    if (x->head==NULL || x->tail==NULL)
    {
        printf("Uma das pontas de uma aresta e nula.");
        free(x);
        return;
    }

    //insere na lista de arestas do vertice a referencia para a aresta criada.
    if (!direcionado(g))
    {
        //caso o grafo não seja direcionado, a aresta será colocada na lista de vizinhança de saída dos vértices
        insere_lista(x, x->head->vizinhanca_saida);
        insere_lista(x, x->tail->vizinhanca_saida);
    }
    else
    {
        insere_lista(x,x->tail->vizinhanca_saida);
        insere_lista(x,x->head->vizinhanca_entrada);
    }

    if (!busca_aresta(g, x))
        insere_lista(x,g->arestas);
    else free(x);
}

//------------------------------------------------------------------------------
// lê um grafo no formato dot de input
// 
// devolve o grafo lido,
//         ou 
//         NULL, em caso de erro 


//	Recria a estrutura de grafo conforme a especificação a partir de um grafo da libcgraph.
grafo le_grafo(FILE *input)
{
    //Abre o grafo do formato da libcgraph.
    Agraph_t *g = agread(input, NULL);
    //Aloca espaço para a estrutura do grafo.
    grafo h = (grafo)malloc(sizeof(struct grafo));
    //Um apontador de vertice auxiliar.
    vertice x;

    //Caso o grafo g não exista, retorna NULL.
    if ( !g )
        return NULL;

    //Obtém o nome do grafo
    char *nomeg = agnameof(g);
    h->nome = (char*)malloc(sizeof(char)*strlen(nomeg)+1);
    strcpy(h->nome,nomeg);
    //Obtém se o grafo é direcionado ou não
    h->direcionado = agisdirected(g);
    //Inicialmente define o grafo como não ponderado.
    h->ponderado = 0;
    //Cria uma lista para os vértices e uma lista para as arestas.
    h->vertices = constroi_lista();
    h->arestas = constroi_lista();

    //Preenche a lista de vertices
    for (Agnode_t *v=agfstnode(g); v; v=agnxtnode(g,v))
    {
        //cria um vertice novo, e copia o nome
        x = (vertice)malloc(sizeof(struct vertice));
        x->nome = (char*)malloc(sizeof(char)*strlen(agnameof(v))+1);
        strcpy(x->nome,agnameof(v));
        //Inicializa as listas de arestas do vértice.
        x->vizinhanca_saida = constroi_lista();
        x->vizinhanca_entrada = constroi_lista();

        //Obtém os graus do vértice
        x->grau = (unsigned int) agdegree(g,v,TRUE,TRUE);	//grau geral (entrada+saida)

        //Se o grafo for direcionado, o vértice tem graus de entrada e saída.
        if (direcionado(h))
        {
            x->grau_saida = (unsigned int) agdegree(g,v,FALSE,TRUE); //grau saida
            x->grau_entrada = (unsigned int) agdegree(g,v,TRUE,FALSE);//grau entrada
        }

        //Insere o novo vertice x na lista de vertices do grafo h.
        if (insere_lista(x,h->vertices)==NULL)
        {
            //em caso de falha de inserção, retorna NULL.
            printf("Falha ao inserir um vertice na lista.");
            return NULL;
        }
    }

    //para cada vértice, busca as arestas que estão conectadas nele, e tenta inserir na lista de arestas do grafo, evitando repetições.
    for (Agnode_t *v=agfstnode(g); v; v=agnxtnode(g,v))
    {
        //Obtém as arestas que estão conectadas ao vértice e as insere diretamente no grafo h.
        for (Agedge_t *a=agfstout(g,v); a; a=agnxtout(g,a))
        {
            //se o grafo não for ponderado porém uma aresta qualquer tiver peso, o grafo é ponderado.
            if (!h->ponderado && agget(a,(char *)"peso")!=NULL)
                h->ponderado = 1;
            insere_aresta(h,a);
        }
    }

    //fecha o grafo g da libcgraph e retorna o novo grafo h, conforme a estrutura especificada.
    agclose(g);
    return h;
}
//------------------------------------------------------------------------------
// escreve o grafo g em output usando o formato dot.
//
// devolve o grafo escrito,
//         ou 
//         NULL, em caso de erro 

grafo escreve_grafo(FILE *output, grafo g) {
    //vertice e arestas auxiliares
    vertice x;
    aresta y;
    //direcionado ou aresta normal
    char rep_aresta = direcionado(g) ? '>' : '-';

    //caso g não exista, retorna NULL pois um erro ocorreu.
    if (g==NULL)
        return g;

    //escreve o header:
    fprintf(output,"strict %sgraph \"%s\" {\n\n", direcionado(g) ? "di" : "", nome_grafo(g));

    //escreve os vértices:
    for (no n=primeiro_no(g->vertices); n; n=proximo_no(n))
    {
        x = conteudo(n);
        fprintf(output, "    \"%s\"  %d\n", nome_vertice(x), x->grau);
    }
    fprintf(output, "\n");

    //escreve as arestas:
    for (no n=primeiro_no(g->arestas); n; n=proximo_no(n))
    {
        y = conteudo(n);
        printf("    \"%s\" -%c \"%s\"", nome_vertice(y->tail), rep_aresta, nome_vertice(y->head));

        if ( ponderado(g))
            printf(" [peso=%ld]", y->peso);

        printf("\n");
    }

    fprintf(output, "\n}\n");
    return g;
}
//------------------------------------------------------------------------------
// devolve o grafo de recomendações de g
//
// cada aresta {c,p} de H representa uma recomendação do produto p
// para o consumidor c, e tem um atributo "weight" que é um inteiro
// representando a intensidade da recomendação do produto p para o
// consumidor c.
//
// cada vértice de g tem um atributo "tipo" cujo valor é 'c' ou 'p',
// conforme o vértice seja consumidor ou produto, respectivamente

grafo recomendacoes(grafo g){

  return g;
}

//------------------------------------------------------------------------------
