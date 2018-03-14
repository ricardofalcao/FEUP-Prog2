/*****************************************************************/
/*         Trabalho pratico 1 | PROG2 | MIEEC | 2017/18          */
/*****************************************************************/
/*                    FUNCOES A IMPLEMENTAR                      */
/*****************************************************************/

#include "cidades.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

short vetorvalido(const vetor *vet) {
  return vet != NULL && vet->elementos != NULL ? 1 : 0;
}

short strvalido(const char *val) {
  return val != NULL && val[0] != '\0' ? 1 : 0;
}

vetor* cidades_load(const char *nomef)
{
  if(!strvalido(nomef)) {
    return NULL;
  }

  vetor* vtr = vetor_novo();
  if(vtr == NULL) {
    return NULL;
  }

  FILE *file = fopen(nomef, "rb");
  if(file == NULL) {
    return NULL;
  }

  cidade cache[1];
  while(fread(cache, sizeof(cidade), 1, file) == 1) {
      if(vetor_insere(vtr, *cache, -1) == -1) {
        vetor_apaga(vtr);
        fclose(file);
        return NULL;
      } 
  }

  fclose(file);
  return vtr;
}

int cidades_save(const vetor *vec, const char *nomef)
{
  if(!vetorvalido(vec) || !strvalido(nomef)) {
    return -1;
  }

  FILE *file = fopen(nomef, "wb");
  if (file == NULL) {
    return -1;
  }

  int tamanho = vec->tamanho;
  int written = fwrite(vec->elementos, sizeof(cidade), tamanho, file);

  fclose(file);
  return written == tamanho ? tamanho : -1;
}

int cidades_peek(const char *nomef, const char *nomecidade, cidade *resultado)
{
  if(!strvalido(nomef) || !strvalido(nomecidade) || resultado == NULL) {
    return -1;
  }

  FILE *file = fopen(nomef, "rb");
  if(file == NULL) {
    return -1;
  }

  cidade cache[1];
  int position = 0;

  while(fread(cache, sizeof(cidade), 1, file) == 1) {
    if(strcmp(cache->nome, nomecidade) == 0) {
      *resultado = *cache;
      fclose(file);
      return position;
    }

    position++;
  }

  fclose(file);
	return -1;
}

int cidades_poke(const char *nomef, const char *nomecidade, cidade nova)
{
  if(!strvalido(nomef) || !strvalido(nomecidade)) {
    return -1;
  }

  FILE *file = fopen(nomef, "r+b");
  if(file == NULL) {
    return -1;
  }

  cidade cache[1];
  int position = 0;

  while(fread(cache, sizeof(cidade), 1, file) == 1) {
    if(strcmp(cache->nome, nomecidade) == 0) {

      fseek(file, -1 * sizeof(cidade), SEEK_CUR);
      fwrite(&nova, sizeof(cidade), 1, file);
      fseek(file, 0, SEEK_CUR);

      fclose(file);
      return position;
    }

    position++;
  }

  fclose(file);
	return -1;
}

int cidades_resort(vetor *vec, char criterio)
{
  if(!vetorvalido(vec)) {
    return -1;
  }

  if(criterio != 'p' && criterio != 'a') {
    return -1;
  }

  int size = vetor_tamanho(vec);
  int i, j;
 
  for (i = 0 ; i < (size - 1); i++) {
    for (j = 0 ; j < (size - i - 1); j++) {
      const cidade cid1 = *vetor_elemento(vec, j);
      const cidade cid2 = *vetor_elemento(vec, j + 1);

      short trocar = 0;

      // Comparador
      if(criterio == 'a') {
        if(cid1.area > cid2.area) {
          trocar = 1;

        } else if(cid1.area == cid2.area) {
          if(cid1.populacao > cid2.populacao) {
            trocar = 1;
          }

        }

      } else {
        int cmp = strcmp(cid1.pais, cid2.pais);

        if(cmp > 0) {
          trocar = 1;

        } else if(cmp == 0) {
          if(cid1.populacao > cid2.populacao) {
            trocar = 1;
          }
          
        }
      }

      if (trocar) {
        vetor_atribui(vec, j, cid2);
        vetor_atribui(vec, j + 1, cid1);
      }
    }
  }

  return -1;
}

char** cidades_similar (vetor *vec, const char *nomecidade, int deltapop, int *nsimilares)
{
  if(!vetorvalido(vec) || !strvalido(nomecidade) || nsimilares == NULL){
    return NULL;
  }

  if(deltapop < 0) {
    deltapop = -deltapop;
  }

  *nsimilares = 0;

  int i;
  const cidade* root;

  for(i = 0; i < vetor_tamanho(vec); i++) {
    const cidade* cid = vetor_elemento(vec, i);
    if(strcmp(cid->nome, nomecidade) == 0) {
      root = cid;
      break;
    }
  }

  if(root == NULL) {
    return NULL;
  }

  char **output = malloc(vetor_tamanho(vec) * sizeof(root->nome));
  if(output == NULL) {
    return NULL;
  }

  for(i = 0; i < vetor_tamanho(vec); i++) {
    const cidade* cid = vetor_elemento(vec, i);
    if(cid == root) {
      continue;
    }

    int aux = root->populacao - cid->populacao;

    if(aux < 0) {
      aux = -aux;
    }

    if(aux <= deltapop) {
      output[*nsimilares] = strdup(cid->nome);
      (*nsimilares)++;
    }
  }

  output = realloc(output, *nsimilares * sizeof(root->nome));
  return output;
}
