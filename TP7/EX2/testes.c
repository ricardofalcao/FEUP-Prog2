#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "bst.h"
#include "avl.h"
#define STRLEN 128

void trim(char* vec) {
    int n = strlen(vec);

    while(vec[n-1] == '\n' || vec[n-1] == '\r') {
        vec[n-1] = 0;
        n--;
    }
}

int main() {
    clock_t inicio, fim;
    double tempo;
    inicio = clock();

    arvore_avl *arv = avl_nova();

    FILE *file = fopen("cidades_sorted.txt", "r");

    char str[STRLEN];
    while(fgets(str, STRLEN, file) != NULL) {
        trim(str);
        avl_insere(arv, str);
    }

    printf("%d\n", avl_altura(arv->raiz));

    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("tempo em segundos: %lf\n", tempo);
    return 0;
}