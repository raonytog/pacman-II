#include "tFantasma.h"
#include "tPacman.h"

#define DIRETORIO_MAX_SIZE 1001

#define COMIDA '*'
#define PORTAL '@'
#define PAREDE '#'
#define PACMAN '>'
#define VAZIO ' '

bool OcorreuCruzamento(tPacman * pacman, tPacman * pacmanAntigo, 
                       tFantasma * left, tFantasma *  right, tFantasma * down, tFantasma * up) {
        // posicoes atuais iguais
    if (SaoIguaisPosicao(ObtemPosicaoPacman(pacman), ObtemPosicaoAtualFantasma(left)) ||
        SaoIguaisPosicao(ObtemPosicaoPacman(pacman), ObtemPosicaoAtualFantasma(right)) ||
        SaoIguaisPosicao(ObtemPosicaoPacman(pacman), ObtemPosicaoAtualFantasma(down)) ||
        SaoIguaisPosicao(ObtemPosicaoPacman(pacman), ObtemPosicaoAtualFantasma(up)) ||

        // se a atualPacman = antigaFantasma && antigaFantasma = atualPacman
        (SaoIguaisPosicao(ObtemPosicaoPacman(pacman), ObtemPosicaoAntigaFantasma(left)) &&
        SaoIguaisPosicao(ObtemPosicaoPacman(pacmanAntigo), ObtemPosicaoAtualFantasma(left))) ||

        (SaoIguaisPosicao(ObtemPosicaoPacman(pacman), ObtemPosicaoAntigaFantasma(right)) &&
        SaoIguaisPosicao(ObtemPosicaoPacman(pacmanAntigo), ObtemPosicaoAtualFantasma(right))) ||

        (SaoIguaisPosicao(ObtemPosicaoPacman(pacman), ObtemPosicaoAntigaFantasma(down)) &&
        SaoIguaisPosicao(ObtemPosicaoPacman(pacmanAntigo), ObtemPosicaoAtualFantasma(down))) ||

        (SaoIguaisPosicao(ObtemPosicaoPacman(pacman), ObtemPosicaoAntigaFantasma(up)) &&
        SaoIguaisPosicao(ObtemPosicaoPacman(pacmanAntigo), ObtemPosicaoAtualFantasma(up)))
        // // atual do pacman igual antiga do fantasma
        // SaoIguaisPosicao(ObtemPosicaoPacman(pacman), ObtemPosicaoAntigaFantasma(left)) ||
        // SaoIguaisPosicao(ObtemPosicaoPacman(pacman), ObtemPosicaoAntigaFantasma(right)) ||
        // SaoIguaisPosicao(ObtemPosicaoPacman(pacman), ObtemPosicaoAntigaFantasma(down)) ||
        // SaoIguaisPosicao(ObtemPosicaoPacman(pacman), ObtemPosicaoAntigaFantasma(up)) ||

        // // antiga do pacman igual atual do fantasma
        // SaoIguaisPosicao(ObtemPosicaoPacman(pacmanAntigo), ObtemPosicaoAntigaFantasma(left)) ||
        // SaoIguaisPosicao(ObtemPosicaoPacman(pacmanAntigo), ObtemPosicaoAntigaFantasma(right)) ||
        // SaoIguaisPosicao(ObtemPosicaoPacman(pacmanAntigo), ObtemPosicaoAntigaFantasma(down)) ||
        // SaoIguaisPosicao(ObtemPosicaoPacman(pacmanAntigo), ObtemPosicaoAntigaFantasma(up))
        ) return true;
    return false;
}

