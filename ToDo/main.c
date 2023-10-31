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
    tPosicao * posicaoPacman = ObtemPosicaoItemMapa(mapa, PACMAN);
    tPacman * pacman = CriaPacman(posicaoPacman);

    GeraArquivoInicializacao(mapa, pacman);

    return 0;
}