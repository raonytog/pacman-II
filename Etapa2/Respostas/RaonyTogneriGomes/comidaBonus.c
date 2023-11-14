#include "comidaBonus.h"

void TrataComidaBonus (tPacman * pacman, tMapa * mapa, tPosicao * comidaBonus) {
        if (ComeuSuperComida(pacman)) {
            if (ObtemRoundsRestantes(pacman) == 0 && EncontrouParedeMapa(mapa, ObtemPosicaoPacman(pacman)))
                MataPacman(pacman);
        }

        // trata comida da parede
        if (comidaBonus != NULL) {
            if (SaoIguaisPosicao(ObtemPosicaoPacman(pacman), comidaBonus)) {
                DefinePacmanComeuSuperComida(pacman);
                AtualizaItemMapa(mapa, comidaBonus, VAZIO);
        }
    }
}