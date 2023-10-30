#include "tPacman.h"

/*
*
*       confg launch pro diretorio
*
*/

/*
*       ,
*       ARGS: 
*       "*.o"
*/

#define VIVO 1 
#define MORTO 0 

#define COMIDA '*'
#define PORTAL '@'
#define PAREDE '#'
#define PACMAN '>'

/* tipo para auxiliar o movimento */
typedef enum {
    ESQUERDA = 0,
    CIMA = 1,
    BAIXO = 2,
    DIREITA = 3 
} MOVIMENTOS;


tPacman* CriaPacman(tPosicao* posicao) {
    tPacman * pacman = (tPacman*)malloc(sizeof(tPacman));
    if (pacman == NULL || posicao == NULL) return NULL;

    // dump de inicializacoes
    pacman->posicaoAtual = posicao;

    pacman->estaVivo = 1;

    pacman->nColisoesParedeBaixo = 0;
    pacman->nColisoesParedeCima = 0;
    pacman->nColisoesParedeDireita = 0;
    pacman->nColisoesParedeEsquerda = 0;

    pacman->nFrutasComidasBaixo = 0;
    pacman->nFrutasComidasCima = 0;
    pacman->nFrutasComidasDireita = 0;
    pacman->nFrutasComidasEsquerda = 0;

    pacman->nMovimentosBaixo = 0;
    pacman->nMovimentosCima = 0;
    pacman->nMovimentosDireita = 0;
    pacman->nMovimentosEsquerda = 0;

    pacman->nMovimentosSignificativos = 0;

    pacman->trilha = NULL;

    pacman->historicoDeMovimentosSignificativos = (tMovimento **) malloc (sizeof(tMovimento *));
    if (pacman->historicoDeMovimentosSignificativos == NULL) {
        printf("Alocacao indevida no historico em tPacman.c\n");
        exit(1);
    }

    return pacman;
}

tPacman* ClonaPacman(tPacman* pacman) {
    tPacman * clone = CriaPacman(ObtemPosicaoPacman(pacman));
    if (pacman == NULL || ObtemPosicaoPacman(pacman) == NULL) return NULL;
    return clone;
}

tMovimento** ClonaHistoricoDeMovimentosSignificativosPacman(tPacman* pacman) {
    tMovimento ** movClone = (tMovimento **) malloc(sizeof(tMovimento *));
    for (int i = 0; i < ObtemNumeroMovimentosSignificativosPacman(pacman); i++) {
        movClone[i] = CriaMovimento( ObtemNumeroMovimento(pacman->historicoDeMovimentosSignificativos[i]), 
                                     ObtemComandoMovimento(pacman->historicoDeMovimentosSignificativos[i]), 
                                     ObtemAcaoMovimento(pacman->historicoDeMovimentosSignificativos[i]) );
    }

    return movClone;
}

tPosicao* ObtemPosicaoPacman(tPacman* pacman) {
    return pacman->posicaoAtual;
}

int EstaVivoPacman(tPacman* pacman) {
    return pacman->estaVivo;
}

