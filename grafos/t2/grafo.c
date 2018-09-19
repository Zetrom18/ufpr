#include <stdio.h>

#include <graphviz/cgraph.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "grafo.h"

// ---
// estrutura de dados para representar um grafo
// atributos: número de arestas, número de vértices, apontador para o vértice inicial, apontador para aresta inicial e verifica se ele é direcionado

struct grafo {
    int grafo_direcionado;
    int n_arestas;
    int n_vertices;
    char *grafo_nome;
    struct vertice *grafo_vertices;
    struct aresta *grafo_arestas;
};

// ---
// estrutura de dados para representar um vértice
// atributos: nome do vértice, tipo (p ou c), e um apontador para o próximo vértice

struct vertice {
    char *vertice_nome;
    char *tipo_produtor_ou_consumidor;
    int label;
    int cor;
    struct vertice *vertice_proximo;
    struct vertice **adjacencia;
};

// ---
// estrutura de dados para representar uma aresta
// atributos: peso da aresta (se houver), vértice de origem e destino, e próxima aresta

struct aresta {
    int aresta_peso;
    struct vertice *aresta_origem, *aresta_destino;
    struct aresta *aresta_proximo;
};

// ---
// Funções de protótipo

grafo copiaGrafo(grafo novo_grafo);
struct vertice* copiaVertice(struct vertice *v1);
struct vertice *encontra_vertice(struct vertice *vertices, const char *nome);
struct vertice *obter_vertices(Agraph_t *grafo);
struct aresta *obter_arestas(Agraph_t *grafo, struct vertice *lista_vertices);
struct aresta *encontra_aresta_ponteiros(struct aresta *arestas, struct vertice *cauda, struct vertice *cabeca);
struct aresta *encontra_aresta_por_nome(struct aresta *arestas, struct vertice *cauda, struct vertice *cabeca);
struct aresta *encontra_aresta(struct aresta *arestas, int tamanho, struct vertice *cauda, struct vertice *cabeca);
void recomendaP(struct grafo *g, struct vertice *c, struct vertice *pList);

// ---
// Encontra um vértice a partir do nome

struct vertice *encontra_vertice(struct vertice *vertices, const char *nome) {
    struct vertice *v;

    // Percorre todos os vértices e retorna o nome se for igual, caso contrário NULL
    for(v = vertices; v != NULL; v = v->vertice_proximo) {
        if(strcmp(v->vertice_nome, nome) == 0) {
            return v;
        }
    }

    return NULL;
}

// ---
// Encontra uma aresta a partir dos vértices dela

struct aresta *encontra_aresta(struct aresta *arestas, int tamanho, struct vertice *cauda, struct vertice *cabeca) {
    struct aresta *a;
    int i;

    // Percorre todas as arestas e retorna ela se a origem e destino forem iguais
    for(i = 0, a = arestas; i < tamanho; i++, a = a->aresta_proximo) {
        if(a->aresta_origem == cauda && a->aresta_destino == cabeca) {
            return a;
        }
    }

    return NULL;
}

// ---
// Encontra uma aresta comparando os nomes.
// Como em determinada parte do código estamos copiando/criando as arestas, não é possível comparar os ponteiros, que serão diferentes.

struct aresta *encontra_aresta_por_nome(struct aresta *arestas, struct vertice *cauda, struct vertice *cabeca) {
    struct aresta *a;

    // Percorre todas as arestas e verifica se nomes são iguais
    for(a = arestas; a != NULL; a = a->aresta_proximo) {
        if(strcmp(a->aresta_origem->vertice_nome, cauda->vertice_nome) + strcmp(a->aresta_destino->vertice_nome, cabeca->vertice_nome) == 0 || strcmp(a->aresta_origem->vertice_nome,cabeca->vertice_nome) + strcmp(a->aresta_destino->vertice_nome,cauda->vertice_nome) == 0) {
            return a;
        }
    }

    return NULL;
}

// ---
// Encontra uma aresta comparando os ponteiros. Esse é mais abrangente que o encontra_aresta

struct aresta *encontra_aresta_ponteiros(struct aresta *arestas, struct vertice *cauda, struct vertice *cabeca) {
    struct aresta *a;

    // Percorre todas as arestas e verifica se a origem e destino são iguais
    for(a = arestas; a != NULL; a = a->aresta_proximo) {
        if((a->aresta_origem == cauda && a->aresta_destino == cabeca) || (a->aresta_origem == cabeca && a->aresta_destino == cauda)) {
            return a;
        }
    }

