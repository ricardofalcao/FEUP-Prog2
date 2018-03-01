#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lista.h"
#define NCARS 80

void trim(char* vec) {
    int n = strlen(vec);

    while(vec[n-1] == '\n' || vec[n-1] == '\r') {
        vec[n-1] = 0;
        n--;
    }
}

lista *lerLista(FILE *file) {
    lista *l = lista_nova();

    char buffer[NCARS];
    char *linha;

    while((linha = fgets(buffer, NCARS, file))) {
        trim(linha);
        lista_insere(l, linha, NULL);
    }

    return l;
}

void printLista(lista *l) {
    l_elemento *root = lista_inicio(l);

    int i;
    while(root) {
        printf("Pos %d -> %s\n", i, root->str);
        root = root->proximo;
        i++;
    }
}

int main() {
    FILE *file;
    file = fopen("arquivo.txt", "r");
    lista *l = lerLista(file);

    int length = lista_tamanho(l);
    printf("Foram carregados %d jogos:\n", length);

    printLista(l);

    // PS2

    lista *ps2 = lista_pesquisa_substring(l, "PS2");
    l_elemento *root = lista_inicio(ps2);

    while(root) {
        l_elemento *elemento = lista_pesquisa(l, root->str, LISTA_INICIO);
        
        if(elemento) {
            lista_remove(l, elemento);
        }

        root = root->proximo;
    }

    length = lista_tamanho(l);
    printf("\nApos a remoçao dos jogos da PS2 a lista tem %d jogos.\n", length);
    lista_apaga(ps2);

    //  OLDIES
    fclose(file);
    file = fopen("oldies.txt", "r");

    lista *oldies = lerLista(file);
    length = lista_tamanho(oldies);

    printf("\nForam carregados %d jogos antigos:\n", length);
    printLista(oldies);

    l = lista_concatena(l, oldies);
    length = lista_tamanho(l);

    printf("\nApos a concatenaçao, existem %d jogos na litsa:\n", length);
    printLista(l);

    if(lista_ordena(l) == -1) {
        printf("Erro ao ordenar a lista!");
    } else {
        printf("Lista ordenada:");
        printLista(l);
    }

    char *jogo = "Duke Nukem (PS3)";
    
    int index = 0;
    int found = 0;
    root = lista_inicio(l);

    while(root) {
        if(strcmp(jogo, root->str) == 0) {
            found = 1;
            break;
        }

        root = root->proximo;
        index++;
    }

    if(found) {
        printf("O jogo %s encontra-se na posicao %d.\n", jogo, index);
    } else {
        printf("O jogo %s nao se encontra na lista.\n", jogo);
    }

    jogo = "Minesweeper (PC)";
    index = lista_insere_ordenada(l, jogo);
    printf("O jogo %s foi inserido na posicao %d.\n", jogo, index);
    printLista(l);

    lista_apaga(l);
    fclose(file);

    return 0;
}