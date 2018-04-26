#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lista.h"
#include "tabdispersao.h"
#define STRLEN 60

void trim(char* vec) {
    int n = strlen(vec);

    while(vec[n-1] == '\n' || vec[n-1] == '\r') {
        vec[n-1] = 0;
        n--;
    }
}

int main() {
    FILE *file = fopen("englishwords.txt", "r");
    lista *l = lista_nova();

    clock_t inicio, fim;
    double tempo;

    char str[STRLEN];
    while(fgets(str, STRLEN, file) != NULL) {
        lista_insere(l, str, NULL);
    }

    inicio = clock();

    lista_pesquisa(l, "eq26", LISTA_INICIO);
    lista_pesquisa(l, "equal.this", LISTA_INICIO);
    lista_pesquisa(l, "peopil", LISTA_INICIO);
    lista_pesquisa(l, "peopel", LISTA_INICIO);

    fim = clock();
    tempo = (double)(fim -inicio) / CLOCKS_PER_SEC;
    printf("tempo em segundos: %lf\n", tempo);

    tabela_dispersao *tab = tabela_nova(lista_tamanho(l), hash_krm);

    while(fgets(str, STRLEN, file) != NULL) {
        tabela_adiciona(tab, str, str);
    }

    inicio = clock();

    tabela_valor(tab, "eq26");
    tabela_valor(tab, "equal.this");
    tabela_valor(tab, "peopil");
    tabela_valor(tab, "peopel");

    fim = clock();
    tempo = (double)(fim -inicio) / CLOCKS_PER_SEC;
    printf("tempo em segundos: %lf\n", tempo);

    fclose(file);

    return 0;
}