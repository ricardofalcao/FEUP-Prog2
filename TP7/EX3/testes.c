#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
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
    arvore_avl *arv = avl_nova();

    FILE *file = fopen("cidades.txt", "r");

    char str[STRLEN];
    while(fgets(str, STRLEN, file) != NULL) {
        strtok(str, ",");

        char *pais = strtok(NULL, ",");
        trim(pais);

        avl_insere(arv, pais);
    }

    printf("%s - %d\n", "Portugal", avl_pesquisa(arv, "Portugal")->contador);
    printf("%s - %d\n", "Spain", avl_pesquisa(arv, "Spain")->contador);
    printf("%s - %d\n", "Russia", avl_pesquisa(arv, "Russia")->contador);

    return 0;
}