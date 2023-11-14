#ifndef TBOMBA_H_
#define TBOMBA_H_

#include "tPosicao.h"
#include "tMapa.h"
#include "tFantasma.h"
#include "tPacman.h"

#define DESARMADA '&'
#define CLOCK_1 '1'
#define CLOCK_2 '2'
#define CLOCK_3 '3'

typedef struct {
    tPosicao * posicao;
    int acionada;
    char aparecia;
} tBomba;

tBomba * CriaBomba (tMapa * mapa);

int EstaDesarmadaBomba (tBomba * bomba);

int EstaArmadaBomba(tBomba * bomba);

void ExplodeBomba (tBomba * bomba, tMapa * mapa, tFantasma * left, 
                   tFantasma *  right, tFantasma * down, tFantasma * up, 
                   tFantasma * hori, tFantasma * verti, tPacman * pacman);

void DesalocaBomba (tBomba * bomba);

tPosicao * RetornaPosicaoBomba (tBomba * bomba);

#endif