    return NULL;
}

// ---
// Carrega os vértices go grafo Agraph_t para o que estamos implementando

struct vertice *obter_vertices(Agraph_t *grafo) {
    Agnode_t *v;
    struct vertice *vertices = NULL;
    int n_vertices = 0, i;

    for (v = agfstnode(grafo); v; v = agnxtnode(grafo, v)) {
        n_vertices ++;
    }

    if(n_vertices > 0) {
        // Aloca a quantidade de memória necessária para armazenar todos os vértices
        vertices = (struct vertice *) malloc(sizeof(struct vertice) * n_vertices);

        if(vertices != NULL) {
            // Percorre todos os vértices do grafo
            for(i = 0, v = agfstnode(grafo); i < n_vertices; i++, v = agnxtnode(grafo, v)) {
                // Duplica na memória o nome do vértice e o atribui na estrutura.
                // A duplicação é feita para evitar erros (por exemplo, se o espaço for desalocado)

                vertices[i].vertice_nome = strdup(agnameof(v));
                vertices[i].label = 0;
                vertices[i].cor = -1;

                // Define o próximo vértice como o vértice do próximo bloco alocado,
                // tirando proveito do fato de se terem alocados todos os vértices numa
                // região contígua de memória (se essa é a última posição, o próximo é NULL)
                vertices[i].vertice_proximo = (i + 1 < n_vertices) ? vertices + (i + 1) : (struct vertice *) NULL;
            }
        }
    }

    return vertices;
}

// ---
// Carrega as arestas go grafo Agraph_t para o que estamos implementando

struct aresta *obter_arestas(Agraph_t *grafo, struct vertice *lista_vertices) {
    Agedge_t *a;
    Agnode_t *v;
    struct aresta *arestas = NULL;
    struct vertice *cauda, *cabeca;
    char *peso;
    int n_arestas = 0, contador = 0;

    for (v = agfstnode(grafo); v; v = agnxtnode(grafo, v)) {
        for (a = agfstout(grafo, v); a; a = agnxtout(grafo, a)) {
            n_arestas += 1;
        }
    }

    if(n_arestas > 0) {
        // Aloca a quantidade de memória necessária para armazenar todas as arestas
        arestas = (struct aresta *) malloc(sizeof(struct aresta) * n_arestas);

        if(arestas != NULL) {
            // Percorre todas as arestas do grafo
            for(v = agfstnode(grafo); v != NULL; v = agnxtnode(grafo, v)) {
                for(a = agfstedge(grafo, v); a != NULL && contador < n_arestas; a = agnxtedge(grafo, a, v)) {

                    cauda = encontra_vertice(lista_vertices, agnameof(agtail(a)));
                    cabeca = encontra_vertice(lista_vertices, agnameof(aghead(a)));

                    // Através da cauda e da cabeça, verifica se a aresta já foi
                    // adicionada na estrutura, se ainda não, então a adiciona
                    if(encontra_aresta(arestas, contador, cauda, cabeca) == NULL) {
                        // Obtêm o parâmetro peso da aresta
                        peso = agget(a, "peso");

                        // Define os vértices de origem e destino da aresta
                        arestas[contador].aresta_origem = cauda;
                        arestas[contador].aresta_destino = cabeca;

                        // Se o peso está definido, então é convertido para int, caso contrário é 0
                        arestas[contador].aresta_peso = (peso != NULL && *peso != '\0') ? atoi(peso) : 0;

                        // Define a próxima aresta (idêntico ao modo como é feito com os vértices)
                        arestas[contador].aresta_proximo = (contador + 1 < n_arestas) ? arestas + (contador + 1) : (struct aresta *) NULL;

                        // Incrementa o contador de arestas
                        contador += 1;
                    }
                }
            }
        }
    }

    return arestas;
}

// ---
// Lê um grafo em formato dot usando as funções da biblioteca cgraph e retorna o grafo lido, ou NULL em caso de erro

