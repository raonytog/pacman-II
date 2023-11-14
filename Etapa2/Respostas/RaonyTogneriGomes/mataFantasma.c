#include "mataFantasma.h"

void PacmanComeuMataFantasma (tMapa * mapa, tPacman * pacman) {
    tPosicao * mataFant = ObtemPosicaoItemMapa(mapa, MATA_FANTASMA);
    if (mataFant == NULL) return;
    
    if (SaoIguaisPosicao(mataFant, ObtemPosicaoPacman(pacman))) {
        DefinePacmanComeuMataFantasma(pacman);
        AtualizaItemMapa(mapa, mataFant, VAZIO);
        DesalocaPosicao(mataFant);
        return;
    }

    DesalocaPosicao(mataFant);
    return;
}

void ExecutaMataFantasma (tFantasma * baixo, tFantasma * cima, tFantasma * esquerda, 
                          tFantasma * direita, tFantasma * horizontal, tFantasma * vertical, 
                          tMapa * mapa, tPacman * pacman, tPosicao * antiga) {
    if (!ComeuMataFantasma(pacman)) return;

    if (SaoIguaisPosicao(ObtemPosicaoPacman(pacman), ObtemPosicaoAtualFantasma(direita))) {
        MataFantasma(direita);
        ResetaMataFantasma(pacman);
    }

    else if (SaoIguaisPosicao(ObtemPosicaoPacman(pacman), ObtemPosicaoAtualFantasma(esquerda))) {
        MataFantasma(esquerda);
        ResetaMataFantasma(pacman);
    }

    else if (SaoIguaisPosicao(ObtemPosicaoPacman(pacman), ObtemPosicaoAtualFantasma(cima))) {
        MataFantasma(cima);
        ResetaMataFantasma(pacman);
    }

    else if (SaoIguaisPosicao(ObtemPosicaoPacman(pacman), ObtemPosicaoAtualFantasma(baixo))) {
        MataFantasma(baixo);
        ResetaMataFantasma(pacman);
    }

    else if (SaoIguaisPosicao(ObtemPosicaoPacman(pacman), ObtemPosicaoAtualFantasma(horizontal))) {
        MataFantasma(horizontal);
        ResetaMataFantasma(pacman);
    }

    else if (SaoIguaisPosicao(ObtemPosicaoPacman(pacman), ObtemPosicaoAtualFantasma(vertical))) {

        MataFantasma(vertical);
        ResetaMataFantasma(pacman);
    }


    DecrementaTimerMataFantasma(pacman);
}