#include <stdio.h>
#include <stdlib.h>

int * criarVetor(int size) {
    return malloc(sizeof(int) * size);
}

int * resizeVetor(int * vetor, int size, int delta) {
    return realloc(vetor, size + delta);
}

void printVetor(const char * prefix, const int * vetor, int size) {
    if(vetor == NULL) {
        return;
    }

    printf("%s: [ ", prefix);
    
    int i;
    for(i = 0; i < size; i++) {
        printf("%d ", vetor[i]);
    }

    printf("]\n");
}

int main() {
    int n;

    printf("Número de elementos? ");
    scanf("%d", &n);

    int *values = criarVetor(n);

    int *pares = NULL;
    int _pares = 0;

    int *impares = NULL;
    int _impares = 0;

    int i, value;
    for(i = 0; i < n; i++) {
        printf("Introduza o %dº elemento: ", i + 1);
        scanf("%d", &value);
        values[i] = value;

        if(value % 2 == 0) {

            if(pares == NULL) {
                pares = criarVetor(1);
                pares[0] = value;
            } else {
                pares[_pares] = value;
            }

            _pares++;

        } else {

            if(impares == NULL) {
                impares = criarVetor(1);
                impares[0] = value;
            } else {
                impares[_impares] = value;
            }

            _impares++;

        }
    }

    printVetor("Vetor original", values, n);
    printVetor("Números pares", pares, _pares);
    printVetor("Números impares", impares, _impares);

    return 0;
}