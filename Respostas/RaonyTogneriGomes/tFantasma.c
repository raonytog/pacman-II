#include "tFantasma.h"

bool ExisteItemPosicao (tMapa * mapa, tPosicao * posicao, char item) {
    if (ObtemItemMapa(mapa, posicao) == item) return true;
    return false;
}

bool FantasmaComeuComida (tFantasma * fantasma) {
    return fantasma->gulaFantasmagorica;
}

tFantasma * CriaFantasmaPresente (tMapa * mapa, char simoblogia_fantasma) {
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
                AtualizaPosicao(fantasma->posicao, posicao);
                fantasma->dx = 0;
                fantasma->dy = -1;
                break;

            case RIGHT_GHOST:
                AtualizaPosicao(fantasma->posicao, posicao);
                fantasma->dx = 0;
                fantasma->dy = 1;
                break;

            case DOWN_GHOST:
                AtualizaPosicao(fantasma->posicao, posicao);
                fantasma->dx = 1;
                fantasma->dy = 0;
                break;

            case UP_GHOST:
                AtualizaPosicao(fantasma->posicao, posicao);
                fantasma->dx = -1;
                fantasma->dy = 0;
                break;
        }
    }
    DesalocaPosicao(posicao);
    return fantasma;
}

tPosicao * ObtemPosicaoAtualFantasma (tFantasma * fantasma) {
    return fantasma->posicao;
}

tPosicao * ObtemPosicaoAntigaFantasma (tFantasma * fantasma) {
    return fantasma->posicaoAntiga;
}

void MoveFantasmas (tFantasma * baixo, tFantasma * cima, tFantasma * esquerda, tFantasma * direita, 
                    tMapa * mapa, tPacman * pacman) {
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
        if (!SaoIguaisPosicao(pacman->posicaoAtual, esquerda->posicao)) AtualizaItemMapa(mapa, esquerda->posicao, VAZIO);
        else AtualizaItemMapa(mapa, esquerda->posicao, PACMAN);

        cloneE->coluna += esquerda->dy;
        if (FantasmaComeuComida(esquerda)) {
            if (!SaoIguaisPosicao(esquerda->posicaoAntiga, pacman->posicaoAtual)) 
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
    }

    // fantasma c
    if (EstaPresenteFantasma(direita)) {
        if (!SaoIguaisPosicao(pacman->posicaoAtual, direita->posicao)) AtualizaItemMapa(mapa, direita->posicao, VAZIO);
        else AtualizaItemMapa(mapa, direita->posicao, PACMAN);

        cloneD->coluna += direita->dy;
        if (FantasmaComeuComida(direita)) {
            if (!SaoIguaisPosicao(pacman->posicaoAtual, direita->posicao))
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
    }

    // fantasma i
    if (EstaPresenteFantasma(baixo)) {
        if (!SaoIguaisPosicao(pacman->posicaoAtual, baixo->posicao)) AtualizaItemMapa(mapa, baixo->posicao, VAZIO);
        else AtualizaItemMapa(mapa, baixo->posicao, PACMAN);

        cloneB->linha += baixo->dx;
        if (FantasmaComeuComida(baixo)) {
            if (!SaoIguaisPosicao(baixo->posicaoAntiga, pacman->posicaoAtual)) 
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
    }

    // fantasma p
    if (EstaPresenteFantasma(cima)) {
        if (!SaoIguaisPosicao(pacman->posicaoAtual, cima->posicao)) AtualizaItemMapa(mapa, cima->posicao, VAZIO);
        else AtualizaItemMapa(mapa, cima->posicao, PACMAN);
        
        cloneC->linha += cima->dx;
        if (FantasmaComeuComida(cima)) {
            if (!SaoIguaisPosicao(cima->posicaoAntiga, pacman->posicaoAtual)) 
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
    }

    DesalocaPosicao(cloneB);
    DesalocaPosicao(cloneC);
    DesalocaPosicao(cloneE);
    DesalocaPosicao(cloneD);
}

bool EstaPresenteFantasma (tFantasma * fantasma) {
    return fantasma->presenteMapa;
}

void DesalocaFantasmaPresentes (tFantasma * fantasma) {
    if (fantasma == NULL) return;

    DesalocaPosicao(fantasma->posicao);
    DesalocaPosicao(fantasma->posicaoAntiga);
    free(fantasma);
}

