#ifndef TBOMBA_H_
#define TBOMBA_H_

#include "tPosicao.h"
#include "tMapa.h"
#include "tPacman.h"
#include "tFantasma.h"
#include <stdlib.h>

#define DESARMADA '&'
#define CLOCK_3 '3'
#define CLOCK_2 '2'
#define CLOCK_1 '1'
#define EXPLODIU ' '

typedef struct {
    tPosicao * posicaoBomba;
    char aparencia;
    int acionada;
} tBomba;


tBomba * CriaBomba ();

bool ExisteBombaMapa (tBomba * bomba);

tPosicao * ObtemPosicaoBomba (tBomba * bomba);

bool EstaDesarmadaBomba (tBomba * bomba);

bool EstaAcionadaBomba (tBomba * bomba);

void ExplodeBomba (tBomba * bomba, tMapa * mapa, tPacman * pacman, 
                   tFantasma * baixo, tFantasma * cima, tFantasma * esquerda, 
                   tFantasma * direita, tFantasma * horizontal, tFantasma * vertical);

void DesalocaBomba (tBomba * bomba);

#endif