void MovePacman(tPacman* pacman, tMapa* mapa, COMANDO comando) {
    tPosicao * pClone = ClonaPosicao(ObtemPosicaoPacman(pacman));
    switch (comando) {
        case ESQUERDA: //esquerda
            pClone->coluna--;
            if (EncontrouParedeMapa(mapa, pClone)) {
                pacman->nColisoesParedeEsquerda++;

            } else {
                AtualizaItemMapa(mapa, ObtemPosicaoPacman(pacman), PACMAN);
                pacman->nMovimentosEsquerda++;
            }
            
            if (EncontrouComidaMapa(mapa, ObtemPosicaoPacman(pacman))) {
                pacman->nFrutasComidasEsquerda++;
            }
            break;
        
        case CIMA: // cima
            pClone->linha--;
            if (EncontrouParedeMapa(mapa, pClone)) {
                pacman->nColisoesParedeCima++;

            } else {
                AtualizaItemMapa(mapa, ObtemPosicaoPacman(pacman), PACMAN);
                pacman->nMovimentosCima++;
            }
            
            if (EncontrouComidaMapa(mapa, ObtemPosicaoPacman(pacman))) {
                pacman->nFrutasComidasCima++;
            }
            break;

        case BAIXO: // baixo
            pClone->linha++;
            if (EncontrouParedeMapa(mapa, pClone)) {
                pacman->nColisoesParedeBaixo++;

            } else {
                AtualizaItemMapa(mapa, ObtemPosicaoPacman(pacman), PACMAN);
                pacman->nMovimentosBaixo++;
            }
            
            if (EncontrouComidaMapa(mapa, ObtemPosicaoPacman(pacman))) {
                pacman->nFrutasComidasBaixo++;
            }
            break;

        case DIREITA: // direita
            pClone->coluna++;
            if (EncontrouParedeMapa(mapa, pClone)) {
                pacman->nColisoesParedeDireita++;

            } else {
                AtualizaItemMapa(mapa, ObtemPosicaoPacman(pacman), PACMAN);
                pacman->nMovimentosDireita++;
            }
            
            if (EncontrouComidaMapa(mapa, ObtemPosicaoPacman(pacman))) {
                pacman->nFrutasComidasDireita++;
            }
            break;
    }

    if (EntrouTunel(ObtemTunelMapa(mapa), ObtemPosicaoPacman(pacman))) {
        LevaFinalTunel(ObtemTunelMapa(mapa), ObtemPosicaoPacman(pacman));
    }

    AtualizaPosicao(pacman->posicaoAtual, pClone);
    DesalocaPosicao(pClone);
    AtualizaTrilhaPacman(pacman);
}

void CriaTrilhaPacman(tPacman* pacman, int nLinhas, int nColunas) {
    if (pacman->trilha != NULL) return;

    pacman->trilha = (int **) malloc (nLinhas * sizeof(int *));
    for (int i = 0; i < nLinhas; i++) {
        pacman->trilha[i] = (int *) malloc (nColunas * sizeof(int));
    }

    for (int i = 0; i < nLinhas; i++) {
        for (int j = 0; j < nColunas; j++) {
            pacman->trilha[i][j] = -1;
        }
    }
}

void AtualizaTrilhaPacman(tPacman* pacman) {
    int row = ObtemLinhaPosicao(ObtemPosicaoPacman(pacman));
    int col = ObtemColunaPosicao(ObtemPosicaoPacman(pacman));
    pacman->trilha[row][col] = ObtemNumeroAtualMovimentosPacman(pacman);
}

void SalvaTrilhaPacman(tPacman* pacman) {
    FILE * fTrilha = NULL;
    fTrilha = fopen("trilha.txt", "w");
    if (!fTrilha) {
        printf("diretorio da saida da trilha invalido\n");
        exit(1);
    }

    for (int i = 0; i < pacman->nLinhasTrilha; i++) {
        for (int j = 0; j < pacman->nColunasTrilha; j++) {
            if (pacman->trilha[i][j] == -1) {
                fprintf(fTrilha,"#");
                if (j != pacman->nColunasTrilha-1) fprintf(fTrilha, " "); // nao printa o espaco na ultima coluna
            }

            else fprintf(fTrilha, "%d ", pacman->trilha[i][j]);
        }
        fprintf(fTrilha, "\n");
    }
    fclose(fTrilha);
}

void InsereNovoMovimentoSignificativoPacman(tPacman* pacman, COMANDO comando, const char* acao) {
    tMovimento * novoMov = CriaMovimento(ObtemNumeroAtualMovimentosPacman(pacman), comando, acao);
    pacman->nMovimentosSignificativos++;
    pacman->historicoDeMovimentosSignificativos = (tMovimento **) realloc (pacman->historicoDeMovimentosSignificativos, pacman->nMovimentosSignificativos * sizeof(tMovimento *));
    pacman->historicoDeMovimentosSignificativos[ObtemNumeroMovimentosSignificativosPacman(pacman) - 1] = novoMov;
}

void MataPacman(tPacman* pacman) {
    pacman->estaVivo = MORTO;
}

