#include "tMapa.h"

#define COMIDA '*'
#define PORTAL '@'
#define PAREDE '#'

/**
 * Cria o mapa dinamicamente
 * \param caminho caminho do arquivo com as configurações do mapa
 */
tMapa* CriaMapa(const char* caminhoConfig) {
    tMapa * mapa = (tMapa *) malloc (sizeof(tMapa));

    FILE * fMapa = NULL;
    fMapa = open(caminhoConfig);
    if (!fMapa) {
        printf("Erro ao abrir o mapa!\n");
        exit(1);
    }

    // a implementar

    return mapa;
}

tPosicao* ObtemPosicaoItemMapa(tMapa* mapa, char item) {
     for (int i = 0; i < mapa->nLinhas; i++)
        for (int j = 0; j < mapa->nColunas; j++)
            if (mapa->grid[i][j] == item) {
                tPosicao * posicao = CriaPosicao(i, j);
                return posicao;
            }
}

tTunel* ObtemTunelMapa(tMapa* mapa) {
    tTunel * tunel = mapa->tunel;
    return tunel;
}

char ObtemItemMapa(tMapa* mapa, tPosicao* posicao) {
    return mapa->grid[posicao->linha][posicao->coluna];
}

int ObtemNumeroLinhasMapa(tMapa* mapa) {
    return mapa->nLinhas;
}

int ObtemNumeroColunasMapa(tMapa* mapa) {
    return mapa->nColunas;
}

int ObtemQuantidadeFrutasIniciaisMapa(tMapa* mapa) {
    int contagem = 0;

    for (int i = 0; i < mapa->nLinhas; i++)
        for (int j = 0; j < mapa->nColunas; j++)
            if (mapa->grid[i][j] == COMIDA) contagem++;
    
    return contagem;
}

int ObtemNumeroMaximoMovimentosMapa(tMapa* mapa) {
    return mapa->nMaximoMovimentos;
}

bool EncontrouComidaMapa(tMapa* mapa, tPosicao* posicao) {
    return mapa->grid[posicao->linha][posicao->coluna] == COMIDA;
}

bool EncontrouParedeMapa(tMapa* mapa, tPosicao* posicao) {
    return mapa->grid[posicao->linha][posicao->coluna] == PAREDE;
}

void AtualizaItemMapa(tMapa* mapa, tPosicao* posicao, char item) {
    mapa->grid[posicao->linha][posicao->coluna] = item;
}

bool PossuiTunelMapa(tMapa* mapa) {
    for (int i = 0; i < mapa->nLinhas; i++)
        for (int j = 0; j < mapa->nColunas; j++)
            if (mapa->grid[i][j] == PORTAL) return 1;
    return 0;
}

bool AcessouTunelMapa(tMapa* mapa, tPosicao* posicao) {
    return EntrouTunel(mapa->tunel, posicao);
}

void EntraTunelMapa(tMapa* mapa, tPosicao* posicao) {
    LevaFinalTunel(mapa->tunel, posicao);
}

void DesalocaMapa(tMapa* mapa) {
    free(mapa->tunel);
    free(mapa);
}