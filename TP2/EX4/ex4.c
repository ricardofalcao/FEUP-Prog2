#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vetor.h"
#define NCARS 20

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

    vetor * v2 = vetor_novo();
    for(i = 0; i < 5; i++) {
        vetor_insere(v2, "extra", -1);
    }

    v = vetor_concatena(v, v2);

    printVetor(v);
    
    if(vetor_inverte(v) == -1) {
        printf("Ocorreu um erro!");
        return 1;
    }

    printVetor(v);

    vetor_baralha(v);

    printVetor(v);

    vetor_apaga(v);
    vetor_apaga(v2);

    return 0;
}