#ifndef MATAFANTASMA_H_
#define MATAFANTASMA_H_

#include "tMapa.h"
#include "tPacman.h"
#include "tFantasma.h"

#define COMIDA '*'
#define PORTAL '@'
#define PAREDE '#'
#define PACMAN '>'
#define VAZIO ' '
#define SUPER_COMIDA '+'
#define MATA_FANTASMA 'x'

void ExecutaMataFantasma (tFantasma * baixo, tFantasma * cima, tFantasma * esquerda, 
                          tFantasma * direita, tFantasma * horizontal, tFantasma * vertical, 
                          tMapa * mapa, tPacman * pacman, tPosicao * antiga);
                
    
void PacmanComeuMataFantasma (tMapa * mapa, tPacman * pacman);

#endif