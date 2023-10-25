#ifndef TVERIFICACOES_H_
#define TVERIFICACOES_H_

#include "tPacman.h"

/**
 * Dado o ponteiro para uma posicao, verifica se 
 * a mesma eh valida no no tabuleiro
 * \param ponteiro para a posicao e ponteiro para o mapa
 */
bool EstaForaDosLimites(tMapa * mapa, tPosicao * posicao);

/**
 * Dado o ponteiro para uma mapa, verifica se o mapa ou o grid é NULL
 * \param ponteiro para o mapa
 */
bool EhNullGridOuMapa (tMapa * mapa);

#endif