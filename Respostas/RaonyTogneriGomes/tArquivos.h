#ifndef TARQUIVOS_H_
#define TARQUIVOS_H_

#include "tMapa.h"
#include "tPacman.h"

#define ESQUERDA 'a'
#define DIREITA 'd'
#define BAIXO 's'
#define CIMA 'w'

#define QTD_MOV_DIFERENTE 4

/* estrutura que trata cada acao para o ranking*/
typedef struct {
    int qtdFrutasComidas;
    int qtdColisoes;
    int qtdUsado;
    char movimento;
} tAcao;


/**
 * Gera arquivo de inicializacao
 * \param mapa mapa
 * \param pacman pacman
 */
void GeraArquivoInicializacao (tMapa * mapa, tPacman * pacman);

/**
 * Gera arquivo de resumo
 * \param pacman pacman
 */
void GeraResumoPacman (tPacman * pacman);

/**
 * Gera arquivo de estatistica
 * \param pacman pacman
 */
void GeraEstatisticaPacman (tPacman * pacman);

/**
 * Gera arquivo de ranking
 * \param pacman pacman
 */
void GeraRankingPacman (tPacman * pacman);

/**
 * Gera os arquivos de resumo, ranking, estatisticas e trilha 
 * \param pacman pacman
 */
void GeraArquivosInformativos(tPacman * pacman);

/**
 * Ordena ranking a partir dos criterios
 * \param acao1 acao 1
 * \param acao2 acao 2
 */
int OrdenaRanking (tAcao acao1, tAcao acao2);

/**
 * Ordena a partir de colisao
 * \param acao1 acao 1
 * \param acao2 acao 2
 */
int CriterioColisao (tAcao acao1, tAcao acao2);

/**
 * Ordena a partir do uso
 * \param acao1 acao 1
 * \param acao2 acao 2
 */
int CriterioUso(tAcao acao1, tAcao acao2);

/**
 * Ordena a partir da ordem alfabetica
 * \param acao1 acao 1
 * \param acao2 acao 2
 */
int CriterioAlfabetico (tAcao acao1, tAcao acao2);

#endif