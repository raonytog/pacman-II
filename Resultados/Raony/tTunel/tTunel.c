#include "tTunel.h"

tTunel* CriaTunel(int linhaAcesso1, int colunaAcesso1, int linhaAcesso2, int colunaAcesso2) {
    tPosicao * posicao1 = CriaPosicao(linhaAcesso1, colunaAcesso1);
    tPosicao * posicao2 = CriaPosicao(linhaAcesso2, colunaAcesso2);

    tTunel * tunel = (tTunel *) malloc(sizeof(tTunel));
    if (tunel == NULL) {
        printf("Alocacao impropria no tTunel.c\n");
        exit(1);
    }

    AtualizaPosicao(tunel->acesso1, posicao1);
    AtualizaPosicao(tunel->acesso2, posicao2)
    return tunel;
}

bool EntrouTunel(tTunel* tunel, tPosicao* posicao) {
    return (SaoIguaisPosicao(posicao, tunel->acesso1) || SaoIguaisPosicao(posicao, tunel->acesso2));
}

void LevaFinalTunel(tTunel* tunel, tPosicao* posicao) {
    if (!EntrouTunel(tunel, posicao)) return;

    if (SaoIguaisPosicao(tunel->acesso1, posicao)) {
       AtualizaPosicao(posicao, tunel->acesso2);

    } else if (SaoIguaisPosicao(tunel->acesso2, posicao)) {
        AtualizaPosicao(posicao, tunel->acesso1);
    }
}

void DesalocaTunel(tTunel* tunel) {
    if (tunel == NULL) return; 

    DesalocaPosicao(tunel->acesso1);
    DesalocaPosicao(tunel->acesso2);
    free(tunel);
}
