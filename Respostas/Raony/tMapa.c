#include "tMapa.h"

#define COMIDA '*'
#define PORTAL '@'

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

    return mapa;
}

/**
 * Obtem a posição de um item do mapa
 * \param mapa mapa
 * \param item item a ser procurado no mapa
 */
tPosicao* ObtemPosicaoItemMapa(tMapa* mapa, char item) {

}

/**
 * Retorna o túnel do mapa com os 2 acessos
 * \param mapa mapa
 */
tTunel* ObtemTunelMapa(tMapa* mapa);

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

/**
 * Retorna se a posição passada como parâmetro representa uma comida no mapa
 * \param mapa mapa
 * \param posicao posicao a ser verificada
 */
bool EncontrouComidaMapa(tMapa* mapa, tPosicao* posicao);

/**
 * Retorna se a posição passada como parâmetro representa uma parede no mapa
 * \param mapa mapa
 * \param posicao posicao a ser verificada
 */
bool EncontrouParedeMapa(tMapa* mapa, tPosicao* posicao);

/**
 * Atualiza um item do mapa
 * \param mapa mapa
 * \param posicao posicao do item
 * \param item posicao item que vai atualizar o mapa
 */
bool AtualizaItemMapa(tMapa* mapa, tPosicao* posicao, char item);

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

/**
 * Libera o espaço alocado para a estrutura tMapa
 * \param mapa mapa
 */
void DesalocaMapa(tMapa* mapa);