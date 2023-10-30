#include "tPosicao.h"

tPosicao* CriaPosicao(int linha, int coluna) {
    tPosicao * posicao = (tPosicao *) malloc (sizeof(tPosicao));
    if (posicao == NULL) {
        printf("Alocacao impropria no tPosicao.c\n");
        exit(1);
    }

    posicao->linha = linha;
    posicao->coluna = coluna;
    return posicao;
}

tPosicao* ClonaPosicao(tPosicao* posicao) {
    tPosicao * posicaoClone = CriaPosicao(ObtemLinhaPosicao(posicao), ObtemColunaPosicao(posicao));
    return posicaoClone;
}

int ObtemLinhaPosicao(tPosicao* posicao) {
    return posicao->linha;
}

int ObtemColunaPosicao(tPosicao* posicao) {
    return posicao->coluna;
}

void AtualizaPosicao(tPosicao* posicaoAtual, tPosicao* posicaoNova) {
    *posicaoAtual = *posicaoNova;
}

bool SaoIguaisPosicao(tPosicao* posicao1, tPosicao* posicao2) {
    return ( (ObtemLinhaPosicao(posicao1) == ObtemLinhaPosicao(posicao2)) && (ObtemColunaPosicao(posicao1) == ObtemColunaPosicao(posicao2)) );
}

void DesalocaPosicao(tPosicao* posicao) {
    free (posicao);
}