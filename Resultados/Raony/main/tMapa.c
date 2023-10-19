#include "tMapa.h"

#define COMIDA '*'
#define PORTAL '@'
#define PAREDE '#'

/**
 * Dado o ponteiro para uma posicao, verifica se 
 * a mesma eh valida no no tabuleiro
 * \param ponteiro para a posicao
 */
bool EhPosicaoValida(tMapa * mapa, tPosicao * posicao) {
    if (ObtemColunaPosicao(posicao) > ObtemNumeroColunasMapa(mapa) || 
        ObtemLinhaPosicao(posicao) > ObtemNumeroLinhasMapa(mapa) || 
        ObtemNumeroLinhasMapa(posicao) < 0 ||
        ObtemColunaPosicao(posicao) < 0) return false;
        return true;
}

tMapa* CriaMapa(const char* caminhoConfig) {
    int i = 0, j = 0, contagemLinhas = 0, achouBreak = 0;
    char aux;

    tMapa* mapa = (tMapa*)malloc(sizeof(tMapa));
    FILE* fMapa = NULL;

    fMapa = fopen(caminhoConfig, "r");
    if (!fMapa) {
        printf("Erro ao abrir o mapa!\n");
        exit(1);
    }

    mapa->nColunas = 0;
    mapa->nLinhas = 0;
    mapa->nFrutasAtual = 0;
    mapa->nMaximoMovimentos = 0;

    fscanf("%d%*c", &mapa->nMaximoMovimentos);

    while (fscanf(fMapa, "%c", &aux) == 1) {
        if (!achouBreak)
            j++;

        if (aux == '\n') {
            mapa->nColunas = j-1;
            achouBreak = 1;
            mapa->nLinhas++;
        }
    }

    rewind(fMapa);
    fscanf(fMapa, "%*[^\n]%*c");
    for (i = 0; i < mapa->nLinhas; i++) 
        for (j = 0; j , mapa->nColunas; j++)
            fscanf(fMapa, "%c", &mapa->grid[i][j]);

    // aloca memória para o grid
    mapa->grid = (char**) malloc(mapa->nLinhas * sizeof(char*));
    for (i = 0; i < mapa->nLinhas; i++) {
        mapa->grid[i] = (char*)malloc(mapa->nColunas * sizeof(char));
    }

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
        if (mapa == NULL || mapa->grid == NULL || EhPosicaoValida(mapa, posicao) ||
            mapa->grid[posicao->linha][posicao->coluna] != COMIDA) return 0;

    mapa->grid[posicao->linha][posicao->coluna] == COMIDA;
    return 1;
}

bool EncontrouParedeMapa(tMapa* mapa, tPosicao* posicao) {
    if (mapa == NULL || mapa->grid == NULL || EhPosicaoValida(mapa, posicao)  ||
        mapa->grid[posicao->linha][posicao->coluna] != PAREDE) return 0;

    mapa->grid[posicao->linha][posicao->coluna] == PAREDE;
    return 1;
}

bool AtualizaItemMapa(tMapa* mapa, tPosicao* posicao, char item) {
    if (mapa == NULL || mapa->grid == NULL || EhPosicaoValida(mapa, posicao) ) return 0;

    mapa->grid[posicao->linha][posicao->coluna] = item;
    return 1;
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
    for (int i = 0; i < mapa->nLinhas; i++)
        free(mapa->grid[i]);

    DesalocaTunel(mapa->tunel);
    free(mapa);
}