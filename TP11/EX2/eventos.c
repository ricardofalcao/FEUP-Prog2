#include "heap.h"

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE 256
#define MAX_HEAP 256

int pop_number(char *str) {
    int i = strlen(str) - 1;
    while(i >= 0 && isspace(str[i])) i--;

    if(i < 0)
        return -1;

    while(i >= 0 && !isspace(str[i])) i--;
    i++;

    int ret = atoi(str + i);
    str[i] = 0;

    return ret;
}


int le_eventos(FILE *f, heap *eventos_agendados) {
    char str[MAX_LINE];
    int i = 0;

    while(fgets(str, MAX_LINE, f) != NULL) {
        int number = pop_number(str);
        heap_insere(eventos_agendados, str, number);
        i++;
    }

    return i;
}

int processa_tempo(int tempo, heap *eventos_agendados, heap *eventos_espera) {
    elemento *el;
    int i = 0;

    while((el = eventos_agendados->elementos[RAIZ]) != NULL && el->prioridade <= tempo) {
        char *str = el->valor;
        int prioridade = pop_number(str);

        heap_insere(eventos_espera, str, -prioridade);
        heap_remove(eventos_agendados);
        i++;
    }

    return i;
}

char* proximo_evento(heap *eventos_espera, int *duracao) {
    char *str = heap_remove(eventos_espera);
    *duracao = pop_number(str);

    return str;
}


void processa_eventos(heap *eventos_agendados){
    heap * eventos_espera = heap_nova(MAX_HEAP);
    int time = 0;

    while(eventos_espera->tamanho || eventos_agendados->tamanho)
    {   
        processa_tempo(time, eventos_agendados, eventos_espera);

        if(eventos_espera->tamanho) {
            char * evento;
            int duracao;
            evento = proximo_evento(eventos_espera, &duracao);
            printf("@%d: %s (duracao: %d)\n", time, evento, duracao);
            time += duracao;
            free(evento);
        }
        else
            time = eventos_agendados->elementos[1]->prioridade;
    }

    heap_apaga(eventos_espera);
}


int main() {
    FILE *f;
    int eventos;
    heap *eventos_agendados;

    f = fopen("eventos.txt", "r");
    if(!f) {
        puts("eventos.txt nao encontrado!");
        return 1;
    }

    eventos_agendados = heap_nova(MAX_HEAP);

    eventos = le_eventos(f, eventos_agendados);
    printf("Lidos %d eventos\n", eventos);
    heap_imprime(eventos_agendados, 1);
    printf("\n");
    processa_eventos(eventos_agendados);

    heap_apaga(eventos_agendados);
    fclose(f);
    return 0;
}
