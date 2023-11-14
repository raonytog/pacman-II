#include "tBomba.h"

tBomba * CriaBomba (tPosicao * posicao) {
    tBomba * bomba = malloc (sizeof(tBomba));
    bomba->aparencia = '&';
    bomba->posicaoBomba = posicao;
    bomba->acionada = 0;
    return bomba;
}

bool ExisteBombaMapa (tBomba * bomba) {
    return bomba != NULL;
}

tPosicao * ObtemPosicaoBomba (tBomba * bomba) {
    return bomba->posicaoBomba;
}

bool EstaDesarmadaBomba (tBomba * bomba) {
    return bomba->acionada == 0;
}

bool EstaAcionadaBomba (tBomba * bomba) {
    return bomba->acionada == 1;
}

void ExplodeBomba (tBomba * bomba, tMapa * mapa, tPacman * pacman, 
                   tFantasma * baixo, tFantasma * cima, tFantasma * esquerda, 
                   tFantasma * direita, tFantasma * horizontal, tFantasma * vertical) {
    if (bomba == NULL) return;
    
    if (SaoIguaisPosicao(ObtemPosicaoPacman(pacman), ObtemPosicaoBomba(bomba)) && EstaDesarmadaBomba(bomba)) {
        bomba->aparencia = CLOCK_3;
        AtualizaItemMapa(mapa, bomba->posicaoBomba, bomba->aparencia);
        bomba->acionada = 1;
        return;
    }

    if (EstaAcionadaBomba(bomba)) {
        if (bomba->aparencia == CLOCK_3) {
            bomba->aparencia = CLOCK_2;
            AtualizaItemMapa(mapa, bomba->posicaoBomba, bomba->aparencia);
        }

        else if (bomba->aparencia == CLOCK_2) {
            bomba->aparencia = CLOCK_1;
            AtualizaItemMapa(mapa, bomba->posicaoBomba, bomba->aparencia);
        }
        
        else {
            bomba->aparencia = EXPLODIU;
            for (int i = ObtemLinhaPosicao(bomba->posicaoBomba)-1; i < ObtemLinhaPosicao(bomba->posicaoBomba)+2 && i < ObtemNumeroLinhasMapa(mapa)-1; i++) {
                for (int j = ObtemColunaPosicao(bomba->posicaoBomba) -1; j < ObtemColunaPosicao(bomba->posicaoBomba)+2 && j < ObtemNumeroColunasMapa(mapa)-1; j++) {
                    tPosicao * posicao = CriaPosicao(i, j);
                    if (SaoIguaisPosicao(posicao, pacman->posicaoAtual)) MataPacman(pacman);

                    if (SaoIguaisPosicao(posicao, cima->posicao)) MataFantasma(cima);
                    if (SaoIguaisPosicao(posicao, baixo->posicao)) MataFantasma(baixo);
                    if (SaoIguaisPosicao(posicao, direita->posicao)) MataFantasma(direita);
                    if (SaoIguaisPosicao(posicao, esquerda->posicao)) MataFantasma(esquerda);
                    if (SaoIguaisPosicao(posicao, horizontal->posicao)) MataFantasma(horizontal);
                    if (SaoIguaisPosicao(posicao, vertical->posicao)) MataFantasma(vertical);

                    if (mapa->grid[i][j] == COMIDA) mapa->nFrutasAtual--;
                    if (i != 0 && i != ObtemNumeroLinhasMapa(mapa)-1 && j != 0 && j != ObtemNumeroColunasMapa(mapa)-1) 
                        mapa->grid[i][j] = VAZIO;
                }
            }
        }
    }
}

