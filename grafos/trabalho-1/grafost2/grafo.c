#include <stdio.h>

#include <stdlib.h>
#include <graphviz/cgraph.h>
#include <string.h>

#include "grafo.h"

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

//------------------------------------------------------------------------------
// estrutura de dados para representar um grafo simples
//
// o grafo pode ser
// - direcionado ou não
// - com pesos nas arestas ou não
//
// além dos vértices e arestas, o grafo tem um nome
//
// os vértices do grafo também tem nome
//
// os nomes do grafo e dos vértices são strings quaisquer
//
// num grafo com pesos nas arestas todas as arestas tem peso, que é um double
//
// o peso default de uma aresta é 0.0

struct grafo {
  int grafo_direcionado;
  char *grafo_nome;
  int n_arestas;
  int n_vertices;
  struct vertice *grafo_vertices;
  struct aresta *grafo_arestas;
};

//------------------------------------------------------------------------------
// estrutura de dados para representar um vértice

struct vertice {
  char *vertice_nome;
  char *tipo_produtor_ou_consumidor;
  struct vertice *vertice_proximo;
};

//------------------------------------------------------------------------------
// estrutura de dados para representar uma aresta

struct aresta {
  double aresta_peso;
  struct vertice *aresta_origem, *aresta_destino;
  struct aresta *aresta_proximo;
};

//------------------------------------------------------------------------------
// encontra um vertice a partir do seu nome

struct vertice *encontra_vertice(struct vertice *vertices, const char *nome) {
  struct vertice *v;

  /* Percorre todos os vértices da estrutura */
  for(v = vertices; v != NULL; v = v->vertice_proximo) {
    /* Se o nome do vértice é igual ao desejado, então o retorna */
    if(strcmp(v->vertice_nome, nome) == 0) {
      return v;
    }
  }

  return NULL;
}

//------------------------------------------------------------------------------
// encontra uma aresta dados seus vertices em uma lista de arestas

struct aresta *encontra_aresta(struct aresta *arestas, int tamanho, struct vertice *cauda, struct vertice *cabeca) {
  struct aresta *a;
  int i;

  /* Percorre todas as arestas */
  for(i = 0, a = arestas; i < tamanho; ++i, a = a->aresta_proximo) {
    /* Se a origem e o destino forem iguais, então a retorna */
    if(a->aresta_origem == cauda && a->aresta_destino == cabeca) {
      return a;
    }
  }

  return NULL;
}

//------------------------------------------------------------------------------
// carrega os vertices de um grafo do tipo Agraph_t para um grafo do tipo
// da estrutura implementada

struct vertice *obter_vertices(Agraph_t *grafo) {
  Agnode_t *v;
  struct vertice *vertices = NULL;
  int n_vertices, i;

  /* Número de vértices do grafo */
  n_vertices = agnnodes(grafo);

  if(n_vertices > 0) {
    /* Aloca a quantidade de memória necessária para armazenar todos os vértices */
    vertices = (struct vertice *) malloc(sizeof(struct vertice) * n_vertices);

    if(vertices != NULL) {
      /* Percorre todos os vértices do grafo */
      for(i = 0, v = agfstnode(grafo); i < n_vertices; ++i, v = agnxtnode(grafo, v)) {
        /* Duplica na memória o nome do vértice e o atribui na estrutura.
           A duplicação é feita para evitar erros (por exemplo, se o espaço for desalocado) */
        vertices[i].vertice_nome = strdup(agnameof(v));
        vertices[i].tipo_produtor_ou_consumidor = agget(v, "tipo");

        /* Define o próximo vértice como o vértice do próximo bloco alocado,
           tirando proveito do fato de se terem alocados todos os vértices numa
           região contígua de memória (se essa é a última posição, o próximo é NULL) */
        vertices[i].vertice_proximo = (i + 1 < n_vertices) ? vertices + (i + 1) : (struct vertice *) NULL;
      }
    }
  }

  return vertices;
}

//------------------------------------------------------------------------------
// carrega as arestas de um grafo do tipo Agraph_t para um grafo do tipo
// da estrutura implementada

struct aresta *obter_arestas(Agraph_t *grafo, struct vertice *lista_vertices) {
  Agedge_t *a;
  Agnode_t *v;
  struct aresta *arestas = NULL;
  struct vertice *cauda, *cabeca;
  char *peso;
  int n_arestas, contador = 0;

