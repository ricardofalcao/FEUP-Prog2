#include <stdio.h>
#include <string.h>

int main() {
  FILE *file;
  file = fopen("pagina.html", "r");

  char prefix[] = "<a href=\"";

  int c = getc(file);
  while(c > 0) {
    int i;
    int success = 1;

    for(i = 0; i < strlen(prefix); i++) {
      if(c == (int) prefix[i]) {
        c = getc(file);
      } else {
        success = 0;
        break;
      }
    }

    if(!success) {
      if(i == 0) {
        c = getc(file);
      }

      continue;
    }

    char link[100];
    int aux = 0;

    while(c != '"')  {
      link[aux++] = c;
      c = getc(file);
    }

    link[aux] = '\0';

    getc(file);
    c = getc(file);

    char nome[40];
    aux = 0;

    while(c != '<') {
      nome[aux++] = c;
      c = getc(file);
    }

    nome[aux] = '\0';
    printf("%s - %s\n", nome, link);
  }

  return 0;
}
