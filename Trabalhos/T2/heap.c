/*****************************************************************/
/*         Trabalho pratico 2 | PROG2 | MIEEC | 2017/18          */
/*****************************************************************/
/*                    FUNCOES A IMPLEMENTAR                      */
/*****************************************************************/

#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int str_valida(const char *str) {
  return str == NULL || str[0] == '\0' ? 0 : 1;
}

int heap_valida(heap *h) {
  return h == NULL || h->elementos == NULL ? 0 : 1;
}

void heap_swap(heap *h, int a, int b) {
  elemento *el = h->elementos[a];
  h->elementos[a] = h->elementos[b];
  h->elementos[b] = el;
}

void heap_float(heap *h, int index) {
  int i = index;
  while(i > 1 && h->elementos[i / 2]->prioridade > h->elementos[i]->prioridade) {
    heap_swap(h, i, i / 2);
    i /= 2;
  }
}

void heap_sink(heap *h, int index) {
  int i = index;
  // enquanto tiver filhos
  while(i * 2 <= h->tamanho) {
    int f1 = i * 2;
    int f2 = i * 2 + 1;

    if(f2 <= h->tamanho && h->elementos[f2]->prioridade < h->elementos[f1]->prioridade) {
      f1 = f2;
    }

    if(h->elementos[i]->prioridade < h->elementos[f1]->prioridade) {
      break;
    }

    heap_swap(h, i, f1);
    i = f1;
  }
}

heap* heap_nova(int capacidade)
{
  if(capacidade <= 0) {
    return NULL;
  }

  heap *h = malloc(sizeof(heap));
  if(h == NULL) {
    return NULL;
  }

  h->capacidade = capacidade;
  h->tamanho = 0;
  
  h->elementos = malloc(sizeof(elemento) * (capacidade + 1));
  if(h->elementos == NULL) {
    return NULL;
  }

  return h;
}

int heap_insere(heap * h, const char * texto, int prioridade)
{
  if(!heap_valida(h) || !str_valida(texto)) {
    return 0;
  }

  if(h->tamanho == h->capacidade) {
    return 0;
  }

  char *copy = strdup(texto);

  if(copy == NULL) {
    return 0;
  }

  elemento *el = malloc(sizeof(elemento));
  el->prioridade = prioridade;
  el->valor = copy;

  h->tamanho++;
  h->elementos[h->tamanho] = el;
  heap_float(h, h->tamanho);

  return 1;
}

void heap_apaga(heap *h)
{
  if(h == NULL) {
    return;
  }

  int i;
  for(i = 1; i <= h->tamanho; i++) {
    free(h->elementos[i]->valor);
    free(h->elementos[i]);
  }

  free(h->elementos);
  free(h);
}

char* heap_remove(heap * h)
{
  if(!heap_valida(h) || h->tamanho == 0) {
    return NULL;
  }

  elemento *raiz = h->elementos[1];
  char *valor = strdup(raiz->valor);
  free(raiz->valor);
  free(raiz);

  elemento *folha = h->elementos[h->tamanho];
  h->elementos[1] = folha;
  h->tamanho--;

  heap_sink(h, 1);
  
  return valor;
}

heap* heap_constroi(elemento* v, int n_elementos)
{
  if(v == NULL || n_elementos <= 0) {
    return NULL;
  }

  heap *h = heap_nova(n_elementos);
  if(h == NULL) {
    return NULL;
  }

  int i;
  for(i = 0; i < n_elementos; i++) {
    elemento el = v[i];

    if(!str_valida(el.valor) || heap_insere(h, el.valor, el.prioridade) == 0) {
      heap_apaga(h);
      return NULL;
    }
  }

  return h;
}

int heap_altera_prioridade(heap *h, int indice, int nova_prioridade)
{
  if(!heap_valida(h) || indice <= 0) {
    return -1;
  }

  h->elementos[indice]->prioridade = nova_prioridade;
  heap_sink(h, indice);
  heap_float(h, indice);

  return 1;
}

void mostraHeap(heap *h, int indice)
{
  int i, nivel = 0;
  
  if (indice <= h->tamanho)
  {
    i = indice;
    while(i > 1)
    {
      i = i/2;
      nivel++;
    }
    
    mostraHeap(h, indice*2);
    
    for(i = 0; i < 3 * nivel; i++)
      printf("     ");
    
    printf("%s (%d)\n",h->elementos[indice]->valor, h->elementos[indice]->prioridade);
    
    mostraHeap(h, indice*2+1);
  }
}