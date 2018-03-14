/*****************************************************************/
/*          Biblioteca vetor | PROG2 | MIEEC | 2017/18           */
/*****************************************************************/

#ifndef VETOR_H


/**
* registo para armazenar cada elemento (apenas uma string neste caso)
*/
typedef struct
{
  int votos;
  float classificacao;
  char *titulo;
  int ano;

} v_elemento;

/**
* este registo contem um vetor de elementos, um contador do tamanho e outro para a capacidade
*/
typedef struct
{
  /** numero de elementos do vetor */
  int tamanho;

  /** capacidade do vetor */
  int capacidade;

  /** array de elementos armazenados */
  v_elemento* elementos;

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
*  insere um elemento na posicao especificada
*  parametro: vec apontador para vetor
*  parametro: valor string a inserir
*  parametro: pos indice do elemento onde se pretende inserir a string, se pos=tamanho ou pos=-1 insere no fim do vetor
*  retorno: -1 se ocorrer algum erro (p.ex. se valor pos indicar uma posicao invalida) ou o valor de pos se bem sucedido
*  nota: se a capacidade nao for suficiente para guardar novo elemento, devera ser aumentada para 2x em relacao a capacidade anterior; inicialmente aumenta para capacidade 1
*/
int vetor_insere(vetor *vec, int votos, float classificacao, const char* titulo, int ano, int pos);

/**
*  devolve a posicao do elemento especificado
*  parametro: vec apontador para vetor
*  parametro: str string pretendida
*  retorno: posicao do elemento ou -1 se ocorrer algum erro ou nao encontrar elemento
*/
int vetor_pesquisa(vetor *vec, const char* str);

/**
*  ordena um vetor por ordem alfabetica
*  parametro: vec apontador para vetor
*  retorno: -1 se ocorrer um erro ou 0 se for bem sucedido
*/
int vetor_ordena(vetor *vec);

#define VETOR_H
#endif
