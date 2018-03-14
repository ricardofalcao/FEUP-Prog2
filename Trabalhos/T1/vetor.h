/*****************************************************************/
/*         Trabalho pratico 1 | PROG2 | MIEEC | 2017/18          */
/*****************************************************************/
/*                  NAO ALTERAR ESTE FICHEIRO                    */
/*****************************************************************/

#ifndef VETOR_H

#define MAXSTR 50

/**
* registo para armazenar cada elemento (uma cidade neste caso)
*/
typedef struct
{
  char nome[MAXSTR];
  char pais[MAXSTR];
  int populacao;
  int area;     

} cidade;

/**
* este registo contem um vetor de elementos, um contador do tamanho e outro para a capacidade
*/
typedef struct
{
  /** numero de elementos do vetor */
  int tamanho;

  /** capacidade do vetor */
  int capacidade;

  /** array de elementos (cidades) armazenados */
  cidade* elementos;

} vetor;

/**
*  cria um novo vetor com tamanho 0 e capacidade 0
*  retorno: apontador para o vetor criado
*  nota: se vetor nao foi criado retorna NULL
*/
vetor* vetor_novo();

/**
*  elimina um vetor, libertando toda a memoria ocupada
*  parametro: vec apontador para vetor
*  nota: se vec = NULL retorna sem fazer nada
*/
void vetor_apaga(vetor *vec);

/**
*  indica o o numero de elementos do vetor
*  parametro: vec apontador para vetor
*  retorno: -1 se ocorrer algum erro ou numero de elementos do vetor
*/
int vetor_tamanho(vetor *vec);

/**
*  retorna o elemento armazenado na posicao especificada
*  parametro: vec apontador para vetor
*  parametro: pos indice do elemento
*  retorno: apontador para o elemento (cidade) na posicao correspondente
*  nota: se ocorrer algum erro retorna NULL (p.ex. se valor pos indicar uma posicao invalida)
*/
const cidade* vetor_elemento(vetor *vec, int pos);

/**
*  insere um elemento na posicao especificada
*  parametro: vec apontador para vetor
*  parametro: cidade1 elemento (cidade) a inserir
*  parametro: pos indice do vetor onde se pretende inserir a cidade, se pos=tamanho ou pos=-1 insere no fim do vetor
*  retorno: -1 se ocorrer algum erro (p.ex. se valor pos indicar uma posicao invalida) ou o valor de pos se bem sucedido
*  nota: se a capacidade nao for suficiente para guardar novo elemento, devera ser aumentada para 2x em relacao a capacidade anterior; inicialmente aumenta para capacidade 1
*/
int vetor_insere(vetor *vec, cidade cidade1, int pos);

/**
*  remove o elemento da posicao especificada
*  parametro: vec apontador para vetor
*  parametro: pos posicao
*  retorno: -1 se ocorrer algum erro (p.ex. se valor pos indicar uma posicao invalida) ou 0 se bem sucedido
*/
int vetor_remove(vetor* vec, int pos);

/**
*  atribui o valor especificado a uma posicao
*  parametro: vec apontador para vetor
*  parametro: pos posicao onde colocar elemento
*  parametro: cidade1 elemento (cidade) a colocar na posicao pos do vetor
*  retorno: -1 se ocorrer algum erro (p.ex. se valor pos indicar uma posicao invalida) ou pos se bem sucedido
*/
int vetor_atribui(vetor *vec, int pos, cidade cidade1);

#define VETOR_H
#endif