grafo le_grafo(FILE *input) {
    Agraph_t *g;
    struct grafo *grafo_lido;

    // Aloca a estrutura do grafo
    grafo_lido = (struct grafo *) malloc(sizeof(struct grafo));

    if(grafo_lido != NULL) {
        // Inicializa a estrutura do grafo
        grafo_lido->grafo_nome = (char *) NULL;
        grafo_lido->grafo_vertices = (struct vertice *) NULL;
        grafo_lido->grafo_arestas = (struct aresta *) NULL;

        // Armazena em g o grafo
        if((g = agread(input, NULL)) == NULL) {
            destroi_grafo(grafo_lido);
            return NULL;
        }

        // Carrega os vértices de g
        if((grafo_lido->grafo_vertices = obter_vertices(g)) == NULL) {
            agclose(g);
            destroi_grafo(grafo_lido);
            return NULL;
        }

        // Carrega as arestas de g
        if((grafo_lido->grafo_arestas = obter_arestas(g, grafo_lido->grafo_vertices)) == NULL) {
            agclose(g);
            destroi_grafo(grafo_lido);
            return NULL;
        }

        // Define o nome do grafo e se ele é direcionado
        grafo_lido->grafo_direcionado = agisdirected(g);
        grafo_lido->grafo_nome = strdup(agnameof(g));
        grafo_lido->n_vertices = agnnodes(g);
        grafo_lido->n_arestas = agnedges(g);

        // Inicializa lista de adjacencia dos vertices
        for(struct vertice *v = grafo_lido->grafo_vertices; v != NULL; v = v->vertice_proximo){

            v->adjacencia = (struct vertice **) malloc(sizeof(vertice)*grafo_lido->n_vertices);
            int i = 0;

            for(struct vertice *vaux = grafo_lido->grafo_vertices; vaux != NULL; vaux = vaux->vertice_proximo){
                if (encontra_aresta_ponteiros(grafo_lido->grafo_arestas, v, vaux) != NULL) {
                    v->adjacencia[i] = vaux;
                    i++;
                }
            }

            for(;i<grafo_lido->n_vertices;i++){
                v->adjacencia[i] = NULL;
            }

        }

        agclose(g);
    }

    return grafo_lido;
}

// ---
// Desaloca toda a memória utilizada em g e retorna 1 em caso de sucesso, ou 0 em caos de erro

int destroi_grafo(grafo g) {
    if(g != NULL) {
        // Libera a região de memória ocupada pelo nome do grafo, se não for nula
        if(g->grafo_nome != NULL) {
            free(g->grafo_nome);
        }

        // Libera a região de memória ocupada pelos vértices do grafo, se não for nula
        if(g->grafo_vertices != NULL) {
            struct vertice *v;

            // Libera os nomes de todos os vértices
            for(v = g->grafo_vertices; v != NULL; v = v->vertice_proximo) {
                if(v->vertice_nome != NULL) {
                    free(v->vertice_nome);
                }
            }

            free(g->grafo_vertices);
        }

        // Libera a região de memória ocupada pelas arestas do grafo, se não for nula
        if(g->grafo_arestas != NULL) {
            free(g->grafo_arestas);
        }

        // Libera a região de memória ocupada pela estrutura do grafo
        free(g);
    }

    return 1;
}

// --
// escreve o grafo g em output usando o formato dot, de forma que
//
// - todos os vértices são escritos antes de todas as arestas/arcos
// - se uma aresta tem peso, este deve ser escrito como um atributo
//
// escreve o grafo g em output usando o formato dot.
//
// cada vértice do grafo escrito tem um atributo de nome "color" e o
// valor desse atributo deve ser uma cor especificada no formato
// "#rrggbb" onde rr, gg e bb são números de dois dígitos em
// representação hexadecimal indicando as intensidades de vermelho
// (red), verde (green) e azul (blue) em que se decompõe essa cor
//
// o valor deste atributo para o vértice v deve ser uma função do
// valor de cor(v,g)
//
// devolve o grafo escrito,
//         ou
//         NULL, em caso de erro

