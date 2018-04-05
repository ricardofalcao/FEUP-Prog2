#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

int main() {
    arvore_avl *arv = avl_nova();

    char *elementos[] = {
        "G", "C", "A", "F", "L", "J", "V", "M", "N", "O"
    };

    int i;
    for(i = 0; i < 10; i++) {
        avl_insere(arv, elementos[i]);
    }

    printf("%d\n\n", avl_altura(arv->raiz));

    avl_imprime(arv);

    return 0;
}