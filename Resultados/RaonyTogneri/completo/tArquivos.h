#ifndef TARQUIVOS_H_
#define TARQUIVOS_H_

#include "tMapa.h"
#include "tPacman.h"

#define ESQUERDA 'a'
#define DIREITA 'd'
#define BAIXO 's'
#define CIMA 'w'

#define QTD_MOV_DIFERENTE 4

typedef struct {
    int qtdFrutasComidas;
    int qtdColisoes;
    int qtdUsado;
    char movimento;
} tAcao;

void GeraArquivoInicializacao (tMapa * mapa, tPacman * pacman);

void GeraResumoPacman (tPacman * pacman);

void GeraEstatisticaPacman (tPacman * pacman);

void GeraRankingPacman (tPacman * pacman);

void GeraArquivosInformativos(tPacman * pacman);

int OrdenaRanking (tAcao acao1, tAcao acao2);

int CriterioColisao (tAcao acao1, tAcao acao2);

int CriterioUso(tAcao acao1, tAcao acao2);

int CriterioAlfabetico (tAcao acao1, tAcao acao2);

#endif