#include <stdio.h>
#include "letras.h"

int main() {
  int letras[26];
  int total = 0;

  int i;
  for(i = 0; i < 26; i++) {
    letras[i] = 0;
  }

  // 0 - a
  // 1 - b
  // 2 - c
  FILE *file;
  file = fopen("lusiadas.txt", "r");

  int c = getc(file);
  while(c > 0) {
    // processar as letras
    int c2 = c;
    c2 = tirarAcentos(c2);
    c2 = tirarCedilhas(c2);
    c2 = tornarMinuscula(c2);

    c = getc(file);
    if(!letraNormal(c2)) {
      continue;
    }
    // c já ta simples
    letras[c2 - 97] = letras [c2 - 97] + 1;
    total++;
  }

  for(i = 0; i < 26; i++) {
    char letra = (char) (i + 97);
    float proporcao = (letras[i] / (float) total) * 100;
    printf("Letra %c = %.2f%%\n", letra, proporcao);
  }

  return 0;
}
