/*****************************************************************/
/*         Trabalho pratico 1 | PROG2 | MIEEC | 2017/18          */
/*****************************************************************/
/*                  NAO ALTERAR ESTE FICHEIRO                    */
/*****************************************************************/

#include "cidades.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define FICH1 "./cidades.bin"
#define FICH2 "./cidades-save.bin"
#define FICH3 "./cidades-pais.bin"
#define FICH4 "./cidades-area.bin"
#define FICH5 "./cidades-poke.bin"

#define INICIA_TESTE() \
	int erros = 0;

#define ERRO(msg)            \
	{                        \
		printf("\n\t" #msg); \
		erros++;             \
	}

#define FINALIZA_TESTE() \
	if (!erros)          \
		printf("OK\n");  \
	else                 \
		printf("\n");    \
	return erros;

int teste_cidades_load()
{
	INICIA_TESTE()

	printf("cidades_load(): ");

	vetor *v = cidades_load(FICH1);
	if (!v)
	{
		printf("\n\terro na leitura do ficheiro '%s'", FICH1);
		erros++;
		FINALIZA_TESTE();
	}

	if (v->tamanho != 1743)
		ERRO("o vetor resultante deveria ter tamanho 1743")

	vetor_apaga(v);

	FINALIZA_TESTE()
}

int teste_cidades_save()
{
	INICIA_TESTE()

	printf("cidades_save(): ");

	vetor *v = cidades_load(FICH1);
	if (!v)
	{
		printf("\n\terro na leitura do ficheiro '%s'", FICH1);
		erros++;
		vetor_apaga(v);
		FINALIZA_TESTE();
	}

	remove(FICH2);

	if (cidades_save(v, FICH2) != 1743)
		ERRO("o valor de retorno deveria ser 1743")

	FILE *f = fopen(FICH2, "rb");
	if (!f)
	{
		printf("\n\terro na leitura do ficheiro '%s'", FICH2);
		erros++;
		vetor_apaga(v);
		FINALIZA_TESTE();
	}
	fseek(f, 0L, SEEK_END);
	if (ftell(f) != 1743 * sizeof(cidade))
		ERRO("o ficheiro resultante não tem o tamanho correcto")

	fclose(f);
	vetor_apaga(v);

	FINALIZA_TESTE()
}

int teste_cidades_resort()
{
	clock_t inicio, fim;
	double t_pais, t_area;

	INICIA_TESTE()

	printf("cidades_resort(): ");

	vetor *v = cidades_load(FICH1);
	inicio = clock();
	cidades_resort(v, 'p');
	fim = clock();
	t_pais = (double)(fim - inicio) / CLOCKS_PER_SEC;
	if (strcmp(vetor_elemento(v, 0)->nome, "Herat") != 0 ||
		strcmp(vetor_elemento(v, vetor_tamanho(v) - 1)->nome, "Harare") != 0)
		ERRO("elemento inicial e/ou final errado depois de ordenar por pais");
	cidades_save(v, FICH3);
	vetor_apaga(v);
	v = cidades_load(FICH1);
	inicio = clock();
	cidades_resort(v, 'a');
	fim = clock();
	t_area = (double)(fim - inicio) / CLOCKS_PER_SEC;
	if (strcmp(vetor_elemento(v, 0)->nome, "Nuuk") != 0 ||
		strcmp(vetor_elemento(v, vetor_tamanho(v) - 1)->nome, "New York, NY-NJ-CT") != 0)
		ERRO("elemento inicial e/ou final errado depois de ordenar por area");
	cidades_save(v, FICH4);
	vetor_apaga(v);
	printf("\n\tTempo de execucao ordenacao por pais (s): %f", t_pais);
	printf("\n\tTempo de execucao ordenacao por area (s): %f\n\t", t_area);

	FINALIZA_TESTE()
}

int teste_cidades_peek()
{
	clock_t inicio, fim;
	int res;
	cidade c = {0};
	INICIA_TESTE()

	printf("cidades_peek(): ");

	inicio = clock();
	res = cidades_peek(FICH1, "Porto", &c);
	fim = clock();

	if (res != 1192)
		ERRO("retorno deveria ser 1192 ao pesquisar a cidade do Porto");

	if (strcmp(c.nome, "Porto") != 0 || strcmp(c.pais, "Portugal") != 0)
		ERRO("nome da cidade ou pais não foram correctamente carregados");
	if (c.populacao != 1485000 || c.area != 777)
		ERRO("populacao ou area nao foram correctamente carregadas");

	printf("\n\tTempo de execucao (s): %f\n\t", (double)(fim - inicio) / CLOCKS_PER_SEC);

	FINALIZA_TESTE()
}

int teste_cidades_poke()
{
	clock_t inicio, fim;
	int res;
	cidade c;
	FILE *f1, *f2;
	INICIA_TESTE()

	printf("cidades_poke(): ");

	f1 = fopen(FICH1, "rb");
	f2 = fopen(FICH5, "wb");
	if (!f1)
	{
		printf("\n\terro na leitura do ficheiro '%s'", FICH1);
		erros++;
		FINALIZA_TESTE();
	}
	if (!f2)
	{
		printf("\n\terro na escrita do ficheiro '%s'", FICH5);
		erros++;
		FINALIZA_TESTE();
	}
	while (!feof(f1))
	{
		fread(&c, sizeof(cidade), 1, f1);
		fwrite(&c, sizeof(cidade), 1, f2);
	}
	fclose(f1);
	fclose(f2);

	strcpy(c.nome, "TesteC");
	strcpy(c.pais, "TesteP");
	c.area = 5;
	c.populacao = 10;

	inicio = clock();
	res = cidades_poke(FICH5, "Porto", c);
	fim = clock();

	if (res != 1192)
		ERRO("retorno deveria ser 1192 ao alterar a cidade do Porto");

	f2 = fopen(FICH5, "rb");
	if (f2)
	{
		fseek(f2, 1192 * sizeof(cidade), SEEK_SET);
		fread(&c, sizeof(cidade), 1, f2);
		if (strcmp(c.nome, "TesteC") != 0 || strcmp(c.pais, "TesteP") != 0)
			ERRO("nome da cidade ou pais não foram correctamente escritos");
		if (c.populacao != 10 || c.area != 5)
			ERRO("populacao ou area nao foram correctamente escritos");
	}
	fclose(f2);

	printf("\n\tTempo de execucao (s): %f\n\t", (double)(fim - inicio) / CLOCKS_PER_SEC);

	FINALIZA_TESTE()
}

int teste_cidades_similar()
{
	char **s = NULL;
	int n = 0, i;

	INICIA_TESTE()

	printf("cidades_similar(): ");

	vetor *v = cidades_load(FICH1);
	s = cidades_similar(v, "Porto", 5000, &n);

	if (n != 6)
		ERRO("numero de cidades similares deveria ser 6");
	if (!s)
	{
		ERRO("vetor de strings inválido");
		vetor_apaga(v);
		FINALIZA_TESTE()
	}

	if (strcmp(s[0], "Al-Manamah") || strcmp(s[1], "Kollam, KL") || strcmp(s[2], "Niamey") || strcmp(s[3], "Srinagar, JK") || strcmp(s[4], "Virginia Beach-Norfolk, VA") || strcmp(s[5], "Yekaterinburg"))
		ERRO("conteudo de vetor de strings esta incorrecto");

	vetor_apaga(v);
	for (i = 0; i < n; i++)
		free(s[i]);
	free(s);

	FINALIZA_TESTE()
}

int main()
{

	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	int erros = 0;

	erros += teste_cidades_load();
	if (erros == 0)
	{
		erros += teste_cidades_save();
		erros += teste_cidades_resort();
		erros += teste_cidades_peek();
		erros += teste_cidades_poke();
		erros += teste_cidades_similar();
	}

	if (!erros)
		printf("FIM DE TODOS OS TESTES.\n");
	else
		printf("FOI ENCONTRADO UM TOTAL DE %d ERROS.\n", erros);
	return 0;
}
