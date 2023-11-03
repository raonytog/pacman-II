#include "tFantasma.h"

// #define FANT_B 'B'  //fantasma horizontal   - inicio: esquerda
// #define FANT_C 'C'  //fantasma horizontal   - inicio: direita
// #define FANT_I 'I'  //fantasma vertical     - inicio: baixo
// #define FANT_P 'P'  //fantasma vertical     - inicio: cima

bool ExisteItemPosicao (tMapa * mapa, tPosicao * posicao, char item) {
    if (ObtemItemMapa(mapa, posicao) == item) return true;
    return false;
}

bool FantasmaComeuComida (tFantasma * fantasma) {
    return fantasma->gulaFantasmagorica;
}

tFantasma * CriaFantasma(tMapa * mapa, char simoblogia_fantasma) {
    tFantasma * fantasma = malloc(sizeof(tFantasma));

    fantasma->dx = 0;
    fantasma->dy = 0;
    fantasma->gulaFantasmagorica = 0;
    fantasma->presenteMapa = 0;
    fantasma->posicao = CriaPosicao(0, 0);
    fantasma->posicaoAntiga = CriaPosicao(0, 0);

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

    // fantasma b
    if (EstaPresenteFantasma(esquerda)) {
        AtualizaItemMapa(mapa, esquerda->posicao, VAZIO);
        cloneE->coluna += esquerda->dy;
        if (FantasmaComeuComida(esquerda)) {
            AtualizaItemMapa(mapa, esquerda->posicaoAntiga, COMIDA);
            esquerda->gulaFantasmagorica = 0;
        }

        if (EncontrouParedeMapa(mapa, cloneE)) {
            esquerda->dy *= -1;
            cloneE->coluna += esquerda->dy;
            cloneE->coluna += esquerda->dy;
        }

        if (EncontrouComidaMapa(mapa, cloneE)) {
            esquerda->gulaFantasmagorica++;
        }
        
        AtualizaPosicao(esquerda->posicao, cloneE);
        AtualizaItemMapa(mapa, esquerda->posicao, LEFT_GHOST);
    }

    // fantasma c
    if (EstaPresenteFantasma(direita)) {
        AtualizaItemMapa(mapa, direita->posicao, VAZIO);
        cloneD->coluna += direita->dy;
        if (FantasmaComeuComida(direita)) {
            AtualizaItemMapa(mapa, direita->posicaoAntiga, COMIDA);
            direita->gulaFantasmagorica = 0;
        }

        if (EncontrouParedeMapa(mapa, cloneD)) {
            direita->dy *= -1;
            cloneD->coluna += direita->dy;
            cloneD->coluna += direita->dy;
        }

        if (EncontrouComidaMapa(mapa, cloneD)) {
            direita->gulaFantasmagorica++;
        }

        AtualizaPosicao(direita->posicao, cloneD);
        AtualizaItemMapa(mapa, direita->posicao, RIGHT_GHOST);
    }

    // fantasma i
    if (EstaPresenteFantasma(baixo)) {
        AtualizaItemMapa(mapa, baixo->posicao, VAZIO);
        cloneB->linha += baixo->dx;
        if (FantasmaComeuComida(baixo)) {
            AtualizaItemMapa(mapa, baixo->posicaoAntiga, COMIDA);
            baixo->gulaFantasmagorica = 0;
        }

        if (EncontrouParedeMapa(mapa, cloneB)) {
            baixo->dx *= -1;
            cloneB->linha += baixo->dx;
            cloneB->linha += baixo->dx;
        }

        if (EncontrouComidaMapa(mapa, cloneB)) {
            baixo->gulaFantasmagorica++;
        }

        AtualizaPosicao(baixo->posicao, cloneB);
        AtualizaItemMapa(mapa, baixo->posicao, DOWN_GHOST);
    }

    // fantasma p
    if (EstaPresenteFantasma(cima)) {
        AtualizaItemMapa(mapa, cima->posicao, VAZIO);
        
        cloneC->linha += cima->dx;
        if (FantasmaComeuComida(cima)) {
            AtualizaItemMapa(mapa, cima->posicaoAntiga, COMIDA);
            cima->gulaFantasmagorica = 0;
        }

        if (EncontrouParedeMapa(mapa, cloneC)) {
            cima->dx *= -1;
            cloneC->linha += cima->dx;
            cloneC->linha += cima->dx;
        } 

        if (EncontrouComidaMapa(mapa, cloneC)) {
            cima->gulaFantasmagorica++;
        }

        AtualizaPosicao(cima->posicao, cloneC);
        AtualizaItemMapa(mapa, cima->posicao, UP_GHOST);
    }

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

