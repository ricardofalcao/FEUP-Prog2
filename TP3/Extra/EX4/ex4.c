#include <stdio.h>
#include "vetor.h"
#define NCARS 256

int main() {
    vetor *v = vetor_novo();
    FILE *file;

    file = fopen("IMDB.txt", "r");
    char buffer[NCARS];
    char *linha;

    // Ignoramos a primeira linha
    linha = fgets(buffer, NCARS, file);
    printf("%s", linha);

    int votos;
    float classificacao;
    char *titulo;
    int ano;

    while(fscanf(file, "%d %f", &votos, &classificacao)) {
        

        vetor_insere(v, votos, classificacao, titulo, ano, -1);
    }

    return 0;
}