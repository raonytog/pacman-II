#ifndef TFANTASMA_H_
#define TFANTASMA_H_

#include "tPosicao.h"
#include "tMapa.h"
#include "tPacman.h"

#define MAX_GHOST 4

#define LEFT_GHOST 'B'   //fantasma horizontal   - inicio: esquerda
#define RIGHT_GHOST 'C'  //fantasma horizontal   - inicio: direita
#define DOWN_GHOST 'I'   //fantasma vertical     - inicio: baixo
#define UP_GHOST 'P'     //fantasma vertical     - inicio: cima

//novos fantasmas
#define HORIZONTAL_GHOST 'H' // inicio direita
#define VERTICAL_GHOST 'V' // inciio - cima

#define COMIDA '*'
#define PORTAL '@'
#define PAREDE '#'
#define PACMAN '>'
#define VAZIO ' '

typedef struct tFantasma {
    int presenteMapa;
    int gulaFantasmagorica;
    int comeuParede;
    int dx;
    int dy;
    tPosicao * posicao;
    tPosicao * posicaoAntiga;
} tFantasma;

/**
*  Verifica se o fantasma existe no mapa
* \param mapa mapa
* \param fantasma fantasma a ser verificado
*/
bool ExisteFantasmaMapa (tMapa * mapa, char item);

bool ComeuParede (tFantasma * fantasma);

/**
*  Verifica se na posicao passada o item esta presente
* \param mapa mapa
* \param posicao posicao do item
* \param item item a verificar se existe no mapa
*/
bool ExisteItemPosicao (tMapa * mapa, tPosicao * posicao, char item);

/**
*  Verifica se o fantasma existe
* \param fantasma fantasma a verificar presenca
*/
bool EstaPresenteFantasma (tFantasma * fantasma);

/**
*  Retorna a posicao atual do fantasma
* \param fantasma fantasma
*/
tPosicao * ObtemPosicaoAtualFantasma (tFantasma * fantasma);

/**
*  Retorna a posicao antiga do fantasma
* \param fantasma fantasma
*/
tPosicao * ObtemPosicaoAntigaFantasma (tFantasma * fantasma);

/**
*  Cria fantasma caso esteja presente no mapa
* \param mapa mapa
* \param simbologia_fantasma sprit do fantasma
*/
tFantasma * CriaFantasmaPresente(tMapa * mapa, char simoblogia_fantasma);

/**
*  Move fantasmas presentes no mapa
* \param baixo fantasma que move para baixo (inicialmente)
* \param cima fantasma que move para cima (inicialmente)
* \param esquerda fantasma que move para esquerda (inicialmente)
* \param direita fantasma que move para direita (inicialmente)
* \param mapa mapa
* \param pacman pacman
*/
void MoveFantasmas (tFantasma * baixo, tFantasma * cima, tFantasma * esquerda, 
                    tFantasma * direita, tFantasma * horizontal, tFantasma * vertical, 
                    tMapa * mapa, tPacman * pacman);


void MataFantasma (tFantasma * fantasma);

/**
*  Desaloca fantasma presente (fantasma diferente de NULL)
* \param fantasma fantasma
*/
void DesalocaFantasmaPresentes (tFantasma * fantasma);

#endif