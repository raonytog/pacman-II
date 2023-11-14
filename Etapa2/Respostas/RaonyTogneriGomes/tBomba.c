#include "tBomba.h"

tBomba * CriaBomba (tMapa * mapa) {
    tBomba * bomba = malloc(sizeof(tBomba));
    bomba->aparecia = DESARMADA;
    bomba->posicao = ObtemPosicaoItemMapa(mapa, bomba->aparecia);
    bomba->acionada = 0;
    return bomba;
}

int EstaDesarmadaBomba (tBomba * bomba) {
    return bomba->acionada == 0;
}

int EstaArmadaBomba(tBomba * bomba) {
    return bomba->acionada == 1;
}

void ExplodeBomba (tBomba * bomba, tMapa * mapa, tFantasma * left, 
                   tFantasma *  right, tFantasma * down, tFantasma * up, 
                   tFantasma * hori, tFantasma * verti, tPacman * pacman) {

    if (bomba->posicao == NULL) return;
    
    if (SaoIguaisPosicao(ObtemPosicaoPacman(pacman), bomba->posicao) && EstaDesarmadaBomba(bomba)) {
        bomba->aparecia = CLOCK_3;
        AtualizaItemMapa(mapa, bomba->posicao, bomba->aparecia);
        bomba->acionada = 1;
        return;
    }

    if (bomba->aparecia == CLOCK_3) {
        bomba->aparecia = CLOCK_2;
        AtualizaItemMapa(mapa, bomba->posicao, bomba->aparecia);
        return;
    }

    if (bomba->aparecia == CLOCK_2) {
        bomba->aparecia = CLOCK_1;
        AtualizaItemMapa(mapa, bomba->posicao, bomba->aparecia);
        return;
    }

    if (bomba->aparecia == CLOCK_1) {
        bomba->aparecia = VAZIO;
        int i = 0, j = 0;

        for (i = ObtemLinhaPosicao(bomba->posicao)-1; i < ObtemLinhaPosicao(bomba->posicao)+2; i++) {
            for (j = ObtemColunaPosicao(bomba->posicao)-1; j < ObtemColunaPosicao(bomba->posicao)+2; j++) {

                if (mapa->grid[i][j] == COMIDA) mapa->nFrutasAtual--;

                if (mapa->grid[i][j] == PACMAN) MataPacman(pacman);

                if (mapa->grid[i][j] == UP_GHOST) MataFantasma(up);
                if (mapa->grid[i][j] == DOWN_GHOST) MataFantasma(down);
                if (mapa->grid[i][j] == RIGHT_GHOST) MataFantasma(right);
                if (mapa->grid[i][j] == LEFT_GHOST) MataFantasma(left);
                if (mapa->grid[i][j] == HORIZONTAL_GHOST) MataFantasma(hori);
                if (mapa->grid[i][j] == VERTICAL_GHOST) MataFantasma(verti);

                mapa->grid[i][j] = VAZIO;
            }
        }
    }
}

tPosicao * RetornaPosicaoBomba (tBomba * bomba) {
    return bomba->posicao;
}

void DesalocaBomba (tBomba * bomba) {
    if (bomba == NULL) return;

    DesalocaPosicao(bomba->posicao);
    free(bomba);
}