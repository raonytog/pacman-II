#ifndef TFANTASMA_H_
#define TFANTASMA_H_

#include "tPosicao.h"
#include "tMapa.h"
#include "tPacman.h"

#define MAX_GHOST 4

#define LEFT_GHOST 'B'  //fantasma horizontal   - inicio: esquerda
#define RIGHT_GHOST 'C'  //fantasma horizontal   - inicio: direita
#define DOWN_GHOST 'I'  //fantasma vertical     - inicio: baixo
#define UP_GHOST 'P'  //fantasma vertical     - inicio: cima

#define COMIDA '*'
#define PORTAL '@'
#define PAREDE '#'
#define PACMAN '>'
#define VAZIO ' '

typedef struct tFantasma {
    int presenteMapa;
    int gulaFantasmagorica;
    int dx;
    int dy;
    tPosicao * posicao;
    tPosicao * posicaoAntiga;
} tFantasma;

/**
*  Verifica se o item esta presente no mapa
* \param ponteiro para o mapa, caractere do item a ser encontrado
*/
bool ExisteFantasmaMapa (tMapa * mapa, char item);


tPosicao * ObtemPosicaoAtualFantasma (tFantasma * fantasma);


tPosicao * ObtemPosicaoAntigaFantasma (tFantasma * fantasma);


tFantasma * CriaFantasma(tMapa * mapa, char simoblogia_fantasma);


void MoveFantasmas (tFantasma * baixo, tFantasma * cima, tFantasma * esquerda, tFantasma * direita, tMapa * mapa);


int EstaPresenteFantasma (tFantasma * fantasma);

void DesalocaFantasma(tFantasma * fantasma);

#endif