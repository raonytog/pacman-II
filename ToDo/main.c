#include "tPacman.h"
#include "utils.h"

#define DIRETORIO_MAX_SIZE 1001

int main (int agrc, char * argv[]) {
    if (agrc <= 1) {
        printf("ERRO: O diretorio de arquivos de configuracao nao foi informado\n");
        return 1;
    }

    char diretorio[DIRETORIO_MAX_SIZE];
    sprintf(diretorio, "%s", argv[1]);

    tMapa * mapa = CriaMapa(diretorio);

    //GeraInicializacao(mapa);

    tPosicao * posicaoPacman = ObtemPosicaoItemMapa(mapa, PACMAN);
    tPacman * pacman = CriaPacman(posicaoPacman);

    return 0;
}