  /* Número de arestas do grafo */
  n_arestas = agnedges(grafo);

  if(n_arestas > 0) {
    /* Aloca a quantidade de memória necessária para armazenar todas as arestas */
    arestas = (struct aresta *) malloc(sizeof(struct aresta) * n_arestas);

    if(arestas != NULL) {
      /* Percorre todas as arestas do grafo */
      for(v = agfstnode(grafo); v != NULL; v = agnxtnode(grafo, v)) {
        for(a = agfstedge(grafo, v); a != NULL && contador < n_arestas; a = agnxtedge(grafo, a, v)) {
          cauda = encontra_vertice(lista_vertices, agnameof(agtail(a)));
          cabeca = encontra_vertice(lista_vertices, agnameof(aghead(a)));

          /* Através da cauda e da cabeça, verifica se a aresta já foi
             adicionada na estrutura, se ainda não, então a adiciona */
          if(encontra_aresta(arestas, contador, cauda, cabeca) == NULL) {
            /* Obtêm o parâmetro peso da aresta */
            peso = agget(a, "peso");

            /* Define os vértices de origem e destino da aresta */
            arestas[contador].aresta_origem = cauda;
            arestas[contador].aresta_destino = cabeca;

            /* Se o peso está definido, então é convertido para o tipo double
               e definido na estrutura, caso contrário, é definido como 0.0 */
            arestas[contador].aresta_peso = (peso != NULL && *peso != '\0') ? atof(peso) : 0.0;

            /* Define a próxima aresta (idêntico ao modo como é feito com os vértices) */
            arestas[contador].aresta_proximo = (contador + 1 < n_arestas) ? arestas + (contador + 1) : (struct aresta *) NULL;

            /* Incrementa o contador de arestas */
            ++contador;
          }
        }
      }
    }
  }

  return arestas;
}

//------------------------------------------------------------------------------
// lê um grafo no formato dot de input, usando as rotinas de libcgraph
//
// desconsidera todos os atributos do grafo lido
// exceto o atributo "peso" nas arestas onde ocorra
//
// num grafo com pesos nas arestas todas as arestas tem peso, que é um double
//
// o peso default de uma aresta num grafo com pesos é 0.0
//
// devolve o grafo lido ou
//         NULL em caso de erro

grafo le_grafo(FILE *input) {
  Agraph_t *g;
  struct grafo *grafo_lido;

  /* Aloca a estrutura do grafo */
  grafo_lido = (struct grafo *) malloc(sizeof(struct grafo));

  if(grafo_lido != NULL) {
    /* Inicializa a estrutura do grafo */
    grafo_lido->grafo_nome = (char *) NULL;
    grafo_lido->grafo_vertices = (struct vertice *) NULL;
    grafo_lido->grafo_arestas = (struct aresta *) NULL;

    /* Armazena em g o grafo lido da entrada */
    if((g = agread(input, NULL)) == NULL) {
      destroi_grafo(grafo_lido);
      return NULL;
    }

    /* Carrega na estrutura os vértices de g */
    if((grafo_lido->grafo_vertices = obter_vertices(g)) == NULL) {
      agclose(g);
      destroi_grafo(grafo_lido);
      return NULL;
    }

    /* Carrega na estrutura as arestas de g */
    if((grafo_lido->grafo_arestas = obter_arestas(g, grafo_lido->grafo_vertices)) == NULL) {
      agclose(g);
      destroi_grafo(grafo_lido);
      return NULL;
    }

    /* Define o nome do grafo e se ele é direcionado */
    grafo_lido->grafo_direcionado = agisdirected(g);
    grafo_lido->grafo_nome = strdup(agnameof(g));
	grafo_lido->n_vertices = agnnodes(g);
	grafo_lido->n_arestas = agnedges(g);

    agclose(g);
  }

  return grafo_lido;
}

//------------------------------------------------------------------------------
// desaloca toda a memória utilizada em g
//
// devolve 1 em caso de sucesso ou
//         0 em caso de erro

