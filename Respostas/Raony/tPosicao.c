#include "tPosicao.h"

tPosicao* CriaPosicao(int linha, int coluna) {
    tPosicao *posicao = (tPosicao *) calloc (2, sizeof(int));
    return posicao;
}

tPosicao* ClonaPosicao(tPosicao* posicao) {
    tPosicao * posicaoClone = NULL;
    posicaoClone->coluna = posicao->coluna;
    posicaoClone->linha = posicao->linha;
    return posicaoClone;
}

int ObtemLinhaPosicao(tPosicao* posicao) {
    return posicao->linha;
}

int ObtemColunaPosicao(tPosicao* posicao) {
    return posicao->coluna;
}

void AtualizaPosicao(tPosicao* posicaoAtual, tPosicao* posicaoNova) {
    posicaoAtual->coluna = posicaoNova->coluna;
    posicaoAtual->linha = posicaoNova->linha;
}

bool SaoIguaisPosicao(tPosicao* posicao1, tPosicao* posicao2) {
    return ( (posicao1->linha == posicao2->linha) && (posicao1->coluna == posicao2->coluna) );
}

void DesalocaPosicao(tPosicao* posicao) {
    free (posicao);
}