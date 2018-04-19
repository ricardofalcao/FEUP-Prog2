/*****************************************************************/
/*         Trabalho pratico 2 | PROG2 | MIEEC | 2017/18          */
/*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"

#define  HEAP_MAX_SIZE 10

/* primeira serie de testes */
const int pri_init [] = { 4, 5, 8, 1, 6 , 12, 3 };

const int nelem = sizeof(pri_init)/sizeof(int);

const char * filmes[] = {
  "Wonder Woman",
  "Spider-Man: Homecoming",
  "Thor: Ragnarok",
  "Logan",
  "Get Out",
  "Blade Runner 2049",
  "Guardians of the Galaxy Vol. 2"
};
  
/* segunda série de testes */

elemento livros[] = {
  {14, "What Happened"},
  {4, "Giraffes Can't Dance"},
  {3, "Milk and Honey"},
  {8, "Astrophysics for People in a Hurry"},
  {2, "Wonder"},
  {18, "How to Win Friends & Influence People"},
  {11, "The Handmaid's Tale"},
  {20, "A Man Called Ove"}
};

const int nlivros = sizeof(livros)/sizeof(elemento); 

static void  ERROR(const char *x) {
  fprintf(stderr, "ERRO: %s\n",x);
}

int main(void)
{
  int i, indice;
  char *str;
  heap *h;
  
  printf("** Testes com filmes\n");
  if ((h = heap_nova(HEAP_MAX_SIZE)) == NULL)
    ERROR("Erro ao criar nova heap.");

  if (h != NULL) {
    for (i = 0; i < nelem; i++) {
      if (heap_insere(h, filmes[i], pri_init[i]) != 1)
        ERROR("Erro ao inserir em heap.");
    }
  
    /* mostraHeap(h, 1); */ 
   
    printf("Numero de elementos: %d\n", h->tamanho);

    if ((str = heap_remove(h)) == NULL)
      ERROR("Erro ao retirar elemento de heap.");
    else
    {
      printf("Primeiro valor retirado da heap: %s ", str);
      if(strcmp(str, "Logan") == 0)
        puts("(OK)");
      else
        puts("(ERRO)");
      free(str);
    }
  
    if ((str = (heap_remove(h))) == NULL)
      ERROR("Erro ao retirar elemento de heap.");
    else
    {
      printf("Segundo valor retirado da heap: %s ", str);
      if(strcmp(str, "Guardians of the Galaxy Vol. 2") == 0)
        puts("(OK)");
      else
        puts("(ERRO)");
      free(str);
    }
  
    printf("Numero de elementos: %d ", h->tamanho);
    if(h->tamanho == 5)
      puts("(OK)");
    else
      puts("(ERRO)");      

    /* mostraHeap(h, 1); */
    
    for (i = 0; i < nelem - 2; i++)
      if ((str = heap_remove(h)) == NULL)
        ERROR("HEAP devia ter elementos.");      
      else
        free(str);
  
    if ((str = heap_remove(h)) != NULL)
      ERROR("HEAP não está vazia!");
    else if (h != NULL)
      printf("OK: Heap vazia.\n");
  
    heap_apaga(h);
  }
  
  printf("** Mais testes com filmes\n");
  
  if ((h = heap_nova(HEAP_MAX_SIZE/2)) == NULL)
    ERROR("Erro ao criar segunda heap.");

  if (h != NULL) {
    
    for (i=0; i< nelem; i++) 
      if (heap_insere(h, filmes[i], pri_init[i]) == 0)
        break;
    
    if (i == 5)
      printf("Nova heap tem 5 elementos.\n");
    else
      ERROR("ERRO na insercao de elementos na segunda heap\n");
    
    printf("Numero de elementos: %d (capacidade: %d)\n",
      h->tamanho, h->capacidade);

    /* mostraHeap(h, 1); */

    heap_apaga(h);
  }
    
  printf("** Teste com livros\n");
  
  if ((h = heap_constroi(livros, nlivros)) == NULL)
    ERROR("Erro ao construir heap.");

  if (h != NULL) {
    if (h->tamanho != nlivros || h->capacidade != nlivros)
      ERROR("Erro ao construir a heap: tamanho ou capacidade errados.");
    else
      printf("Tamanho de heap=%d (OK) e capacidade=%d (OK).\n",
      h->tamanho, h->capacidade);

    if (!strcmp(h->elementos[1]->valor, "Wonder"))
      printf("Valor na raiz do heap OK.\n");
    else
      printf("Valor na raiz da heap errado.\n");
  
    /* mostraHeap(h,1); */
  
    indice = 2;
    printf("Alterar prioridade de \"%s\" para %d.\n",
      h->elementos[indice]->valor, 9);
    if (heap_altera_prioridade(h, indice, 9) == -1)
      ERROR("Erro ao alterar a prioridade.");
  
    /* mostraHeap(h,1); */ 
  
    if (!strcmp("Milk and Honey",h->elementos[5]->valor))
      printf("OK: Elemento alterado esta' na posicao certa.\n");
    else
      ERROR("Elemento alterado NAO esta' na posicao certa.\n");
    
    indice = 7;
    printf("Alterar prioridade de \"%s\" para %d.\n",
      h->elementos[indice]->valor, 1);
    
    if (heap_altera_prioridade(h, indice, 1) == -1)
      ERROR("Erro ao alterar a prioridade.");
    
    if (!strcmp("The Handmaid's Tale", h->elementos[1]->valor))
      printf("OK: Elemento alterado esta' na posicao certa.\n");
    else
      ERROR("Elemento alterado NAO esta' na posicao certa.\n");
    
    /* mostraHeap(h,1); */
  
    heap_apaga(h);
  }
  return 0;
}
