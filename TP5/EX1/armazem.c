#include "armazem.h"
#include "fila_contentores.h"
#include "pilha_contentores.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * funcoes do armazem
 */
/* alinea b) */
armazem* armazem_novo(int comprimento, int altura)
{
	armazem *arm = malloc(sizeof(armazem));
	if(arm == NULL) {
		return NULL;
	}

	arm->altura = altura;
	arm->comprimento = comprimento;

	return arm;
}

/* alinea c) */
int armazem_vazio(armazem* armz)
{
	if(armz == NULL || armz->contentores == NULL) {
		return 1;
	}

	/* devolve vazio */
	return 0;
}

/* alinea d) */
int armazem_cheio(armazem* armz)
{
	if(armz == NULL || armz->contentores == NULL) {
		return 0;
	}

	fila *f = armz->contentores;
	if(fila_tamanho(f) != armz->comprimento) {
		return 0;
	}

	pilha *p = fila_back(f);
	if(pilha_tamanho(p) != armz->altura) {
		return 0;
	}

	return 1;
}

/* alinea e) */
int armazenar_contentor(armazem* armz, contentor* contr)
{
	if(armz == NULL) {
		return 0;
	}

	if(armz->contentores == NULL) {
		armz->contentores = fila_nova();
	}

	fila *f = armz->contentores;
	pilha *p = fila_back(f);

	if(p == NULL || pilha_tamanho(p) == armz->altura) {
		// esta cheio
		if(fila_tamanho(f) == armz->comprimento) {
			return 0;
		}

		p = pilha_nova();
		fila_push(f, p);
	}

	pilha_push(p, contr);
	return 1;
}

/* alinea f) */
contentor* expedir_contentor(armazem* armz)
{
	if(armz == NULL || armz->contentores == NULL) {
		return NULL;
	}

	fila *f = armz->contentores;
	pilha *p = fila_front(f);

	contentor *c = pilha_top(p);
	char *cc = strdup(c->destino);
	pilha_pop(p);
	c->destino = cc;

	if(pilha_tamanho(p) == 0) {
		fila_pop(f);
	
		if(fila_tamanho(f) == 0) {
			fila_apaga(f);
			armz->contentores = NULL;
		}
	}

	return c;
}