int destroi_grafo(grafo g) {
  if(g != NULL) {
    /* Libera a região de memória ocupada pelo nome do grafo, se não for nula */
    if(g->grafo_nome != NULL) {
      free(g->grafo_nome);
    }

    /* Libera a região de memória ocupada pelos vértices do grafo, se não for nula */
    if(g->grafo_vertices != NULL) {
      struct vertice *v;

      /* Libera os nomes de todos os vértices */
      for(v = g->grafo_vertices; v != NULL; v = v->vertice_proximo) {
        if(v->vertice_nome != NULL) {
          free(v->vertice_nome);
        }
      }

      free(g->grafo_vertices);
    }

    /* Libera a região de memória ocupada pelas arestas do grafo, se não for nula */
    if(g->grafo_arestas != NULL) {
      free(g->grafo_arestas);
    }

    /* Libera a região de memória ocupada pela estrutura do grafo */
    free(g);
  }

  return 1;
}

//------------------------------------------------------------------------------
// escreve o grafo g em output usando o formato dot, de forma que
//
// 1. todos os vértices são escritos antes de todas as arestas/arcos
// 2. se uma aresta tem peso, este deve ser escrito como um atributo
//
// devolve o grafo escrito ou
//         NULL em caso de erro

grafo escreve_grafo(FILE *output, grafo g) {
  struct vertice *v;
  struct aresta *a;
  char caractere_aresta;

  /* Imprime na saida a definição do grafo, caso seja um grafo direcionado,
     é adicionado o prefixo "di" */
  fprintf(output, "strict %sgraph \"%s\" {\n\n", (g->grafo_direcionado) ? "di" : "", g->grafo_nome);

  /* Imprime os nomes dos vértices */
  for(v = g->grafo_vertices; v != NULL; v = v->vertice_proximo) {
    fprintf(output, "    \"%s\"\n", v->vertice_nome);
  }

  fprintf(output, "\n");

  /* Se o grafo é direcionado, representamos as arestas por v -> u,
     sendo v o vértice de origem e u o vértice de destino de cada aresta.
     Caso contrário, representamos as arestas por v -- u */
  caractere_aresta = (g->grafo_direcionado) ? '>' : '-';

  /* Imprime as arestas */
  for(a = g->grafo_arestas; a != NULL; a = a->aresta_proximo) {
    fprintf(output, "    \"%s\" -%c \"%s\" ", a->aresta_origem->vertice_nome, caractere_aresta, a->aresta_destino->vertice_nome);

    /* Se o peso for diferente de 0.0 (padrão), então ele é imprimido como um atributo */
    if(a->aresta_peso > 0.000000001 || a->aresta_peso < -0.000000001) {
      fprintf(output, "[peso=%.8f]", a->aresta_peso);
    }

    fprintf(output, "\n");
  }

  fprintf(output, "}\n");
  return g;
}

//------------------------------------------------------------------------------
// encontra um vertice a partir do seu nome

struct aresta *nosso_encontra_aresta(struct aresta *arestas, struct vertice *cauda, struct vertice *cabeca) {
  struct aresta *a;

  /* Percorre todas as arestas */
  for(a = arestas; a != NULL; a = a->aresta_proximo) {
    /* Se a origem e o destino forem iguais, então a retorna */
    if((a->aresta_origem == cauda && a->aresta_destino == cabeca) || (a->aresta_origem == cabeca && a->aresta_destino == cauda)) {
      return a;
    }
  }

  return NULL;
}


grafo copiaGrafo(grafo g1){
  struct grafo *g = (struct grafo *) malloc(sizeof(struct grafo));
    g->grafo_direcionado = g1->grafo_direcionado;
    g->n_arestas = g1->n_arestas;
    g->n_vertices = g1->n_vertices;
    g->grafo_nome = (char *)malloc(sizeof(g1->grafo_nome));
    strcpy(g->grafo_nome,"recomendacoes");
    g->grafo_vertices = (struct vertice *)malloc(sizeof(g1->grafo_vertices));
    g->grafo_vertices = g1->grafo_vertices;
    g->grafo_arestas = (struct aresta *)malloc(sizeof(g1->grafo_arestas));
    g->grafo_arestas = NULL;
    return g;
}


struct vertice* copiaVertice(struct vertice *v1){
  struct vertice *v = (struct vertice *) malloc(sizeof(struct vertice));
  v->vertice_nome = (char *) malloc(sizeof(v1->vertice_nome));
  strcpy(v->vertice_nome,v1->vertice_nome);
  v->tipo_produtor_ou_consumidor = (char *) malloc(sizeof(v1->tipo_produtor_ou_consumidor));
  strcpy(v->tipo_produtor_ou_consumidor,v1->tipo_produtor_ou_consumidor);
  v->vertice_proximo = (struct vertice *) malloc(sizeof(struct vertice));
  v->vertice_proximo = NULL;
  return v;
}


