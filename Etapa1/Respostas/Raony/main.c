#include "tFantasma.h"
#include "tPacman.h"
#include "tArquivos.h"

#define DIRETORIO_MAX_SIZE 1001

#define COMIDA '*'
#define PORTAL '@'
#define PAREDE '#'
#define PACMAN '>'
#define VAZIO ' '

/**
 * Verifica as condicoes para cruzamento do fantasma com o pacman
 * \param pacman pacman
 * \param antiga posicao antiga do pacman
 * \param left fantasma que anda pela esquerda (inicialmente)
 * \param right fantasma que anda pela direita (inicialmente)
 * \param down fantasma que anda para baixo (inicialmente)
 * \param up fantasma que anda para cima (inicialmente)
 */
bool OcorreuCruzamento(tPacman * pacman, tPosicao * antiga, 
                       tFantasma * left, tFantasma *  right, tFantasma * down, tFantasma * up) {
        // posicoes atuais iguais
    if (SaoIguaisPosicao(ObtemPosicaoPacman(pacman), ObtemPosicaoAtualFantasma(left)) ||
        SaoIguaisPosicao(ObtemPosicaoPacman(pacman), ObtemPosicaoAtualFantasma(right)) ||
        SaoIguaisPosicao(ObtemPosicaoPacman(pacman), ObtemPosicaoAtualFantasma(down)) ||
        SaoIguaisPosicao(ObtemPosicaoPacman(pacman), ObtemPosicaoAtualFantasma(up)) ||

        // se a atualPacman = antigaFantasma && antigaFantasma = atualPacman
        (SaoIguaisPosicao(ObtemPosicaoPacman(pacman), ObtemPosicaoAntigaFantasma(left)) &&
        SaoIguaisPosicao(antiga, ObtemPosicaoAtualFantasma(left))) ||

        (SaoIguaisPosicao(ObtemPosicaoPacman(pacman), ObtemPosicaoAntigaFantasma(right)) &&
        SaoIguaisPosicao(antiga, ObtemPosicaoAtualFantasma(right))) ||

        (SaoIguaisPosicao(ObtemPosicaoPacman(pacman), ObtemPosicaoAntigaFantasma(down)) &&
        SaoIguaisPosicao(antiga, ObtemPosicaoAtualFantasma(down))) ||

        (SaoIguaisPosicao(ObtemPosicaoPacman(pacman), ObtemPosicaoAntigaFantasma(up)) &&
        SaoIguaisPosicao(antiga, ObtemPosicaoAtualFantasma(up)))
        ) return true;
    return false;
}

/**
 * Retorna o enum COMANDO digitado pelo teclaod (a, w, s, d)
 * \param movimento caractere do movimento
*/
COMANDO RetornaComando (char mov) {
    switch (mov) {
        case 'a':
            return MOV_ESQUERDA;

        case 'w':
            return MOV_CIMA;

        case 's':
            return MOV_BAIXO;

        case 'd':
            return MOV_DIREITA;
    }
}

/**
 * Atualiza a posicao do pacman no mapa
 * Caso o mapa possua tunel, verifica se o pacman esta sobrepondo um portal para tratar
 * 
 * \param mapa mapa
 * \param pacman pacman
 * \param antiga posicao antiga do pacman
 * \param comando comando de movimento (a, w, s, d)
 */
void AtualizaPacmanMapa(tMapa * mapa, tPacman * pacman, tPosicao * antiga, COMANDO comando) {

    if (PossuiTunelMapa(mapa)) { 
        if (!EntrouTunel(ObtemTunelMapa(mapa), ObtemPosicaoPacman(pacman))) AtualizaItemMapa(mapa, ObtemPosicaoPacman(pacman), VAZIO);
        else AtualizaItemMapa(mapa, ObtemPosicaoPacman(pacman), PORTAL);

    } else AtualizaItemMapa(mapa, ObtemPosicaoPacman(pacman), VAZIO);

    MovePacman(pacman, mapa, comando);
    AtualizaItemMapa(mapa, ObtemPosicaoPacman(pacman), PACMAN);
}

/**
 * Imprime o grid do mapa
 * \param mapa mapa
 * \param left fantasma que anda pela esquerda (inicialmente)
 * \param right fantasma que anda pela direita (inicialmente)
 * \param down fantasma que anda para baixo (inicialmente)
 * \param up fantasma que anda para cima (inicialmente)
 */
void ImprimeMapa(tMapa * mapa, tFantasma * left, tFantasma *  right, tFantasma * down, tFantasma * up) {
    for (int i = 0; i < ObtemNumeroLinhasMapa(mapa); i++) {
        for (int j = 0; j < ObtemNumeroColunasMapa(mapa); j++) {
            tPosicao * posicao = CriaPosicao(i, j);
            if (SaoIguaisPosicao(posicao, ObtemPosicaoAtualFantasma(left)) && EstaPresenteFantasma(left))
                printf("%c", LEFT_GHOST);

            else if (SaoIguaisPosicao(posicao, ObtemPosicaoAtualFantasma(right)) && EstaPresenteFantasma(right))
                printf("%c", RIGHT_GHOST);
            
            else if (SaoIguaisPosicao(posicao, ObtemPosicaoAtualFantasma(down)) && EstaPresenteFantasma(down))
                printf("%c", DOWN_GHOST);
            
            else if (SaoIguaisPosicao(posicao, ObtemPosicaoAtualFantasma(up)) && EstaPresenteFantasma(up))
                printf("%c", UP_GHOST);
            
            else printf("%c", mapa->grid[i][j]);
            DesalocaPosicao(posicao);
        }
        printf("\n");
    }
}

