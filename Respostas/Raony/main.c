#include "tFantasma.h"
#include "tPacman.h"
#include "tPosicao.h"

#define DIRETORIO_MAX_SIZE 1001

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

    tFantasma * fb = CriaFantasma(mapa, FANT_B);
    tFantasma * fc = CriaFantasma(mapa, FANT_C);
    tFantasma * fi = CriaFantasma(mapa, FANT_I);
    tFantasma * fp = CriaFantasma(mapa, FANT_P);

    tJogo * jogo = InicializaJogo(mapa, pacman, fb, fc, fi, fp);

    GeraArquivoInicializacao(mapa, pacman);
    
    JogaJogo(jogo);

    return 0;
}