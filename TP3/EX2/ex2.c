#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lista.h"
#include "vetor.h"
#define NCARS 16
#define ACESSOS 10000

void trim(char* vec) {
    int n = strlen(vec);

    while(vec[n-1] == '\n' || vec[n-1] == '\r') {
        vec[n-1] = 0;
        n--;
    }
}

void inserirNomesV(FILE *file, vetor* v) {
    char buffer[NCARS];
    char *linha;

    while((linha = fgets(buffer, NCARS, file))) {
        trim(linha);

        vetor_insere(v, linha, 0);
    }
}

void inserirNomesL(FILE *file, lista *l) {
    char buffer[NCARS];
    char *linha;

    while((linha = fgets(buffer, NCARS, file))) {
        trim(linha);

        lista_insere(l, linha, lista_inicio(l));
    }
}

void inserirNomesFimV(FILE *file, vetor* v) {
    char buffer[NCARS];
    char *linha;

    while((linha = fgets(buffer, NCARS, file))) {
        trim(linha);

        vetor_insere(v, linha, -1);
    }
}

void inserirNomesFimL(FILE *file, lista *l) {
    char buffer[NCARS];
    char *linha;

    while((linha = fgets(buffer, NCARS, file))) {
        trim(linha);

        lista_insere(l, linha, NULL);
    }
}

void executarAcessosV(vetor *v) {
    int i;
    for(i = 0; i < ACESSOS; i++) {
        int random = rand() % ACESSOS;
        vetor_elemento(v, random);
    }
}

void executarAcessosL(lista *l) {
    int i;
    for(i = 0; i < ACESSOS; i++) {
        int random = rand() % ACESSOS;
        lista_elemento(l, random);
    }
}

void removerElementosV(vetor *v) {
    int length = vetor_tamanho(v);
    int i;

    for(i = 0; i < length; i++) {
        vetor_remove(v, 0);
    }
}

void removerElementosL(lista *l) {
    l_elemento *root;

    while((root = lista_inicio(l))) {
        lista_remove(l, root);
    }
}

void printTempo(char * prefix, clock_t start_t, clock_t end_t) {
    printf("Tempo (%s): %.3f\n", prefix, (double) (end_t - start_t) / CLOCKS_PER_SEC);
}

int main() {
    FILE *file;
    file = fopen("nomes.txt", "r");

    lista *l = lista_nova();
    vetor *v = vetor_novo();

    srand(time(NULL));

    clock_t start_t, end_t;

    // Inserir nomes (1)

    {
        start_t = clock();

        inserirNomesL(file, l);

        end_t = clock();
        printTempo("Inserir Lista", start_t, end_t);

        start_t = clock();

        inserirNomesV(file, v);

        end_t = clock();
        printTempo("Inserir Vetor", start_t, end_t);
    }

    // Acessos (2)

    {
        start_t = clock();

        executarAcessosL(l);

        end_t = clock();
        printTempo("Acessos Lista", start_t, end_t);

        start_t = clock();

        executarAcessosV(v);

        end_t = clock();
        printTempo("Acessos Vetor", start_t, end_t);
    }

    // Remover (3)

    {
        start_t = clock();

        removerElementosL(l);

        end_t = clock();
        printTempo("Remoçoes Lista", start_t, end_t);

        start_t = clock();

        removerElementosV(v);

        end_t = clock();
        printTempo("Remoçoes Vetor", start_t, end_t);
    }

    // Inserir nomes (1)

    {
        start_t = clock();

        inserirNomesFimL(file, l);

        end_t = clock();
        printTempo("Inserir Lista Fim", start_t, end_t);

        start_t = clock();

        inserirNomesFimV(file, v);

        end_t = clock();
        printTempo("Inserir Vetor Fim", start_t, end_t);
    }
    
    lista_apaga(l);
    vetor_apaga(v);
    fclose(file);
    return 0;
}