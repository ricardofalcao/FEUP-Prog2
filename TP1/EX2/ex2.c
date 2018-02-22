#include <stdio.h>
#include <string.h>

int main() {
  char generos[80][20];

  FILE *file;
  file = fopen("generos.txt", "r");

  int id;
  char genero[20];
  while(fscanf(file, "%d %s", &id, genero) > 0) {
    strcpy(generos[id], genero);
  }

  file = fopen("musica.mp3", "rb");

  fseek(file, -128, SEEK_END);

  char tag[4];

  fread(tag, sizeof(char), 3, file);
  tag[3] = '\0';

  if(strcmp(tag, "TAG") != 0) {
    printf("Nao foi possivel ler o ficheiro mp3. Tripou. %s\n", tag);
    return 0;
  }

  char titulo[31];
  fread(titulo, sizeof(char), 30, file);
  titulo[30] = '\0';

  char artista[31];
  fread(artista, sizeof(char), 30, file);
  artista[30] = '\0';

  char album[31];
  fread(album, sizeof(char), 30, file);
  album[30] = '\0';

  char ano[5];
  fread(ano, sizeof(char), 4, file);
  ano[4] = '\0';

  fseek(file, 28, SEEK_CUR);

  char data[3];
  fread(data, sizeof(data), 1, file);

  char numero = '0';

  if(data[0] == '0') {
    numero = data[1];
  }

  printf("Titulo - %s\n", titulo);
  printf("Artista - %s\n", artista);
  printf("Album - %s\n", album);
  printf("Ano - %s\n", ano);
  printf("Numero - %d\n", data[0] == '0' ? 0 : data[1]);
  printf("Genero - %s\n", generos[data[2]]);

  return 0;
}
