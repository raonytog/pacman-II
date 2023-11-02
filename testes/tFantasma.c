#include "tFantasma.h"

// #define FANT_B 'B'  //fantasma horizontal   - inicio: esquerda
// #define FANT_C 'C'  //fantasma horizontal   - inicio: direita
// #define FANT_I 'I'  //fantasma vertical     - inicio: baixo
// #define FANT_P 'P'  //fantasma vertical     - inicio: cima

bool ExisteFantasmaMapa (tMapa * mapa, char item) {
    for (int i = 0; i < ObtemNumeroLinhasMapa(mapa); i++) {
        for (int j = 0; j < ObtemNumeroColunasMapa(mapa); j++) {
            tPosicao * posicao = CriaPosicao(i, j);
            if (ObtemItemMapa(mapa, posicao) == item) {
                DesalocaPosicao(posicao);
                return true;
            }
        }
    }

    return false;
}

bool FantasmaComeuComida (tFantasma * fantasma) {
    return fantasma->gulaFantasmagorica;
}

tFantasma * CriaFantasma(tMapa * mapa, char simoblogia_fantasma) {
    tFantasma *fantasma = malloc(sizeof(tFantasma *));

    fantasma->dx = 0;
    fantasma->dy = 0;
    fantasma->gulaFantasmagorica = 0;
    fantasma->presenteMapa = 0;
    fantasma->posicao = NULL;
    fantasma->posicaoAntiga = NULL;

    tPosicao * posicao = ObtemPosicaoItemMapa(mapa, simoblogia_fantasma);
    if (posicao == NULL) {
        return fantasma;

    } else {
        fantasma->presenteMapa = 1;
        switch (simoblogia_fantasma) {
            case LEFT_GHOST:
                fantasma->posicao = posicao;
                fantasma->dx = 0;
                fantasma->dy = -1;
                break;

            case RIGHT_GHOST:
                fantasma->posicao = posicao;
                fantasma->dx = 0;
                fantasma->dy = 1;
                break;

            case DOWN_GHOST:
                fantasma->posicao = posicao;
                fantasma->dx = 1;
                fantasma->dy = 0;
                break;

            case UP_GHOST:
                fantasma->posicao = posicao;
                fantasma->dx = -1;
                fantasma->dy = 0;
                break;
        }
    }
    return fantasma;
}

tPosicao * ObtemPosicaoAtualFantasma (tFantasma * fantasma) {
    return fantasma->posicao;
}

tPosicao * ObtemPosicaoAntigaFantasma (tFantasma * fantasma) {
    return fantasma->posicaoAntiga;
}

void MoveFantasmas (tFantasma * baixo, tFantasma * cima, tFantasma * esquerda, tFantasma * direita, tMapa * mapa) {
    tPosicao * cloneB = ClonaPosicao(ObtemPosicaoAtualFantasma(baixo));
    AtualizaPosicao(baixo->posicaoAntiga, baixo->posicao);

    tPosicao * cloneC = ClonaPosicao(ObtemPosicaoAtualFantasma(cima));
    AtualizaPosicao(cima->posicaoAntiga, cima->posicao);

    tPosicao * cloneE = ClonaPosicao(ObtemPosicaoAtualFantasma(esquerda));
    AtualizaPosicao(esquerda->posicaoAntiga, esquerda->posicao);

    tPosicao * cloneD = ClonaPosicao(ObtemPosicaoAtualFantasma(direita));
    AtualizaPosicao(direita->posicaoAntiga, direita->posicao);

    if (EstaPresenteFantasma(esquerda)) { // fantasma b
        cloneE->coluna += esquerda->dy;
        if (FantasmaComeuComida(esquerda)) {
            AtualizaItemMapa(mapa, esquerda->posicaoAntiga, COMIDA);
            esquerda->gulaFantasmagorica = 0;
        }

        if (EncontrouParedeMapa(mapa, cloneE)) {
            esquerda->dy *= -1;
            cloneE->coluna += esquerda->dy;

        } else if (EncontrouComidaMapa(mapa, cloneE)) {
            esquerda->gulaFantasmagorica++;
        }
    }
    AtualizaPosicao(esquerda->posicao, cloneE);
    AtualizaItemMapa(mapa, esquerda->posicao, LEFT_GHOST);


    if (EstaPresenteFantasma(direita)) { // fantasma c
        cloneD->coluna += direita->dy;
        if (FantasmaComeuComida(direita)) {
            AtualizaItemMapa(mapa, direita->posicaoAntiga, COMIDA);
            direita->gulaFantasmagorica = 0;
        }

        if (EncontrouParedeMapa(mapa, cloneD)) {
            direita->dy *= -1;
            cloneD->coluna += direita->dy;

        } else if (EncontrouComidaMapa(mapa, cloneD)) {
            direita->gulaFantasmagorica++;
        }
    }
    AtualizaPosicao(direita->posicao, cloneD);
    AtualizaItemMapa(mapa, direita->posicao, RIGHT_GHOST);


    if (EstaPresenteFantasma(baixo)) { // fantasma i
        cloneB->linha += baixo->dx;
        if (FantasmaComeuComida(baixo)) {
            AtualizaItemMapa(mapa, baixo->posicaoAntiga, COMIDA);
            baixo->gulaFantasmagorica = 0;
        }

        if (EncontrouParedeMapa(mapa, cloneB)) {
            baixo->dx *= -1;
            cloneB->linha += baixo->dx;

        } else if (EncontrouComidaMapa(mapa, cloneB)) {
            baixo->gulaFantasmagorica++;
        }
    }
    AtualizaPosicao(baixo->posicao, cloneB);
    AtualizaItemMapa(mapa, baixo->posicao, DOWN_GHOST);


    if (EstaPresenteFantasma(cima)) { // fantasma p
        cloneC->linha += cima->dx;
        if (FantasmaComeuComida(cima)) {
            AtualizaItemMapa(mapa, cima->posicaoAntiga, COMIDA);
            cima->gulaFantasmagorica = 0;
        }

        if (EncontrouParedeMapa(mapa, cloneC)) {
            cima->dx *= -1;
            cloneC->linha += cima->dx;

        } else if (EncontrouComidaMapa(mapa, cloneC)) {
            cima->gulaFantasmagorica++;
        }
    }
    AtualizaPosicao(cima->posicao, cloneC);
    AtualizaItemMapa(mapa, cima->posicao, DOWN_GHOST);

    DesalocaPosicao(cloneB);
    DesalocaPosicao(cloneC);
    DesalocaPosicao(cloneE);
    DesalocaPosicao(cloneD);
}

int EstaPresenteFantasma (tFantasma * fantasma) {
    return fantasma->presenteMapa;
}

void DesalocaFantasma(tFantasma * fantasma) {
    if (fantasma == NULL) return;

    DesalocaPosicao(fantasma->posicao);
    DesalocaPosicao(fantasma->posicaoAntiga);
    free(fantasma);
}

