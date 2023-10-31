#include "utils.h"

bool EstaForaDosLimites(tMapa * mapa, tPosicao * posicao) {
    if (ObtemColunaPosicao(posicao) > ObtemNumeroColunasMapa(mapa) || 
        ObtemLinhaPosicao(posicao)  > ObtemNumeroLinhasMapa(mapa) || 
        ObtemLinhaPosicao(posicao) < 0 || ObtemColunaPosicao(posicao) < 0) return true;
    return false;
}

bool EhNullGridOuMapa (tMapa * mapa) {
    return (mapa == NULL || mapa->grid == NULL);
}

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
    fprintf("Pac-Man comecara o jogo na linha %d e coluna %d\n", ObtemLinhaPosicao(ObtemPosicaoPacman(pacman)), ObtemColunaPosicao(ObtemPosicaoPacman(pacman)));

    fclose(fInicializacao);
}