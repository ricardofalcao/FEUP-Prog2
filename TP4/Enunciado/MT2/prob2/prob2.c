#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "pilha.h"

#define BUFFER 256

/****************************************************/
/*              Funcoes a implementar               */
/****************************************************/

/*** problema 2 ***/
float* avalia_expressoes(FILE *ficheiro, int *N)
{
	return NULL;
}

/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/

#define BUFFER 256

int main()
{
	FILE *fin;
	float *resultados;
	char expressao[BUFFER];
	int i, n=0;

	fin = fopen("expressoes.txt", "r");
	if(fin == NULL)
	{
		printf("Erro ao abrir ficheiro.\n");
		return 1;
	}

	if((resultados = avalia_expressoes(fin, &n)) != NULL)
	{
		rewind(fin);
		for(i=0; i<n && fgets(expressao, BUFFER, fin) != NULL; i++)
		{
			expressao[strlen(expressao)-1] = '\0';
			printf("%s -> %f\n", expressao, resultados[i]);
		}
	}
	else
		printf("Funcao retornou erro.\n");

	fclose(fin);

	return 0;
}
