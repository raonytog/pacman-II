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
    tPosicao * posicaoClone = ClonaPosicao(ObtemPosicaoPacman(pacman));
    switch (comando) {
        case ESQUERDA: //esquerda
            posicaoClone->coluna--;
            if (EncontrouParedeMapa(mapa, posicaoClone)) {
                pacman->nColisoesParedeEsquerda++;
                posicaoClone->coluna++;
                
            } else {
                if (EncontrouComidaMapa(mapa, posicaoClone))
                    pacman->nFrutasComidasEsquerda++;

                AtualizaItemMapa(mapa, posicaoClone, PACMAN);
            }

            pacman->nMovimentosEsquerda++;
            break;

        case DIREITA: // direita
            posicaoClone->coluna++;
            if (EncontrouParedeMapa(mapa, posicaoClone)) {
                pacman->nColisoesParedeDireita++;
                posicaoClone->coluna--;

            } else {
                if (EncontrouComidaMapa(mapa, posicaoClone)) 
                    pacman->nFrutasComidasDireita++;
                
                AtualizaItemMapa(mapa, posicaoClone, PACMAN);
            }

            pacman->nMovimentosDireita++;
            break;
        
        case CIMA: // cima
            posicaoClone->linha--;
            if (EncontrouParedeMapa(mapa, posicaoClone)) {
                pacman->nColisoesParedeCima++;
                posicaoClone->linha++;

            } else {
                if (EncontrouComidaMapa(mapa, posicaoClone)) 
                    pacman->nFrutasComidasCima++;
                    
                AtualizaItemMapa(mapa, posicaoClone, PACMAN);
            }

            pacman->nMovimentosCima++;
            break;

        case BAIXO: // baixo
            posicaoClone->linha++;
            if (EncontrouParedeMapa(mapa, posicaoClone)) {
                pacman->nColisoesParedeBaixo++;
                posicaoClone->linha--;

            } else {
                if (EncontrouComidaMapa(mapa, posicaoClone)) 
                    pacman->nFrutasComidasBaixo++;

                AtualizaItemMapa(mapa, posicaoClone, PACMAN);
            }
            
            pacman->nMovimentosBaixo++;
            break;
    }

    if (PossuiTunelMapa(mapa) && EntrouTunel(ObtemTunelMapa(mapa), posicaoClone)) {
        LevaFinalTunel(ObtemTunelMapa(mapa), posicaoClone);
        AtualizaPosicao(pacman->posicaoAtual, posicaoClone);
        AtualizaTrilhaPacman(pacman);
    }

    AtualizaPosicao(pacman->posicaoAtual, posicaoClone);
    DesalocaPosicao(posicaoClone);
    AtualizaTrilhaPacman(pacman);
}

void CriaTrilhaPacman(tPacman* pacman, int nLinhas, int nColunas) {
    printf("ADORO SEXO");
    if (pacman->trilha != NULL) return;

    // atribui os numeros de linhas e colunas
    pacman->nLinhasTrilha = nLinhas;
    pacman->nColunasTrilha = nColunas;

    // aloca espaco pra trilha
    pacman->trilha = (int **) malloc (nLinhas * sizeof(int *));
    for (int i = 0; i < nLinhas; i++) {
        pacman->trilha[i] = (int *) malloc (nColunas * sizeof(int));
        for (int j = 0; j < nColunas; j++) {
            pacman->trilha[i][j] = -1;
        }
    }
}

void AtualizaTrilhaPacman(tPacman* pacman) {
    int row = ObtemLinhaPosicao(ObtemPosicaoPacman(pacman)), col = ObtemColunaPosicao(ObtemPosicaoPacman(pacman));
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
            if (pacman->trilha[i][j] == -1) fprintf(fTrilha, "#");
            else fprintf(fTrilha, "%d ", pacman->trilha[i][j]);

            // nao printa o espaco na ultima coluna
            if (j != pacman->nColunasTrilha-1) fprintf(fTrilha, " "); 
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

    // desaloca o pacman em si
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