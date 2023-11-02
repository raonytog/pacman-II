#include "tFantasma.h"
#include "tPacman.h"

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

COMANDO LeMovimento() {
    char mov = '\0';
    while (1) {
        scanf("%c%*c", &mov);

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

    tFantasma * left = CriaFantasma(mapa, LEFT_GHOST);
    tFantasma * right = CriaFantasma(mapa, RIGHT_GHOST);
    tFantasma * down = CriaFantasma(mapa, DOWN_GHOST);
    tFantasma * up = CriaFantasma(mapa, UP_GHOST);

    GeraArquivoInicializacao(mapa, pacman);

    while (1) {
        COMANDO movimento = LeMovimento();
        printf("Estado do jogo apos o movimento '%c':\n", movimento);
        MovePacman(pacman, mapa, movimento);
        MoveFantasmas(down, up, left, right, mapa);

        // verifica se ganhou
        // se morreu


    }
    
    DesalocaMapa(mapa);
    
    DesalocaPacman(pacman);

    DesalocaFantasma(left);
    DesalocaFantasma(right);
    DesalocaFantasma(down);
    DesalocaFantasma(up);

    return 0;
}