grafo escreve_grafo(FILE *output, grafo g) {
    struct vertice *v;
    struct aresta *a;
    char caractere_aresta;
    // palheta de cores do color brewer 'paired':
    // https://bl.ocks.org/mbostock/5577023
    const char *cores[] = {"#a6cee3","#1f78b4","#b2df8a","#33a02c","#fb9a99","#e31a1c","#fdbf6f","#ff7f00","#cab2d6","#6a3d9a","#ffff99","#b15928"};

    // Caso seja um grafo direcionado, é adicionado o prefixo "di"
    fprintf(output, "strict %sgraph \"%s\" {\n\n", (g->grafo_direcionado) ? "di" : "", g->grafo_nome);

    // Imprime os nomes dos vértices com o tipo c ou p, se houver
    for(v = g->grafo_vertices; v != NULL; v = v->vertice_proximo) {
      if (v->tipo_produtor_ou_consumidor != NULL) {
        fprintf(output, " \"%s\" [tipo=%s]\n", v->vertice_nome, v->tipo_produtor_ou_consumidor);
      } else if (cor(v, g) != -1) {
        int coratual = cor(v, g);
        if (coratual < 11) {
          fprintf(output, " \"%s\" [color=%s]\n", v->vertice_nome, cores[coratual]);
        } else {
          fprintf(output, " \"%s\" [color=#ffff%2d]\n", v->vertice_nome, coratual);
        }
      } else {
        fprintf(output, " \"%s\"\n", v->vertice_nome);
      }
    }

        fprintf(output, "\n");

        // Se o grafo for direcionado, representamos as arestas por v -> u,
        // sendo v o vértice de origem e u o vértice de destino de cada aresta.
        // Caso contrário, representamos as arestas por v -- u
        caractere_aresta = (g->grafo_direcionado) ? '>' : '-';

        // Imprime as arestas
        for(a = g->grafo_arestas; a != NULL; a = a->aresta_proximo) {
            fprintf(output, " \"%s\" -%c \"%s\" ", a->aresta_origem->vertice_nome, caractere_aresta, a->aresta_destino->vertice_nome);

            // Se o peso for diferente de 0, então ele é impresso
            if(a->aresta_peso != 0) {
                fprintf(output, "[peso=%d]", a->aresta_peso);
            }

            fprintf(output, "\n");
        }

    fprintf(output, "}\n");
    return g;
}

// ---
// Copia o grafo da entrada para um novo grafo, que será nosso output.

grafo copiaGrafo(grafo grafo_antigo){

    // Aloca a memória
    struct grafo *g = (struct grafo *) malloc(sizeof(struct grafo));

    // Copia os atributos
    g->grafo_direcionado = grafo_antigo->grafo_direcionado;
    g->n_arestas = grafo_antigo->n_arestas;
    g->n_vertices = grafo_antigo->n_vertices;
    g->grafo_nome = (char *)malloc(sizeof(grafo_antigo->grafo_nome));
    strcpy(g->grafo_nome,"recomendacoes");

    // Aloca os vértices
    g->grafo_vertices = (struct vertice *)malloc(sizeof(grafo_antigo->grafo_vertices));
    g->grafo_vertices = grafo_antigo->grafo_vertices;

    // Aloca as arestas
    g->grafo_arestas = (struct aresta *)malloc(sizeof(grafo_antigo->grafo_arestas));
    g->grafo_arestas = NULL;

    // Retorna o novo grafo
    return g;
}


// ---
// Copia o vértice (será usado para copiar do grafo anterior para o novo)

struct vertice* copiaVertice(struct vertice *v1){

    // Aloca o vértice
    struct vertice *v = (struct vertice *) malloc(sizeof(struct vertice));

    // Aloca e copia o atributo
    v->vertice_nome = (char *) malloc(sizeof(v1->vertice_nome));
    strcpy(v->vertice_nome,v1->vertice_nome);

    // Aloca e copia o atributo
    v->tipo_produtor_ou_consumidor = (char *) malloc(sizeof(v1->tipo_produtor_ou_consumidor));
    strcpy(v->tipo_produtor_ou_consumidor,v1->tipo_produtor_ou_consumidor);

    // Aloca e copia o atributo
    v->vertice_proximo = (struct vertice *) malloc(sizeof(struct vertice));
    v->vertice_proximo = NULL;
    return v;
}

// ---
// Como estamos copiando/criando as arestas, não é possível comparar os ponteiros, que serão diferentes. Então estamos comparando os nomes.

