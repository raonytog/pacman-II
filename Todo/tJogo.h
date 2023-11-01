#ifndef TJOGO_H_
#define TJOGO_H_

#include "tPacman.h"
#include "tFantasma.h"
#include "tMapa.h"

#define VIVO 1 
#define MORTO 0 

#define COMIDA '*'
#define PORTAL '@'
#define PAREDE '#'
#define PACMAN '>'
#define VAZIO ' '

typedef struct tJogo{
    tMapa * mapa;

    tPacman * pacman;

    tFantasma * fantasmaB;
    tFantasma * fantasmaC;
    tFantasma * fantasmaI;
    tFantasma * fantasmaP;

    int qtdFantasmasMapa;
} tJogo;

tPacman* RetornaPacman(tJogo * jogo);

tMapa* RetornaMapa(tJogo * jogo);

tFantasma* RetornaFantasmaB(tJogo * jogo);

tFantasma* RetornaFantasmaC(tJogo * jogo);

tFantasma* RetornaFantasmaI(tJogo * jogo);

tFantasma* RetornaFantasmaP(tJogo * jogo);

int RetornaQtdFantasmas(tJogo * jogo);

tJogo* InicializaJogo(tMapa * mapa, tPacman * pacman, tFantasma * fb, tFantasma * fc, tFantasma * fi, tFantasma * fp);

COMANDO LeMovimento();

void JogaJogo(tJogo * jogo);

void DesalocaJogo(tMapa * mapa, tPacman * pacman);

#endif
