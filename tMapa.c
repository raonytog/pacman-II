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
        ObtemLinhaPosicao(posicao) < 0 ||
        ObtemColunaPosicao(posicao) < 0) return false;
        return true;
}

/**
 * Dado o ponteiro para uma mapa, verifica se o mapa ou o grid é NULL
 * \param ponteiro para o mapa
 */
bool EhNullGridOuMapa (tMapa * mapa) {
    return mapa == NULL || mapa->grid == NULL;
}

tMapa* CriaMapa(const char* caminhoConfig) {
    int i = 0, j = 0, contagemLinhas = 0, achouBreak = 0;
    int linhaP1 = 0, linhaP2 = 0, colunaP1 = 0, colunaP2 = 0, tickFlag = 0;
    char aux = '0', caminhoMapa[1000];

    tMapa * mapa = (tMapa*)malloc(sizeof(tMapa));
    FILE * fMapa = NULL;

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
    mapa->tunel = NULL;

    fscanf(fMapa, "%d\n", &mapa->nMaximoMovimentos);
    while (fscanf(fMapa, "%c", &aux) == 1) {
        // atribui o numero de colunas e conta o num de \n como num linhas
        if (aux == '\n') {
            mapa->nColunas = j;
            mapa->nLinhas++;
            achouBreak = 1; // bloqueia q o numero de colunas altere
        }

        //le qts char tem ate o \n
        if (!achouBreak) {
            j++;
        }
    }

    // aloca memória para o grid
    mapa->grid = (char**) malloc(ObtemNumeroLinhasMapa(mapa) * sizeof(char*));
    for (i = 0; i < ObtemNumeroLinhasMapa(mapa); i++) {
        mapa->grid[i] = (char*) malloc(ObtemNumeroColunasMapa(mapa) * sizeof(char));
    }
    

    // le o mapa e armazena no grid, alem de criar o portal caso exista no mapa
    rewind(fMapa);
    fscanf(fMapa, "%d\n", &mapa->nMaximoMovimentos);
    for (i = 0; i < ObtemNumeroLinhasMapa(mapa)+1; i++) {
//fscanf(fMapa, "%c", &aux);
        for (j = 0; j < ObtemNumeroColunasMapa(mapa)+1; j++) {
            fscanf(fMapa, "%c", &mapa->grid[i][j]);
        }
    }

    mapa->nFrutasAtual = ObtemQuantidadeFrutasIniciaisMapa(mapa);
    for (i = 0; i < ObtemNumeroLinhasMapa(mapa); i++) {
        for (j = 0; j < ObtemNumeroColunasMapa(mapa); j++) {
            if (mapa->grid[i][j] == PORTAL) {
                switch (tickFlag) {
                     case 1:
                        tickFlag++;
                        linhaP1 = i;
                        colunaP1 = j;
                        break;

                     case 2:
                        linhaP2 = i;
                        colunaP2 = j;
                        tTunel * portal = CriaTunel(linhaP1, colunaP1, linhaP2, colunaP2);
                        mapa->tunel = portal;
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
    tTunel * tunel = mapa->tunel;
    return tunel;
}

char ObtemItemMapa(tMapa* mapa, tPosicao* posicao) {
    if (EhNullGridOuMapa(mapa) || EhPosicaoValida(mapa, posicao)) return '\0';
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

    for (int i = 0; i < ObtemNumeroLinhasMapa(mapa); i++)
        for (int j = 0; j < ObtemNumeroColunasMapa(mapa); j++) {

            tPosicao * posicao = CriaPosicao(0, 0);
            if (EncontrouComidaMapa(mapa, posicao)) contagem++;
            DesalocaPosicao(posicao);
        }
    
    return contagem;
}

int ObtemNumeroMaximoMovimentosMapa(tMapa* mapa) {
    return mapa->nMaximoMovimentos;
}

bool EncontrouComidaMapa(tMapa* mapa, tPosicao* posicao) {
        if (EhNullGridOuMapa(mapa) || EhPosicaoValida(mapa, posicao) ||
            mapa->grid[posicao->linha][posicao->coluna] != COMIDA) return 0;

    mapa->nFrutasAtual--;
    return 1;
}

bool EncontrouParedeMapa(tMapa* mapa, tPosicao* posicao) {
    if (EhNullGridOuMapa(mapa) || EhPosicaoValida(mapa, posicao)  ||
        mapa->grid[posicao->linha][posicao->coluna] != PAREDE) return 0;

    return 1;
}

bool AtualizaItemMapa(tMapa* mapa, tPosicao* posicao, char item) {
    if (EhNullGridOuMapa(mapa)|| EhPosicaoValida(mapa, posicao)) return 0;

    mapa->grid[posicao->linha][posicao->coluna] = item;
    return 1;
}

bool PossuiTunelMapa(tMapa* mapa) {
    if (mapa->tunel == NULL) return false;
    return true;
}

bool AcessouTunelMapa(tMapa* mapa, tPosicao* posicao) {
    return EntrouTunel(mapa->tunel, posicao);
}

void EntraTunelMapa(tMapa* mapa, tPosicao* posicao) {
    LevaFinalTunel(mapa->tunel, posicao);
}

void DesalocaMapa(tMapa* mapa) {
    if (mapa == NULL) return;

    for (int i = 0; i < mapa->nLinhas; i++)
        free(mapa->grid[i]);

    DesalocaTunel(mapa->tunel);
    free(mapa);
}