void DesalocaPacman(tPacman* pacman) {
    if (pacman == NULL) return;

    // desaloca posicao
    DesalocaPosicao(pacman->posicaoAtual);

    // desaloca movimento
    for (int i = 0; i < pacman->nMovimentosSignificativos; i++)
        DesalocaMovimento(pacman->historicoDeMovimentosSignificativos[i]);
    free(pacman->historicoDeMovimentosSignificativos);

    // desaloca trilha
    for (int i = 0; i < pacman->nLinhasTrilha; i++)
        free(pacman->trilha[i]);
    free(pacman->trilha);

    free(pacman);
}

int ObtemNumeroAtualMovimentosPacman(tPacman* pacman) {
    return ObtemNumeroMovimentosBaixoPacman(pacman) + ObtemNumeroMovimentosCimaPacman(pacman) + 
           ObtemNumeroMovimentosEsquerdaPacman(pacman) + ObtemNumeroMovimentosDireitaPacman(pacman);
}

int ObtemNumeroMovimentosSemPontuarPacman(tPacman* pacman) {
    return ObtemNumeroAtualMovimentosPacman(pacman) - ObtemPontuacaoAtualPacman(pacman);
}

int ObtemNumeroColisoesParedePacman(tPacman* pacman) {
    return ObtemNumeroColisoesParedeBaixoPacman(pacman) + ObtemNumeroColisoesParedeCimaPacman(pacman) +
           ObtemNumeroColisoesParedeEsquerdaPacman(pacman) + ObtemNumeroColisoesParedeDireitaPacman(pacman);
}

int ObtemNumeroMovimentosBaixoPacman(tPacman* pacman) {
    return pacman->nMovimentosBaixo;
}

int ObtemNumeroFrutasComidasBaixoPacman(tPacman* pacman) {
    return pacman->nFrutasComidasBaixo;
}

int ObtemNumeroColisoesParedeBaixoPacman(tPacman* pacman) {
    return pacman->nColisoesParedeBaixo;
}

int ObtemNumeroMovimentosCimaPacman(tPacman* pacman) {
    return pacman->nMovimentosCima;
}

int ObtemNumeroFrutasComidasCimaPacman(tPacman* pacman) {
    return pacman->nFrutasComidasCima;
}

int ObtemNumeroColisoesParedeCimaPacman(tPacman* pacman) {
    return pacman->nColisoesParedeCima;
}

int ObtemNumeroMovimentosEsquerdaPacman(tPacman* pacman) {
    return pacman->nMovimentosEsquerda;
}

int ObtemNumeroFrutasComidasEsquerdaPacman(tPacman* pacman) {
    return pacman->nFrutasComidasEsquerda;
}

int ObtemNumeroColisoesParedeEsquerdaPacman(tPacman* pacman) {
    return pacman->nColisoesParedeEsquerda;
}

int ObtemNumeroMovimentosDireitaPacman(tPacman* pacman) {
    return pacman->nMovimentosDireita;
}

int ObtemNumeroFrutasComidasDireitaPacman(tPacman* pacman) {
    return pacman->nFrutasComidasDireita;
}

int ObtemNumeroColisoesParedeDireitaPacman(tPacman* pacman) {
    return pacman->nColisoesParedeDireita;
}

int ObtemNumeroMovimentosSignificativosPacman(tPacman* pacman) {
    if (EstaVivoPacman(pacman)) return ObtemPontuacaoAtualPacman(pacman) + ObtemNumeroColisoesParedePacman(pacman);
    else return ObtemPontuacaoAtualPacman(pacman) + ObtemNumeroColisoesParedePacman(pacman) + 1;
}

int ObtemPontuacaoAtualPacman(tPacman* pacman) {
    return ObtemNumeroFrutasComidasBaixoPacman(pacman) + ObtemNumeroFrutasComidasCimaPacman(pacman) +
           ObtemNumeroFrutasComidasEsquerdaPacman(pacman) + ObtemNumeroFrutasComidasDireitaPacman(pacman);
}