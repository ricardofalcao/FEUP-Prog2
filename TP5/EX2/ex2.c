#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

int pilha_argumentos(pilha *p, int *arg1, int *arg2) {
    int size = pilha_tamanho(p);
    if(size < 2) {
        return -1;
    }

    *arg2 = pilha_top(p);
    pilha_pop(p);

    *arg1 = pilha_top(p);
    pilha_pop(p);
    return 0;
}

int _calcula_total(char* expressao_rpn) {
    pilha *stack = pilha_nova();
    
    int i = 0, arg1, arg2, calc = -1;
    char c;

    while((c = expressao_rpn[i]) != '\0') {
        switch (c) {
            case '+':  {
                if(pilha_argumentos(stack, &arg1, &arg2) == 0) {
                    pilha_push(stack, arg1 + arg2);
                }

                break;   
            }

            case '-':  {
                if(pilha_argumentos(stack, &arg1, &arg2) == 0) {
                    pilha_push(stack, arg1 - arg2);
                }

                break;   
            }

            case '*':  {
                if(pilha_argumentos(stack, &arg1, &arg2) == 0) {
                    pilha_push(stack, arg1 * arg2);
                }

                break;   
            }

            case '/':  {
                if(pilha_argumentos(stack, &arg1, &arg2) == 0) {
                    pilha_push(stack, arg1 / arg2);
                }

                break;   
            }

            case ' ': {
                if(calc != -1) {
                    pilha_push(stack, calc);
                    calc = -1;
                }

                break;
            }

            default: {
                if(calc == -1) {
                    calc = 0;
                } else {
                    calc *= 10;
                }

                calc += (c - '0');
                break;
            }
        }

        i++;
    }

    int resultado = pilha_top(stack);
    pilha_apaga(stack);

    return resultado;
}

void calcula_total(char* expressao_rpn) {
    printf("\"%s\" = %d\n", expressao_rpn, _calcula_total(expressao_rpn));
}

int main() {
    int i;
    calcula_total("6 1 2 + /");
    calcula_total("20 43 52 + * 5 /");

    return 0;
}