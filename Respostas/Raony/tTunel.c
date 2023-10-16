#include "tTunel.h"

tTunel* CriaTunel(int linhaAcesso1, int colunaAcesso1, int linhaAcesso2, int colunaAcesso2) {
    tPosicao * posicao1 = CriaPosicao(linhaAcesso1, colunaAcesso1);
    tPosicao * posicao2 = CriaPosicao(linhaAcesso2, colunaAcesso2);

    tTunel * tunel = (tTunel *) malloc(sizeof(tTunel));
    tunel->acesso1 = posicao1;
    tunel->acesso2 = posicao2;
    return tunel;
}

bool EntrouTunel(tTunel* tunel, tPosicao* posicao) {
    if (posicao->coluna == tunel->acesso1->coluna || 
        posicao->coluna == tunel->acesso2->coluna &&
        posicao->linha == tunel->acesso1->linha || 
        posicao->linha == tunel->acesso2->linha) {
        return 1;
    }

    return 0;
}

void LevaFinalTunel(tTunel* tunel, tPosicao* posicao) {
    if (!EntrouTunel(tunel, posicao)) return;

    if (tunel->acesso1->coluna == posicao->coluna && tunel->acesso1->linha == posicao->linha) {
        posicao->coluna = tunel->acesso2->coluna;
        posicao->linha = tunel->acesso2->linha;

    } else if (tunel->acesso2->coluna == posicao->coluna && tunel->acesso2->linha == posicao->linha) {
        posicao->coluna = tunel->acesso1->coluna;
        posicao->linha = tunel->acesso1->linha;
    }
}

void DesalocaTunel(tTunel* tunel) {
    DesalocaPosicao(tunel->acesso1);
    DesalocaPosicao(tunel->acesso2);
    free(tunel);
}
