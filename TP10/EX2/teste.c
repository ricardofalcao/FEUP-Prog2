#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabdispersao.h"
#define USERLEN 16
#define PASSLEN 32

void trim(char* vec) {
    int n = strlen(vec);

    while(vec[n-1] == '\n' || vec[n-1] == '\r') {
        vec[n-1] = 0;
        n--;
    }
}

int main() {
    FILE *file = fopen("passwords.txt", "r");

    tabela_dispersao *tab = tabela_nova(8, hash_djbm);

    char str1[USERLEN], str2[PASSLEN];
    while(fscanf(file, "%s %s", str1, str2) == 2) {
        trim(str1);
        trim(str2);
        tabela_adiciona(tab, str1, str2);
    }

    fclose(file);

    while(1) {
        printf("Insira o username: ");
        fgets(str1, USERLEN, stdin);
        trim(str1);

        while(1) {
            printf("Insira a password: ");
            fgets(str2, PASSLEN, stdin);
            trim(str2);

            const char *str3 = tabela_valor(tab, str1);
            if(str3 == NULL) {
                printf("Utilizador nao encontrado.\n");
                break;
            }

            if(strcmp(str2, str3) == 0) {
                printf("Autenticado!\n");
                break;
            }

            printf("Password inválida!\n");
        }
    }

    return 0;
}