void recomendaP(struct grafo *g, struct vertice *c, struct vertice *pList){
    struct aresta *a;
    for (struct vertice *p = pList; p != NULL; p = p->vertice_proximo){

        // Se a aresta já existir, aumenta o peso dela em 1. Caso contrário, irá criar ela
        if (encontra_aresta_por_nome(g->grafo_arestas,c,p) != NULL){
            encontra_aresta_por_nome(g->grafo_arestas,c,p)->aresta_peso++;
            } else{
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
// para o consumidor c, e tem o atributo "peso" que é um inteiro
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
    int intersecao = 0;
    int diferenca = 0;

    // Duplica nosso grafo
    struct grafo *novo_grafo = copiaGrafo(g);

    // Percorre todos os vértices que são consumidores
    for(c1 = g->grafo_vertices; c1 != NULL; c1 = c1->vertice_proximo) {
        if (strcmp(c1->tipo_produtor_ou_consumidor,"c") == 0) {

            // Percorre todos os vértices que são consumidores e não são o vértice atual
            for(c2 = g->grafo_vertices; c2 != NULL; c2 = c2->vertice_proximo) {
                if (c2 != c1 && strcmp(c2->tipo_produtor_ou_consumidor,"c") == 0) {

                    // Percorre todos os vértices que são produtores e possui uma aresta com c2.
                    for(p = g->grafo_vertices; p != NULL; p = p->vertice_proximo) {
                        if (strcmp(p->tipo_produtor_ou_consumidor,"p") == 0 && encontra_aresta_ponteiros(g->grafo_arestas, c2, p) != NULL){
                            // Se também possuir uma aresta com c1, então aumenta em 1 a interseção. Caso contrário, aumenta a diferença e copia o vértice.
                            if (encontra_aresta_ponteiros(g->grafo_arestas, c1, p) != NULL){
                                intersecao += 1;
                                } else {
                                aux = (struct vertice*) malloc(sizeof(struct vertice));
                                aux = copiaVertice(p);
                                aux->vertice_proximo = recomenda;
                                recomenda = aux;
                                diferenca += 1;
                            }
                        }
                    }

                    // Se a interseção for maior que a diferença, modifica o peso/cria aresta com peso 1 no grafo, e reseta os parâmetros para o próximo loop.
                    if (intersecao >= diferenca){
                        recomendaP(novo_grafo,c1,recomenda);
                    }
                    recomenda = NULL;
                    intersecao = 0;
                    diferenca = 0;
                }
            }
        }
    }

    return novo_grafo;
}

//------------------------------------------------------------------------------
// efetua a criação do vertice de nome passado pelo teste.c

vertice vertice_de_nome(char *nome, grafo g) {
    for(vertice v = g->grafo_vertices; v != NULL; v = v->vertice_proximo)
    if (strcmp(nome, v->vertice_nome) == 0)
    return v;
    return NULL;
}

//------------------------------------------------------------------------------
// pega a maior label, para ser usada na busca_lexicografica

vertice get_highest_label(int label, grafo g) {
    for(vertice v = g->grafo_vertices; v != NULL; v = v->vertice_proximo)
    if(v->label==label-1)
    return v;
    return NULL;
}

//------------------------------------------------------------------------------
// preenche o vetor v (presumidamente um vetor com n_vertices(g)
// posições) com os vértices de g ordenados de acordo com uma busca em
// largura lexicográfica sobre g a partir de r e devolve v

vertice *busca_lexicografica(vertice r, grafo g, vertice *vetor) {

    vertice v = r;
    int label = g->n_vertices;
    v->label = label;
    int i;

    while(v != NULL){
        for(i = 0; v->adjacencia[i] != NULL; i++){
            if(v->adjacencia[i]->label == 0){
                v->adjacencia[i]->label = --label;
            }
        }
        v = get_highest_label(v->label, g);
    }

    if (vetor == NULL){
        vetor = (vertice*) malloc(sizeof(vertice) * g->n_vertices);
        if (vetor == NULL)
        return NULL;
    }


    for(i = 0; i < g->n_vertices; i++){
        vetor[i] = get_highest_label(g->n_vertices + 1 - i, g);
    }
    return vetor;
}

//------------------------------------------------------------------------------
// devolve um número entre 0 e o número de vertices de g

unsigned int cor(vertice v, grafo g){
    return v->cor;
}


int n_vertices(grafo g) {
  return g->n_vertices;
}

//------------------------------------------------------------------------------
// função da busca gulosa que irá percorrer os vértices para descobrir qual cor
// deverá ser escolhida.

unsigned int get_color(vertice v, grafo g){
    bool found = false;
    int i, j;
    for(i=1; i < g->n_vertices; i++) {
        for(j = 0; v->adjacencia[j] != NULL; j++) {
            if(v->adjacencia[j]->cor == i)
            found = true;
        }

        if(!found){
            return i;
        }
        found = false;
    }

    return i;
}

//------------------------------------------------------------------------------
// colore os vértices de g de maneira "gulosa" segundo a ordem dos
// vértices em v e devolve o número de cores utilizado
//
// ao final da execução,
//     1. cor(v,g) > 0 para todo vértice de g
//     2. cor(u,g) != cor(v,g), para toda aresta {u,v} de g

unsigned int colore(grafo g, vertice *v){
    int max_color = 0;
    for(int i = g->n_vertices - 1; i >= 0; i--){
        v[i]->cor = get_color(v[i], g);

        if(v[i]->cor > max_color)
        max_color = v[i]->cor;
    }
    return max_color;
}
