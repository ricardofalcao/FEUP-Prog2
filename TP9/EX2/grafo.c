/*****************************************************************/
/*   Grafo c/ matriz de adjacencias | PROG2 | MIEEC | 2017/18    */      
/*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

int grafo_vertice_valido(grafo *g, int vertice) {
    return vertice > 0 && vertice <= g->tamanho;
}

void min(int vertice1, int vertice2, int *origem, int *dest) {
    if(vertice1 < vertice2) {
        *origem = vertice1;
        *dest = vertice2;
    } else {
        *origem = vertice2;
        *dest = vertice1;
    }
}

/* cria grafo com n vertices */
grafo* grafo_novo(int n)
{
    int v;
    grafo* g;
    
    g = (grafo*)malloc(sizeof(grafo));
    g->tamanho = n;

    /* cria array de listas de adjacencias */
    g->adjacencias = (int**)malloc(n * sizeof(int*));
    for(v=0; v<n; v++)
    {
        g->adjacencias[v] = (int*)calloc(n - v - 2, sizeof(int));
    }

    return g;
}

/* apaga grafo e liberta memoria */
void grafo_apaga(grafo* g)
{
    if(g == NULL)
        return;

    if(g->adjacencias != NULL)
    {
        int v;
        for (v = 0; v < g->tamanho; v++)
            free(g->adjacencias[v]);
        free(g->adjacencias);
    }
    free(g);
}

/* adiciona no grafo g uma aresta entre os vertices origem e destino
   retorna -1 em caso de erro (parametros invalidos)
   retorna 0 se a aresta ja existir e 1 se foi adicionada */
int grafo_adiciona(grafo *g, int vertice1, int vertice2)
{
    // Complexidade O(2)
    if(vertice1 == vertice2) {
        return -1;
    }

    int aresta = grafo_aresta(g, vertice1, vertice2);
    if(aresta != 0) {
        return aresta;
    }

    vertice1--;
    vertice2--;

    int origem, dest;
    min(vertice1, vertice2, &origem, &dest);

    g->adjacencias[origem][dest - origem - 1] = 1;

    return 1;
}

/* remove do grafo g a aresta entre os vertices origem e destino
   retorna -1 em caso de erro (parametros invalidos)
   retorna 0 se a aresta nao existir e 1 se foi removida */
int grafo_remove(grafo *g, int vertice1, int vertice2)
{
    // Complexidade O(2)
    if(vertice1 == vertice2) {
        return -1;
    }

    int aresta = grafo_aresta(g, vertice1, vertice2);
    if(aresta != 1) {
        return aresta;
    }

    vertice1--;
    vertice2--;

    int origem, dest;
    min(vertice1, vertice2, &origem, &dest);

    g->adjacencias[origem][dest - origem - 1] = 0;
    return 1;
}

/* testa no grafo g a aresta entre os vertices origem e destino
   retorna -1 em caso de erro (parametros invalidos)
   retorna 0 se a aresta nao existir e 1 se existir */
int grafo_aresta(grafo *g, int vertice1, int vertice2)
{
    // Complexidade O(1)
    if(vertice1 == vertice2) {
        return -1;
    }

    if(!grafo_vertice_valido(g, vertice1) || !grafo_vertice_valido(g, vertice2)) {
        return -1;
    }

    vertice1--;
    vertice2--;

    int origem, dest;
    min(vertice1, vertice2, &origem, &dest);

    return g->adjacencias[origem][dest - origem - 1] == 1;
}

/* cria um novo grafo com base numa lista de adjacencias
   parametro adjacencies e' um array de inteiros, representado
   um numero n_edges de arestas.
   retorna um apontador para o grafo criado */
grafo* grafo_deLista(int* adjacencias, int n_arestas)
{
    if(n_arestas <= 0) {
        return NULL;
    }

    int n_vertices = 0;
    int i;
    
    for(i = 0; i < n_arestas; i++) {
        int origem = adjacencias[i * 2];
        int dest = adjacencias[i * 2 + 1];

        if(origem > n_vertices) {
            n_vertices = origem;
        }

        if(dest > n_vertices) {
            n_vertices = dest;
        }
    }
    

    grafo *g = grafo_novo(n_vertices);

    /* alinea 1.2 */
    for(i = 0; i < n_arestas; i ++) {
        int origem = adjacencias[i * 2];
        int dest = adjacencias[i * 2 + 1];

        grafo_adiciona(g, origem, dest);
    }

    return g;
}

/* cria e retorna um vetor de inteiros contendo os vertices
   de destino de todas as arestas com origem em i */
vetor* grafo_arestasSaida(grafo* g, int vertice)
{
    // complexidade O(N)
    vertice--;
    vetor *vet = vetor_novo();

    for(int i = 0; i < g->tamanho; i++) {
        int origem, dest;
        min(vertice, i, &origem, &dest);

        if(g->adjacencias[origem][dest - origem - 1] == 1) {
            vetor_insere(vet, i + 1, -1);
        }
    }
    /* alinea 1.3 */

    return vet;
}

/* cria e retorna um vetor de inteiros contendo os vertices
   de origem de todas as arestas com destino a i */
vetor* grafo_arestasEntrada(grafo* g, int origem)
{
    return grafo_arestasSaida(g, origem);
}

/* verifica se o grafo g e' completo
   retorna -1 em caso de erro (parametros invalidos)
   retorna 1 se o grafo for completo e 0 se nao o for */
int grafo_completo(grafo* g)
{
    // Complexidade O(N + (N - 1) + (N - 2) ...)
    int i, j;
    for(i = 0; i < g->tamanho; i++) {
        for(j = 0; j < g->tamanho - i - 1; i++) {
            if(g->adjacencias[i][j] == 0) {
                return 0;
            }
        }
    }

    return 1;
}

/* verifica se o vertice i do grafo g e' uma celebridade
   retorna -1 em caso de erro (parametros invalidos)
   retorna 1 se o vertice for uma celebridade e 0 se nao o for */
int grafo_eCelebridade(grafo* g, int i)
{
    // Complexidade O(1)
    return 0;
}

/* verifica se o grafo g tem pelo menos uma celebridade
   retorna -1 em caso de erro (parametros invalidos)
   retorna 1 se existir uma celebridade e 0 se nao existir */
int grafo_temCelebridade(grafo* g)
{
    // Complexidade O(1)
    return 0;
}

/* imprime as adjacencias do grafo */
void grafo_imprime(grafo* g)
{
    int i, j;

    if (g == NULL)
        return;

    for (i = 0; i < g->tamanho; i++)
    {
        printf("%d: ", i);
        for(j = 0; j < g->tamanho; j++)
        {
            if(g->adjacencias[i][j] != 0)
                printf("%d ", j);
        }
        printf("\n");
    }
}

