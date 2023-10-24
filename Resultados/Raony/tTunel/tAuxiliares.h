#ifndef TAUXILIARES_H_
#define TAUXILIARES_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tMapa.h"
#include "tPosicao.h"
#include "tTunel.h"


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