/*****************************************************************/
/*         Trabalho pratico 2 | PROG2 | MIEEC | 2017/18          */
/*****************************************************************/

#ifndef HEAP_H
#define HEAP_H

typedef struct {
	int prioridade;
	char *valor;
} elemento;

typedef struct {
	/* numero de elementos no vetor */
	int tamanho;
	/* tamanho maximo do vetor */
	int capacidade;

	/* vetor de apontadores para elementos */
	elemento ** elementos;
} heap;

/* cria nova heap */
heap* heap_nova(int tamanho_maximo);

/* apaga heap */
void heap_apaga(heap *h);

/* insere elemento na heap com uma determinada prioridade */
int heap_insere(heap *h, const char * texto, int prioridade);

/* remove elemento na raiz da heap */
char * heap_remove(heap *h);

/* imprime o estado actual da heap, a partir do indice indicado */
void mostraHeap(heap *h, int indice);

/* cria uma nova heap com os elementos do vetor v */
heap *heap_constroi (elemento* v, int n_elementos);

/* alterar prioridade de elemento existente na posicao indice_elemento */
int heap_altera_prioridade (heap *h, int indice_elemento, int nova_prioridade);

#endif /* HEAP_H */