/**
 * Caso a posicao seja um fantasma, atualiza a posicao para vazio
 * \param mapa mapa
 * \param left fantasma que anda pela esquerda (inicialmente)
 * \param right fantasma que anda pela direita (inicialmente)
 * \param down fantasma que anda para baixo (inicialmente)
 * \param up fantasma que anda para cima (inicialmente)
 */
void RetiraFantasmasMapa (tMapa * mapa, tFantasma * left, tFantasma *  right, tFantasma * down, tFantasma * up) {
    for (int i = 0; i < ObtemNumeroLinhasMapa(mapa); i++) {
        for (int j = 0; j < ObtemNumeroColunasMapa(mapa); j++) {
            if (mapa->grid[i][j] == UP_GHOST || mapa->grid[i][j] == DOWN_GHOST ||
                mapa->grid[i][j] == RIGHT_GHOST || mapa->grid[i][j] == LEFT_GHOST) {
                    mapa->grid[i][j] = VAZIO;
            }
        }
    }
}

int main (int agrc, char * argv[]) { /* main oficial */
    if (agrc <= 1) {
        printf("ERRO: O diretorio de arquivos de configuracao nao foi informado\n");
        return 1;
    }

    char diretorio[DIRETORIO_MAX_SIZE];
    sprintf(diretorio, "%s", argv[1]);

// int main () { /* main para testes */
//     char diretorio[DIRETORIO_MAX_SIZE] = "Casos/02";

    /* cria os ponteiros necessarios para o jogo */
    tMapa * mapa = CriaMapa(diretorio);
    tPacman * pacman = CriaPacman(ObtemPosicaoItemMapa(mapa, PACMAN));

    tFantasma * left = CriaFantasmaPresente(mapa, LEFT_GHOST);
    tFantasma * right = CriaFantasmaPresente(mapa, RIGHT_GHOST);
    tFantasma * down = CriaFantasmaPresente(mapa, DOWN_GHOST);
    tFantasma * up = CriaFantasmaPresente(mapa, UP_GHOST);

    /* gera inicializacao, gera a trilha e retira os fantasmas do mapa */
    GeraArquivoInicializacao(mapa, pacman);
    RetiraFantasmasMapa(mapa, left, right, down, up);
    CriaTrilhaPacman(pacman, ObtemNumeroLinhasMapa(mapa), ObtemNumeroColunasMapa(mapa));
    AtualizaTrilhaPacman(pacman);
    

    char mov = '\0';
    while ( EstaVivoPacman(pacman) && 
            ObtemNumeroAtualMovimentosPacman(pacman) < ObtemNumeroMaximoMovimentosMapa(mapa) &&
            ObtemPontuacaoAtualPacman(pacman) < ObtemQuantidadeFrutasIniciaisMapa(mapa)) {

        /* clone de posicao temporaria para trabalhar */
        tPosicao * clone = ClonaPosicao(ObtemPosicaoPacman(pacman)); 

        scanf("%c%*c", &mov);
        printf("Estado do jogo apos o movimento '%c':\n", mov);

        AtualizaPacmanMapa(mapa, pacman, clone, RetornaComando(mov));
        MoveFantasmas(down, up, left, right, mapa, pacman);

        /* trata as condicoes de cruzamento entre fantasma e pacman */
        if (OcorreuCruzamento(pacman, clone, left, right, down, up)) {
            InsereNovoMovimentoSignificativoPacman(pacman, RetornaComando(mov), "fim de jogo por encostar em um fantasma");
            MataPacman(pacman);
            AtualizaItemMapa(mapa, ObtemPosicaoPacman(pacman), VAZIO);
        }
        
        ImprimeMapa(mapa, left, right, down, up);
        printf("Pontuacao: %d\n\n", ObtemPontuacaoAtualPacman(pacman));

        /* desaloca a posicao clone usada temporariamente */
        DesalocaPosicao(clone);
    }

    if (EstaVivoPacman(pacman) && ObtemPontuacaoAtualPacman(pacman) == ObtemQuantidadeFrutasIniciaisMapa(mapa)) printf("Voce venceu!\n");
    else printf("Game over!\n");
    printf("Pontuacao final: %d\n", ObtemPontuacaoAtualPacman(pacman));

    GeraArquivosInformativos(pacman);

    /* desaloca os ponteiros da partida */
    DesalocaMapa(mapa);
    DesalocaPacman(pacman);
    DesalocaFantasmaPresentes(left);
    DesalocaFantasmaPresentes(right);
    DesalocaFantasmaPresentes(down);
    DesalocaFantasmaPresentes(up);

    return 0;
}