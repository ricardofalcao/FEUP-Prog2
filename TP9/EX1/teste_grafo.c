#include "grafo.h"
#include <stdio.h>

int main()
{
	/* exemplo da alinea 1.2 */
	int adj[] = {1,2,1,3,1,4,1,5,2,5,3,5,4,5,6,5};
	grafo *g12 = grafo_deLista(adj, 8);
	grafo_imprime(g12);

	/* outros testes */

	vetor *vet1 = grafo_arestasSaida(g12, 1);
	vetor *vet2 = grafo_arestasEntrada(g12, 5);

	printf("\n\n");

	int i;
	for(i  = 0; i < vet1->tamanho; i++) {
		printf("%d ", vetor_elemento(vet1, i));
	}

	printf("\n");
	for(i  = 0; i < vet2->tamanho; i++) {
		printf("%d ", vetor_elemento(vet2, i));
	}

	printf("\n");

	printf("Celeb: %d\n", grafo_eCelebridade(g12, 1));
	printf("Celeb2: %d\n", grafo_eCelebridade(g12, 5));
	printf("Celeb3: %d\n", grafo_temCelebridade(g12));

	/*
	grafo *gr = grafo_novo(5);
	printf("\n* Testes iniciais:\n");
	printf("	Teste 1: %d\n", grafo_adiciona(gr, 1, 2));
	printf("	Teste 2: %d\n", grafo_adiciona(gr, 1, 2));
	printf("	Teste 3: %d\n", grafo_adiciona(gr, 1, 4));
	printf("	Teste 4: %d\n", grafo_adiciona(gr, 4, 3));
	printf("	Teste 5: %d\n", grafo_adiciona(gr, 10, 2));
	*/

	grafo_apaga(g12);
	printf("\nFIM\n");

	return 0;
}
