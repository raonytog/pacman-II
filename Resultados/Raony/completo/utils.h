#ifndef UTILS_H_
#define UTILS_H_

#include "tPacman.h"
#include "tMapa.h"
#include "tPosicao.h"
#include "tMovimento.h"
#include "tTunel.h"

#define VIVO 1 
#define MORTO 0 

#define COMIDA '*'
#define PORTAL '@'
#define PAREDE '#'
#define PACMAN '>'

typedef enum {
    ESQUERDA = 0,
    CIMA = 1,
    BAIXO = 2,
    DIREITA = 3 
} MOVIMENTOS;

/**
 * Dado o ponteiro para uma posicao, verifica se 
 * a mesma eh valida no no tabuleiro
 * \param ponteiro para a posicao
 * \param ponteiros para o mapa
 */
bool EstaForaDosLimites(tMapa * mapa, tPosicao * posicao);

/**
 * Dado o ponteiro para uma mapa, verifica se o mapa ou o grid é NULL
 * \param ponteiro para o mapa
 */
bool EhNullGridOuMapa (tMapa * mapa);


/**
 * Gera o arquvio de inicializacao
 * \param ponteiro para o mapa
 * \param ponteiro para o pacman
*/
void GeraArquivoInicializacao (tMapa * mapa, tPacman * pacman);

tPosicao * AlteraPosicao(tPosicao * posicao, MOVIMENTOS movimento);

#endif