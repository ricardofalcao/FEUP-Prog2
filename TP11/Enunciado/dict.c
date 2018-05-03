#include "avl.h"

#include <stdio.h>
#include <ctype.h>
#include <string.h>


#define MAX_WORD 256


void downcase (char * str)
{
  if(str == NULL)
    return;

  while(*str != '\0')
  {
    *str = tolower(*str);
    str++;
  }
}

int le_dicionario(FILE * f, arvore_avl *dict) {

  /* alinea 1.1 */
  return 0;
}

char* isola_palavra(char *str, int *len) {

  /* alinea 1.2 */
  return NULL;
}

char* verifica_texto(arvore_avl * dict, char *str, int *len) {

  /* alinea 1.3 */
  return NULL;
}


int main() {
    FILE * f = fopen("dict.txt", "r");
    if(!f) {
        puts("dict.txt nao encontrado!");
        return 1;
    }

    arvore_avl *dict = avl_nova();
    int words = le_dicionario(f, dict);

    printf("Lidas %d palavras\n", words);

    int len=0;
    char *ret = "The quick brown fox ola adeus jumps over the lazy dog foox barz bla";
    while((ret = verifica_texto(dict, ret , &len)) != NULL) {
        char word[MAX_WORD + 1] = {};
        strncpy(word, ret, len);
        printf("Palavra desconhecida: %s\n", word);
        ret += len;
    }
    
    avl_apaga(dict);
    fclose(f);
    return 0;
}
