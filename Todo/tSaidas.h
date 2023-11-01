#ifndef TSAIDAS_H_
#define TSAIDAS_H_

#include "tPosicao.h"
#include "tMovimento.h"
#include "tMapa.h"
#include "tPacman.h"

/**
 * Gera um arquivo de inicialização com as informações do mapa e do Pac-Man.
 * 
 * @param mapa Ponteiro para a estrutura do mapa.
 * @param pacman Ponteiro para a estrutura do Pac-Man.
 */
void GeraArquivoInicializacao (tMapa * mapa, tPacman * pacman);

#endif