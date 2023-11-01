#include "tJogo.h"

tJogo* InicializaJogo(tMapa * mapa, tPacman * pacman, tFantasma * fb, tFantasma * fc, tFantasma * fi, tFantasma * fp) {
    tJogo * jogo = (tJogo *) malloc (sizeof(tJogo));
    jogo->fantasmaB = fb;
    jogo->fantasmaC = fc;
    jogo->fantasmaI = fi;
    jogo->fantasmaP = fp;

    jogo->mapa = mapa;
    jogo->pacman = pacman;

    jogo->qtdFantasmasMapa = EstaPresenteFantasma(fb) + EstaPresenteFantasma(fc) + EstaPresenteFantasma(fi) + EstaPresenteFantasma(fp);
    return jogo;
}

COMANDO LeMovimento() {
    char mov = '\0';
    while (1) {
        scanf("%c\n", &mov);

        switch (mov) {
        case 'a':
            return MOV_ESQUERDA;
            break;

        case 'd':
            return MOV_DIREITA;
            break;

        case 'w':
            return MOV_CIMA;
            break;

        case 's':
            return MOV_BAIXO;
            break;
        }
    }
}

void JogaJogo(tJogo * jogo) {
    while(1) {
        COMANDO movimento = LeMovimento();
        MovePacman(RetornaPacman(jogo), RetornaMapa(jogo), movimento);
        // MoveFantasmas(jogo);

        if (ObtemNumeroAtualMovimentosPacman(RetornaPacman(jogo)) > ObtemNumeroMaximoMovimentosMapa(RetornaMapa(jogo)) || 
            !EstaVivoPacman(RetornaPacman(jogo))) {
                printf("perdeu bebe");
                break;;

        } else if (ObtemPontuacaoAtualPacman(RetornaPacman(jogo)) == ObtemQuantidadeFrutasIniciaisMapa(RetornaMapa(jogo))) {
            printf("era p ganha");
            break;
        }
    }
}

tPacman* RetornaPacman(tJogo * jogo) {
    if (jogo->pacman != NULL) return jogo->pacman;
}

tMapa* RetornaMapa(tJogo * jogo) {
    if (jogo->mapa != NULL) return jogo->mapa;
}

tFantasma* RetornaFantasmaB(tJogo * jogo) {
    if (jogo->fantasmaB != NULL) return jogo->fantasmaB;
}

tFantasma* RetornaFantasmaC(tJogo * jogo) {
    if (jogo->fantasmaC != NULL) return jogo->fantasmaC;
}

tFantasma* RetornaFantasmaI(tJogo * jogo) {
    if (jogo->fantasmaI != NULL) return jogo->fantasmaI;
}

tFantasma* RetornaFantasmaP(tJogo * jogo) {
    if (jogo->fantasmaP != NULL) return jogo->fantasmaP;
}

int RetornaQtdFantasmas(tJogo * jogo) {
    return jogo->qtdFantasmasMapa;
}

void DesalocaJogo(tMapa * mapa, tPacman * pacman);