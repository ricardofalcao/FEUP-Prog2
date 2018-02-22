#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vetor.h"
#define NCARS 24

void printVetor(vetor * v) {
    int tamanho = vetor_tamanho(v);
    printf("\nPalavras (%d):\n", tamanho);

    int i;
    for(i = 0; i < tamanho; i++) {
        printf("#%d - %s\n", i + 1, vetor_elemento(v, i));
    }
}

void trim(char* vec) {
    int n = strlen(vec);

    while(vec[n-1]=='\n' || vec[n-1]=='\r') {
        vec[n-1]=0;
        n--;
    }
}

int main()  {
    vetor * v = vetor_novo();

    int i;
    for(i = 0; i < 5; i++) {
        printf("Insira a %dª palavra: ", i + 1);

        char palavra[NCARS];
        fgets(palavra, NCARS, stdin);
        trim(palavra);

        if(vetor_insere(v, palavra, -1) == -1) {
            printf("Ocorreu um erro!");
            return 1;
        }
    }

    printVetor(v);

    printf("\nInsira a palavra a remover: ");
    char palavra[NCARS];
    fgets(palavra, NCARS, stdin);

    printf("\"%s\"\n", palavra);

    int index = vetor_pesquisa(v, palavra);
    if(index >= 0) {
        vetor_remove(v, index);
        printf("Encontrado e removido!\n");
    } else {
        printf("Não foi encontrado!\n");
    }

    printVetor(v);

    printf("\nOrdenando vetor...");
    if(vetor_ordena(v) == -1) {
        printf("Ocorreu um erro!");
        return 1;
    }

    printVetor(v);

    return 0;
}