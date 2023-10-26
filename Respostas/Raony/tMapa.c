// #include "tMapa.h"
// #include <string.h>
#include "utils.h"

tMapa* CriaMapa(const char* caminhoConfig) {
    tMapa * mapa = (tMapa*)malloc(sizeof(tMapa));
    FILE * fMapa = NULL;

    // define o caminho para o mapa
    char aux[1000], caminhoMapa[1000];
    sprintf(caminhoMapa, "%s/mapa.txt", caminhoConfig);
    fMapa = fopen(caminhoMapa, "r");
    if (!fMapa) {
        printf("Erro ao abrir o mapa!\n");
        exit(1);
    }

    // inicializa as variaveis
    mapa->nColunas = 0;
    mapa->nLinhas = 0;
    mapa->nFrutasAtual = 0;
    mapa->nMaximoMovimentos = 0;
    mapa->grid = NULL;
    mapa->tunel = NULL;

    // le limites do mapa
    fscanf(fMapa, "%d\n", &mapa->nMaximoMovimentos);
    while (fscanf(fMapa, "%[^\n]", aux) == 1) {
        mapa->nColunas = strlen(aux);
        mapa->nLinhas++;
        fscanf(fMapa, "%*c");
    }

    // aloca memória para o grid
    int i = 0, j = 0;
    mapa->grid = (char**) malloc (ObtemNumeroLinhasMapa(mapa) * sizeof(char*));
    for (i = 0; i < ObtemNumeroLinhasMapa(mapa); i++) {
        mapa->grid[i] = (char*) malloc (ObtemNumeroColunasMapa(mapa) * sizeof(char));
    }
    
    // le o mapa e armazena no grid, alem de criar o portal caso exista no mapa
    int linhaP1 = 0, colunaP1 = 0, numPortaisEcontrados = 0;
    rewind(fMapa);
    fscanf(fMapa, "%d", &mapa->nMaximoMovimentos);
    for (i = 0; i < ObtemNumeroLinhasMapa(mapa); i++) {
        fscanf(fMapa, "%*c");
        for (j = 0; j < ObtemNumeroColunasMapa(mapa); j++) {
            fscanf(fMapa, "%c", &mapa->grid[i][j]);

            if (mapa->grid[i][j] == COMIDA) mapa->nFrutasAtual++;
            
            if (mapa->grid[i][j] == PORTAL) {
                numPortaisEcontrados++;

                if (numPortaisEcontrados == 1) {
                    linhaP1 = i; 
                    colunaP1 = j;

                } else if (numPortaisEcontrados == 2) {
                    tTunel * tunel = CriaTunel(linhaP1, colunaP1, i, j);
                    mapa->tunel = tunel;
                }
            }
        }
    }

    fclose(fMapa);
    return mapa;
}

tPosicao* ObtemPosicaoItemMapa(tMapa* mapa, char item) {
    for (int i = 0; i < mapa->nLinhas; i++)
        for (int j = 0; j < mapa->nColunas; j++)
            if (mapa->grid[i][j] == item) {
                tPosicao * posicao = CriaPosicao(i, j);
                return posicao;
            }

    return NULL;
}

tTunel* ObtemTunelMapa(tMapa* mapa) {
    return mapa->tunel;                     
}

char ObtemItemMapa(tMapa* mapa, tPosicao* posicao) {
    if (EhNullGridOuMapa(mapa) || EstaForaDosLimites(mapa, posicao)) return '\0';
    return mapa->grid[posicao->linha][posicao->coluna];
}

int ObtemNumeroLinhasMapa(tMapa* mapa) {
    return mapa->nLinhas;
}

int ObtemNumeroColunasMapa(tMapa* mapa) {
    return mapa->nColunas;
}

int ObtemQuantidadeFrutasIniciaisMapa(tMapa* mapa) {
    return mapa->nFrutasAtual;
}

int ObtemNumeroMaximoMovimentosMapa(tMapa* mapa) {
    return mapa->nMaximoMovimentos;
}

bool EncontrouComidaMapa(tMapa* mapa, tPosicao* posicao) {
    if (EhNullGridOuMapa(mapa) || EstaForaDosLimites(mapa, posicao) ||
        mapa->grid[posicao->linha][posicao->coluna] != COMIDA) return false;

    return true;
}

bool EncontrouParedeMapa(tMapa* mapa, tPosicao* posicao) {
    if (EhNullGridOuMapa(mapa) || EstaForaDosLimites(mapa, posicao) || mapa->grid[posicao->linha][posicao->coluna] != PAREDE) return 0;

    return 1;
}

bool AtualizaItemMapa(tMapa* mapa, tPosicao* posicao, char item) {
    if (EhNullGridOuMapa(mapa)|| EstaForaDosLimites(mapa, posicao)) return 0;

    mapa->grid[posicao->linha][posicao->coluna] = item;
    return 1;
}

bool PossuiTunelMapa(tMapa* mapa) {
    return mapa->tunel != NULL;
}

bool AcessouTunelMapa(tMapa* mapa, tPosicao* posicao) {
    return EntrouTunel(mapa->tunel, posicao);
}

void EntraTunelMapa(tMapa* mapa, tPosicao* posicao) {
    LevaFinalTunel(mapa->tunel, posicao);
}

void DesalocaMapa(tMapa* mapa) {
    if (mapa == NULL) return;

    if (mapa->grid != NULL) {
        for (int i = 0; i < ObtemNumeroLinhasMapa(mapa); i++) {
            free(mapa->grid[i]);
        }
        free(mapa->grid);
    }

    DesalocaTunel(mapa->tunel);
    free(mapa);
}