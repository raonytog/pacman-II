#include "tSaidas.h"

void GeraArquivoInicializacao (tMapa * mapa, tPacman * pacman) {
    FILE * fInicializacao = NULL;
    fInicializacao = fopen("inicializacao.txt", "w");
    if (!fInicializacao) {
        printf("diretorio da saida da trilha invalido\n");
        exit(1);
    }

    for (int i = 0; i < ObtemNumeroLinhasMapa(mapa); i++) {
        for (int j = 0; j < ObtemNumeroColunasMapa(mapa); j++)
            fprintf(fInicializacao, "%c", mapa->grid[i][j]);
        fprintf(fInicializacao, "\n");
    }
    fprintf(fInicializacao, "Pac-Man comecara o jogo na linha %d e coluna %d\n", 
            ObtemLinhaPosicao(ObtemPosicaoPacman(pacman))+1, ObtemColunaPosicao(ObtemPosicaoPacman(pacman))+1);

    fclose(fInicializacao);
}