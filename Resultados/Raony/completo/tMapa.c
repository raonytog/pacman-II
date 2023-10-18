#include "tMapa.h"

#define COMIDA '*'
#define PORTAL '@'
#define PAREDE '#'

/**
 * Cria o mapa dinamicamente
 * \param caminho caminho do arquivo com as configurações do mapa
 */
tMapa* CriaMapa(const char* caminhoConfig) {

    /*
    MAT + COL * I + J
    int (MAT*)[C]    
    */

    int i = 0, j = 0, contagemLinhas = 0;
    char aux = '0';
    tMapa * mapa = (tMapa *) malloc (sizeof(tMapa));
    FILE * fMapa = NULL;
    fMapa = open(caminhoConfig);
    if (!fMapa) {
        printf("Erro ao abrir o mapa!\n");
        exit(1);
    }

    fscanf("%d", &mapa->nMaximoMovimentos);
    while ( aux != '\n') {
        scanf("%c", &aux);
        j++;
    }
    mapa->nColunas = j;

    rewind(fMapa);
    scanf("%*c"); // joga fora a qnt de movimento q ja foi lida anteriormente

    aux = '0';
    while ( scanf("%c", &aux) == 1) {
        if (aux == '\n') contagemLinhas++;
    }
    mapa->nLinhas = contagemLinhas;

    mapa->grid = malloc (ObtemNumeroLinhasMapa(mapa) * ObtemNumeroColunasMapa(mapa) * sizeof(char));

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
    return mapa->grid[mapa->nColunas * posicao->linha + posicao->coluna];
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
        if (mapa == NULL || mapa->grid == NULL ||
        ObtemColunaPosicao(posicao) > ObtemNumeroColunasMapa(mapa) || ObtemColunaPosicao(posicao) < 0 ||
        ObtemLinhaPosicao(posicao) > ObtemNumeroLinhasMapa(mapa) || ObtemNumeroLinhasMapa(posicao) < 0 ||
        mapa->grid[ObtemNumeroColunasMapa(mapa) * ObtemLinhaPosicao(posicao) + ObtemColunaPosicao(posicao)] != COMIDA) return 0;

    return mapa->grid[posicao->linha][posicao->coluna] == COMIDA;
    return 1;
}

bool EncontrouParedeMapa(tMapa* mapa, tPosicao* posicao) {
    if (mapa == NULL || mapa->grid == NULL ||
        ObtemColunaPosicao(posicao) > ObtemNumeroColunasMapa(mapa) || ObtemColunaPosicao(posicao) < 0 ||
        ObtemLinhaPosicao(posicao) > ObtemNumeroLinhasMapa(mapa) || ObtemNumeroLinhasMapa(posicao) < 0 ||
        mapa->grid[ObtemNumeroColunasMapa(mapa) * ObtemLinhaPosicao(posicao) + ObtemColunaPosicao(posicao)] != PAREDE) return 0;

    mapa->grid[ObtemNumeroColunasMapa(mapa) * ObtemLinhaPosicao(posicao) + ObtemColunaPosicao(posicao)] == PAREDE;
    return 1;
}

bool AtualizaItemMapa(tMapa* mapa, tPosicao* posicao, char item) {
    if (mapa == NULL || mapa->grid == NULL ||
        ObtemColunaPosicao(posicao) > ObtemNumeroColunasMapa(mapa) || ObtemColunaPosicao(posicao) < 0 ||
        ObtemLinhaPosicao(posicao) > ObtemNumeroLinhasMapa(mapa) || ObtemNumeroLinhasMapa(posicao) < 0) return 0;

    mapa->grid[ObtemNumeroColunasMapa(mapa) * ObtemLinhaPosicao(posicao) + ObtemColunaPosicao(posicao)] = item;
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