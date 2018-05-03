#include "avl.h"

#include <stdio.h>
#include <ctype.h>
#include <string.h>


#define MAX_WORD 256

void trim(char * vec) {
    int n = strlen(vec);

    while(vec[n-1] == '\n' || vec[n-1] == '\r') {
        vec[n-1] = 0;
        n--;
    }
}

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
  char str[MAX_WORD];
  int i = 0;

  while(fgets(str, MAX_WORD, f) != NULL) {
    trim(str);
    downcase(str);

    avl_insere(dict, str);
    i++;
  }

  /* alinea 1.1 */
  return i;
}

char* isola_palavra(char *str, int *len) {
  int i = 0;
  while(str[i] == ' ') {
    if(str[i] == '\0') {
      return NULL;
    }

    i++;
  }

  int j = i;
  while(str[j] != ' ' && str[j] != '\0') {
    j++;
  }

  *len = j - i;
  return *len == 0 ? NULL : &str[i];
}

char* verifica_texto(arvore_avl * dict, char *str, int *len) {
  char *_word = str;
  int comprimento = 0;

  while((_word = isola_palavra(_word, &comprimento)) != NULL) {
    char word[MAX_WORD + 1] = {};
    strncpy(word, _word, comprimento);
    downcase(word);

    if(avl_pesquisa(dict, word) == NULL) {
      *len = comprimento;
      return _word;
    }

    _word += comprimento;
  }

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
