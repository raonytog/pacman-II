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

bool EstaForaDosLimites(tMapa * mapa, tPosicao * posicao);

bool EhNullGridOuMapa (tMapa * mapa);

tPosicao * AlteraPosicao(tPosicao * posicao, MOVIMENTOS movimento);

#endif