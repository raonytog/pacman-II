#include "tVerificacoes.h"

bool EstaForaDosLimites(tMapa * mapa, tPosicao * posicao) {
    if (ObtemColunaPosicao(posicao) > ObtemNumeroColunasMapa(mapa) || 
        ObtemLinhaPosicao(posicao)  > ObtemNumeroLinhasMapa(mapa) || 
        ObtemLinhaPosicao(posicao) < 0 || ObtemColunaPosicao(posicao) < 0) return true;
    return false;
}


bool EhNullGridOuMapa (tMapa * mapa) {
    return (mapa == NULL || mapa->grid == NULL);
}