#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "avl.h"


void guarda_conteudo(arvore_avl *arvore, lista *lst)
{
	/* alinea 3.1 */


}

lista* descobre_segredo(arvore_avl *arvore, lista *indicacoes)
{
	/* alinea 3.2 */

	return NULL;
}


/* v-- nao alterar funcao main --v */

int main()
{
	char data[][20] = { "prog2", "mt2", "trabalho", "e'", "muito", "zzzz...",
						"dificil", "facil", "nada", "verdade"};
	int i;
	
	{
		arvore_avl *T;
		lista *lst;
		int i;

		T = avl_nova();
		for(i=0; i<10; i++)
			avl_insere(T, data[i]);

		lst = lista_nova();
		guarda_conteudo(T, lst);

		printf("Conteudo: ");
		if (lista_tamanho(lst) != 0)
		{
			for (i = 0; i < lista_tamanho(lst); i++)
				printf ("%s  ", lista_elemento(lst, i)->str);
			puts("");
		}
		
		
		avl_apaga(T);
		lista_apaga(lst);
	}

	{
		int i;
		arvore_avl *T;
		lista *res, *indicacoes;
		
		printf("\n");

		T = avl_nova();
		for(i=0; i<10; i++)
			avl_insere(T, data[i]);

		indicacoes = lista_nova();
		lista_insere(indicacoes, "esquerda", NULL);
		lista_insere(indicacoes, "esquerda", NULL);
		lista_insere(indicacoes, "direita", NULL);
		
		res = descobre_segredo(T, indicacoes);
		
		printf("Segredo: ");
		if(res)
		{
			for(i=0; i<res->tamanho; i++)
				printf("%s ", lista_elemento(res, i)->str);
		}
		
		avl_apaga(T);
		printf("\n");
	}
	

	return 0;
}
