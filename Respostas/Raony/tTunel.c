#include "tTunel.h"
#include "tPosicao.h"

/**
 * Cria o tunel dinamicamente
 * \param linhaAcesso1 linha da posição do acesso 1 do túnel
 * \param colunaAcesso1 coluna da posição do acesso 1 do túnel
 * \param linhaAcesso2 linha da posição do acesso 2 do túnel
 * \param colunaAcesso2 coluna da posição do acesso 2 do túnel
 */
tTunel* CriaTunel(int linhaAcesso1, int colunaAcesso1, int linhaAcesso2, int colunaAcesso2) {
    tPosicao * posicao1 = (tPosicao *) malloc (sizeof(tPosicao));
    posicao1->linha = linhaAcesso1;
    posicao1->coluna = colunaAcesso1;

    tPosicao * posicao2 = (tPosicao *) malloc (sizeof(tPosicao));
    posicao2->linha = linhaAcesso2;
    posicao2->coluna = colunaAcesso2;

    tTunel * tunel = (tTunel *) malloc(sizeof(tTunel));
    tunel->acesso1 = posicao1;
    tunel->acesso2 = posicao2;
    return tunel;
}

/**
 * Verifica se entrou no túnel pela posição
 * \param tunel tunel
 * \param posicao posição
 */
bool EntrouTunel(tTunel* tunel, tPosicao* posicao) {
    if (posicao->coluna == tunel->acesso1->coluna || posicao->coluna == tunel->acesso2->coluna &&
        posicao->linha == tunel->acesso1->linha || posicao->linha == tunel->acesso2->linha) return 1;
    return 0;
}

/**
 * Atualiza a posição para o final do túnel
 * \param tunel tunel
 * \param posicao posição
 */
void LevaFinalTunel(tTunel* tunel, tPosicao* posicao) {
    posicao->coluna = tunel->acesso2->coluna;
    posicao->linha = tunel->acesso2->linha;
}

/**
 * Libera o espaço alocado para a estrutura tTunel
 * 
 * \param tunel tunel
 */
void DesalocaTunel(tTunel* tunel) {
    DesalocaPosicao(tunel->acesso1);
    DesalocaPosicao(tunel->acesso2);
    free(tunel);
}
