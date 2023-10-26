#ifndef UTILS_H_
#define UTILS_H_

#include "tPacman.h"

typedef enum {
    ESQUERDA = 0,
    CIMA = 1,
    BAIXO = 2,
    DIREITA = 3 
} MOVIMENTOS;

bool EstaForaDosLimites(tMapa * mapa, tPosicao * posicao);

bool EhNullGridOuMapa (tMapa * mapa);

tPosicao * AlteraPosicao(tPosicao * posicao, MOVIMENTOS movimento);

#endif