void AtualizaPacmanMapa(tMapa * mapa, tPacman * pacman, COMANDO comando) {
    tPosicao * antiga = ObtemPosicaoItemMapa(mapa, PACMAN);
    MovePacman(pacman, mapa, comando);
    AtualizaItemMapa(mapa, antiga, VAZIO);
    AtualizaItemMapa(mapa, ObtemPosicaoPacman(pacman), PACMAN);
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
    fprintf(fInicializacao, "Pac-Man comecara o jogo na linha %d e coluna %d\n", 
            ObtemLinhaPosicao(ObtemPosicaoPacman(pacman))+1, ObtemColunaPosicao(ObtemPosicaoPacman(pacman))+1);

    fclose(fInicializacao);
}

void ImprimeMapa(tMapa * mapa) {
    for (int i = 0; i < ObtemNumeroLinhasMapa(mapa); i++) {
        for (int j = 0; j < ObtemNumeroColunasMapa(mapa); j++) {
            printf("%c", mapa->grid[i][j]);
        }
        printf("\n");
    }
}

COMANDO RetornaComando (char mov) {
    switch (mov) {
        case 'a':
            return MOV_ESQUERDA;
            break;

        case 'w':
            return MOV_CIMA;
            break;

        case 's':
            return MOV_BAIXO;
            break;

        case 'd':
            return MOV_DIREITA;
            break;
    }
}

// int main (int agrc, char * argv[]) {
//     if (agrc <= 1) {
//         printf("ERRO: O diretorio de arquivos de configuracao nao foi informado\n");
//         return 1;
//     }

//     char diretorio[DIRETORIO_MAX_SIZE];
//     sprintf(diretorio, "%s", argv[1]);

int main () {
    char diretorio[DIRETORIO_MAX_SIZE] = "Casos/07";

    tMapa * mapa = CriaMapa(diretorio);
    tPacman * pacman = CriaPacman(ObtemPosicaoItemMapa(mapa, PACMAN));

    tFantasma * left = CriaFantasma(mapa, LEFT_GHOST);
    tFantasma * right = CriaFantasma(mapa, RIGHT_GHOST);
    tFantasma * down = CriaFantasma(mapa, DOWN_GHOST);
    tFantasma * up = CriaFantasma(mapa, UP_GHOST);

    GeraArquivoInicializacao(mapa, pacman);
    CriaTrilhaPacman(pacman, ObtemNumeroLinhasMapa(mapa), ObtemNumeroColunasMapa(mapa));

    char mov = '\0';
    while (EstaVivoPacman(pacman) && ObtemNumeroAtualMovimentosPacman(pacman) < ObtemNumeroMaximoMovimentosMapa(mapa)) {
        tPacman * clone = ClonaPacman(pacman);

        // if (ObtemNumeroAtualMovimentosPacman(pacman) == ObtemNumeroMaximoMovimentosMapa(mapa)) {
        //     printf("%d %d", ObtemNumeroAtualMovimentosPacman(pacman), ObtemNumeroMaximoMovimentosMapa(mapa));
        // }

        scanf("%c%*c", &mov);
        printf("Estado do jogo apos o movimento '%c':\n", mov);

        AtualizaPacmanMapa(mapa, pacman, RetornaComando(mov));
        MoveFantasmas(down, up, left, right, mapa);

        ImprimeMapa(mapa);
        printf("Pontuacao: %d\n\n", ObtemPontuacaoAtualPacman(pacman));

        if (OcorreuCruzamento(pacman, clone, left, right, down, up)) {
            InsereNovoMovimentoSignificativoPacman(pacman, RetornaComando(mov), "fim de jogo por encostar em um fantasma");
            MataPacman(pacman);
        }

        DesalocaPacman(clone);
    }

    if (EstaVivoPacman(pacman)) printf("Voce venceu!\n");
    else printf("Game over!\n");

    printf("Pontuacao final: %d\n", ObtemPontuacaoAtualPacman(pacman));


    
    
    DesalocaMapa(mapa);
    
    DesalocaPacman(pacman);

    DesalocaFantasma(left);
    DesalocaFantasma(right);
    DesalocaFantasma(down);
    DesalocaFantasma(up);

    return 0;
}