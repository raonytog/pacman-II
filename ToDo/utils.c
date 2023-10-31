#include "utils.h"

/**
 * Dado o ponteiro para uma posicao, verifica se 
 * a mesma eh valida no no tabuleiro
 * \param ponteiro para a posicao e ponteiro para o mapa
 */
bool EstaForaDosLimites(tMapa * mapa, tPosicao * posicao) {
    if (ObtemColunaPosicao(posicao) > ObtemNumeroColunasMapa(mapa) || 
        ObtemLinhaPosicao(posicao)  > ObtemNumeroLinhasMapa(mapa) || 
        ObtemLinhaPosicao(posicao) < 0 || ObtemColunaPosicao(posicao) < 0) return true;
    return false;
}

/**
 * Dado o ponteiro para uma mapa, verifica se o mapa ou o grid é NULL
 * \param ponteiro para o mapa
 */
bool EhNullGridOuMapa (tMapa * mapa) {
    return (mapa == NULL || mapa->grid == NULL);
}