/*****************************************************************/
/*         Trabalho pratico 1 | PROG2 | MIEEC | 2017/18          */
/*****************************************************************/
/*                  NAO ALTERAR ESTE FICHEIRO                    */
/*****************************************************************/

#ifndef CIDADES_H
#define CIDADES_H

#include "vetor.h"

/**
 * coloca num vetor inicialmente vazio a informacao contida em ficheiro binario
 * parametro: nomef nome do ficheiro
 * retorno: apontador para o vetor criado
 * nota: se existe erro na leitura do ficheiro ou vetor nao foi criado retorna NULL
 */
vetor* cidades_load(const char *nomef);


/**
 * coloca num ficheiro binario inicialmente vazio a informacao contida no vetor
 * parametro: nomef nome do ficheiro
 * parametro: vec apontador para o vetor
 * retorno: -1 se aconteceu algum erro ou numero de elementos guardados no ficheiro
 */
int cidades_save(const vetor *vec, const char *nomef);


/**
*  pesquisa um elemento (cidade) diretamente no ficheiro
*  parametro: nomef nome do ficheiro
*  parametro: nomecidade nome da cidade a pesquisar
*  parametro: resultado cidade encontrada (por referencia)
*  retorno: posicao do elemento encontrado no ficheiro ou -1 se ocorrer algum erro ou nao encontrar elemento
*/
int cidades_peek(const char *nomef, const char *nomecidade, cidade *resultado);


/**
*  altera o valor de um elemento (cidade) diretamente no ficheiro, sem garantir que se mantem ordenado
*  parametro: nomef nome do ficheiro
*  parametro: nomecidade nome da cidade a alterar
*  parametro: novo elemento (cidade) a substituir a cidade original
*  retorno: posicao do elemento alterado no ficheiro ou -1 se ocorrer algum erro ou nao encontrar elemento
*/
int cidades_poke(const char *nomef, const char *nomecidade, cidade nova);


/**
*  reordena o vetor de cidades crescentemente, de acordo com criterio especificado
*  parametro: vec apontador para vetor
*  parametro: criterio carater que indica o criterio de ordenacao
*             se 'p', ordena por pais e, em caso de empate, por populacao ;
*             se 'a', ordena por area e, em caso de empate, por populacao
*  retorno: -1 se ocorrer um erro ou 0 se for bem sucedido
*/
int cidades_resort(vetor *vec, char criterio);

/**
procura as cidades similares em populacao a uma cidade especificada
 * parametro: vec apontador para o vetor de cidades
*  parametro: nomecidade nome da cidade referencia
*  parametro: deltapop diferenca maxima (valor absoluto) em populacao relativamente 'a populacao da cidade referencia
*  parametro: nsimilares numero de resultados encontrados (por referencia)
*  retorno: vetor(array) de strings com o nome das cidades encontradas
*           as cidades retornadas mantem a ordem em que estavam guardadas no vetor original
*  nota: se cidade referencia nao existe ou nao encontra cidades similares, retorna NULL
*/
char** cidades_similar (vetor *vec, const char *nomecidade, int deltapop, int *nsimilares);

#endif
