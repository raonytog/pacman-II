#include "tFantasma.h"
#include "tJogo.h"

void MoveFantasmas (tJogo * jogo) {
    printf("um dia mexe");
}

int EstaPresenteFantasma (tFantasma * fantasma) {
    return fantasma->presenteMapa;
}

tFantasma * CriaFantasma(tMapa * mapa, char simoblogia_fantasma) {
    switch (simoblogia_fantasma) {
        case FANT_B:
                tPosicao * posiB = ObtemPosicaoItemMapa(mapa, simoblogia_fantasma);
                tFantasma * fantB = (tFantasma *) malloc(sizeof(tFantasma));
                fantB->dx = 0;
                fantB->dy = -1;
                fantB->posicao = posiB;
                fantB->posicaoAntiga = posiB;
                if (posiB != NULL) fantB->presenteMapa = 1;
                else fantB->presenteMapa = 0;
                return fantB;
            break;

        case FANT_C:
                tPosicao * posiC = ObtemPosicaoItemMapa(mapa, simoblogia_fantasma);
                tFantasma * fantC = (tFantasma *) malloc(sizeof(tFantasma));
                fantC->dx = 0;
                fantC->dy = 1;
                fantC->posicao = posiC;
                fantC->posicaoAntiga = posiC;
                if (posiC != NULL) fantC->presenteMapa = 1;
                else fantC->presenteMapa = 0;
                return fantC;
            break;

        case FANT_I:
                tPosicao * posiI = ObtemPosicaoItemMapa(mapa, simoblogia_fantasma);
                tFantasma * fantI = (tFantasma *) malloc(sizeof(tFantasma));
                fantI->dx = 1;
                fantI->dy = 0;
                fantI->posicao = posiI;
                fantI->posicaoAntiga = posiI;
                if (posiI != NULL) fantI->presenteMapa = 1;
                else fantI->presenteMapa = 0;
                return fantI;
            break;

        case FANT_P:
                tPosicao * posiP = ObtemPosicaoItemMapa(mapa, simoblogia_fantasma);
                tFantasma * fantP = (tFantasma *) malloc(sizeof(tFantasma));
                fantP->dx = -1;
                fantP->dy = 0;
                fantP->posicao = posiP;
                fantP->posicaoAntiga = posiP;
                if (posiP != NULL) fantP->presenteMapa = 1;
                else fantP->presenteMapa = 0;
                return fantP;
            break;
    }
}