void imprimeVertices(struct vertice* vi){
  puts("\nImprime\n");
  for (struct vertice *v = vi;v != NULL;v = v->vertice_proximo){
    puts(v->vertice_nome);
  }
  puts("\nDone\n");
}


void imprimeArestas(struct aresta* ai){
  puts("\nImprime\n");
  for (struct aresta *a = ai;a != NULL;a = a->aresta_proximo){
    printf("%s -- %s\n",a->aresta_origem, a->aresta_destino);
  }
  puts("\nDone\n");
}


void recomendaP(struct grafo *g, struct vertice *c, struct vertice *pList){
  struct aresta *a;
  for (struct vertice *p = pList; p != NULL; p = p->vertice_proximo){
    if (nosso_encontra_aresta(g->grafo_arestas,c,p) != NULL){
      // Peso da aresta ++
      nosso_encontra_aresta(g->grafo_arestas,c,p)->aresta_peso++;
    }else{
      a = (struct aresta*) malloc(sizeof(struct aresta));
      a->aresta_peso = 1;
      a->aresta_origem = c;
      a->aresta_destino = p;
      a->aresta_proximo = g->grafo_arestas;
      g->grafo_arestas = a;
    }
  }

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
  struct vertice *c1;
  struct vertice *c2;
  struct vertice *p;
  struct vertice *recomenda = NULL;
  struct vertice *aux;
  struct aresta *a;
  char caractere_aresta;
  int intersecao = 0;
  int diferenca = 0;

  // Copia um grafo pro outro. Esqueci como faz isso em C. Deve ser o memcopy.
  struct grafo *g1 = copiaGrafo(g);
  // escreve_grafo(stdout, g);
  //escreve_grafo(stdout, g1);

  /* Se o grafo é direcionado, representamos as arestas por v -> u,
     sendo v o vértice de origem e u o vértice de destino de cada aresta.
     Caso contrário, representamos as arestas por v -- u */
  caractere_aresta = (g->grafo_direcionado) ? '>' : '-';


  /* Imprime os nomes dos vértices */
  for(c1 = g->grafo_vertices; c1 != NULL; c1 = c1->vertice_proximo) {
    if (strcmp(c1->tipo_produtor_ou_consumidor,"c") == 0) {
      // printf("\n c1: %s \n", c1->vertice_nome);
      for(c2 = g->grafo_vertices; c2 != NULL; c2 = c2->vertice_proximo) {
        if (c2 != c1 && strcmp(c2->tipo_produtor_ou_consumidor,"c") == 0) {
          // printf("\n c2: %s \n", c2->vertice_nome);
          for(p = g->grafo_vertices; p != NULL; p = p->vertice_proximo) {
            if (strcmp(p->tipo_produtor_ou_consumidor,"p") == 0) {
              if (nosso_encontra_aresta(g->grafo_arestas, c2, p) != NULL){
                if (nosso_encontra_aresta(g->grafo_arestas, c1, p) != NULL){
                  intersecao += 1;
                } else {
                  aux = (struct vertice*) malloc(sizeof(struct vertice));
                  aux = copiaVertice(p);
                  aux->vertice_proximo = recomenda;
                  recomenda = aux;
                  diferenca += 1;
                  // printf("Diferente: %s\n", aux->vertice_nome);
                  // imprimeVertices(recomenda);
                }
              }
            }
          }
          if (intersecao >= diferenca){
            recomendaP(g1,c1,recomenda);
          }
          recomenda = NULL;
          intersecao = 0;
          diferenca = 0;
        }
      }
    }

      // // Para cada vértice, temos que ver todas as arestas que ele não tem conexão..
      //  /* Imprime as arestas */
      // for(a = g->grafo_arestas; a != NULL; a = a->aresta_proximo) {
      // printf("    \"%s\" -%c \"%s\" ", a->aresta_origem->vertice_nome, caractere_aresta, a->aresta_destino->vertice_nome);

      // /* Se o peso for diferente de 0.0 (padrão), então ele é imprimido como um atributo */
      // if(a->aresta_peso > 0.000000001 || a->aresta_peso < -0.000000001) {
      //   printf("[peso=%.8f]", a->aresta_peso);
      // }


  }

  puts("");

  return g1;
}

//------------------------------------------------------------------------------
