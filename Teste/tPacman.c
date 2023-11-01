#include "tPacman.h"

#define VIVO 1 
#define MORTO 0 

#define COMIDA '*'
#define PORTAL '@'
#define PAREDE '#'
#define PACMAN '>'
#define VAZIO ' '

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

    pacman->historicoDeMovimentosSignificativos = NULL;

    return pacman;
}

tPacman* ClonaPacman(tPacman* pacman) {
    tPacman * clone = malloc (sizeof(tPacman));
    clone->posicaoAtual = pacman->posicaoAtual;
    clone->trilha = NULL;
    clone->historicoDeMovimentosSignificativos = NULL;
    return clone;
}

tMovimento** ClonaHistoricoDeMovimentosSignificativosPacman(tPacman* pacman) {
    tMovimento ** movClone = (tMovimento **) malloc(ObtemNumeroMovimentosSignificativosPacman(pacman) * sizeof(tMovimento *));
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
    int bateuParede = 0;
    tPosicao * posicaoClone = ClonaPosicao(ObtemPosicaoPacman(pacman));
    switch (comando) {
        case ESQUERDA: //esquerda (a)
            posicaoClone->coluna--;
            pacman->nMovimentosEsquerda++;
            if (EncontrouParedeMapa(mapa, posicaoClone)) {
                bateuParede = 1;
                pacman->nColisoesParedeEsquerda++;
                posicaoClone->coluna++;
                InsereNovoMovimentoSignificativoPacman(pacman, comando, "colidiu com a parede");
                
            } else {
                if (EncontrouComidaMapa(mapa, posicaoClone)) {
                    pacman->nFrutasComidasEsquerda++;
                    InsereNovoMovimentoSignificativoPacman(pacman, comando, "pegou comida");
                    AtualizaItemMapa(mapa, posicaoClone, VAZIO);
                }
            }
            break;

        case DIREITA: // direita (d)
            posicaoClone->coluna++;
            pacman->nMovimentosDireita++;
            if (EncontrouParedeMapa(mapa, posicaoClone)) {
                bateuParede = 1;
                pacman->nColisoesParedeDireita++;   
                posicaoClone->coluna--;
                InsereNovoMovimentoSignificativoPacman(pacman, comando, "colidiu com a parede");

            } else {
                if (EncontrouComidaMapa(mapa, posicaoClone)) {
                    pacman->nFrutasComidasDireita++;
                    InsereNovoMovimentoSignificativoPacman(pacman, comando, "pegou comida");
                    AtualizaItemMapa(mapa, posicaoClone, VAZIO);
                }
            }
            break;
        
        case CIMA: // cima (w)
            posicaoClone->linha--;
            pacman->nMovimentosCima++;
            if (EncontrouParedeMapa(mapa, posicaoClone)) {
                bateuParede = 1;
                pacman->nColisoesParedeCima++;
                posicaoClone->linha++;
                InsereNovoMovimentoSignificativoPacman(pacman, comando, "colidiu com a parede");

            } else {
                if (EncontrouComidaMapa(mapa, posicaoClone)) {
                    pacman->nFrutasComidasCima++;
                    InsereNovoMovimentoSignificativoPacman(pacman, comando, "pegou comida");
                    AtualizaItemMapa(mapa, posicaoClone, VAZIO);
                }
            }
            break;

        case BAIXO: // baixo (s)
            posicaoClone->linha++;
            pacman->nMovimentosBaixo++;
            if (EncontrouParedeMapa(mapa, posicaoClone)) {
                bateuParede = 1;
                pacman->nColisoesParedeBaixo++;
                posicaoClone->linha--;
                InsereNovoMovimentoSignificativoPacman(pacman, comando, "colidiu com a parede");

            } else {
                if (EncontrouComidaMapa(mapa, posicaoClone)) {
                    printf("PEGOU COMIDAA");
                    pacman->nFrutasComidasBaixo++;
                    InsereNovoMovimentoSignificativoPacman(pacman, comando, "pegou comida");
                    AtualizaItemMapa(mapa, posicaoClone, VAZIO);
                }
            }
            break;
    }

    AtualizaPosicao(pacman->posicaoAtual, posicaoClone);
    AtualizaTrilhaPacman(pacman);

    if (PossuiTunelMapa(mapa)) {
        if (EntrouTunel(ObtemTunelMapa(mapa), posicaoClone) && !bateuParede) {
            AtualizaPosicao(pacman->posicaoAtual, posicaoClone);
            AtualizaTrilhaPacman(pacman);
            LevaFinalTunel(ObtemTunelMapa(mapa), posicaoClone);
        }
    }
    
    AtualizaPosicao(pacman->posicaoAtual, posicaoClone);
    AtualizaTrilhaPacman(pacman);
    DesalocaPosicao(posicaoClone);
}

void CriaTrilhaPacman(tPacman* pacman, int nLinhas, int nColunas) {
    if (pacman->trilha != NULL) return;

    // atribui os numeros de linhas e colunas
    pacman->nLinhasTrilha = nLinhas;
    pacman->nColunasTrilha = nColunas;

    //aloca espaco pra trilha
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
            else fprintf(fTrilha, "%d", pacman->trilha[i][j]);

            // nao printa o espaco na ultima coluna
            if (j != pacman->nColunasTrilha-1) fprintf(fTrilha, " "); 
        }
        fprintf(fTrilha, "\n");
    }
    fclose(fTrilha);
}

void InsereNovoMovimentoSignificativoPacman(tPacman* pacman, COMANDO comando, const char* acao) {
    (pacman->nMovimentosSignificativos)++;
    pacman->historicoDeMovimentosSignificativos = (tMovimento **) realloc (pacman->historicoDeMovimentosSignificativos, ObtemNumeroMovimentosSignificativosPacman(pacman) * sizeof(tMovimento *));
    pacman->historicoDeMovimentosSignificativos[ObtemNumeroMovimentosSignificativosPacman(pacman)-1] = CriaMovimento(ObtemNumeroAtualMovimentosPacman(pacman), comando, acao);
}

void MataPacman(tPacman* pacman) {
    pacman->estaVivo = MORTO;
}

void DesalocaPacman(tPacman* pacman) {
    if (pacman == NULL) return;

    // desaloca movimento
    if (pacman->historicoDeMovimentosSignificativos != NULL) {
        for (int i = 0; i < pacman->nMovimentosSignificativos; i++)
            DesalocaMovimento(pacman->historicoDeMovimentosSignificativos[i]);
        free(pacman->historicoDeMovimentosSignificativos);
    }

    // desaloca trilha
    if (pacman->trilha != NULL) {
        for (int i = 0; i < pacman->nLinhasTrilha; i++)
            free(pacman->trilha[i]);
        free(pacman->trilha);
    }

    // desaloca posicao
    DesalocaPosicao(pacman->posicaoAtual);

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
    return ObtemNumeroColisoesParedeBaixoPacman(pacman) + ObtemNumeroColisoesParedeCimaPacman(pacman)
         + ObtemNumeroColisoesParedeEsquerdaPacman(pacman) + ObtemNumeroColisoesParedeDireitaPacman(pacman);
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
    return ObtemPontuacaoAtualPacman(pacman) + ObtemNumeroColisoesParedePacman(pacman);
}

int ObtemPontuacaoAtualPacman(tPacman* pacman) {
    return ObtemNumeroFrutasComidasBaixoPacman(pacman) + ObtemNumeroFrutasComidasCimaPacman(pacman) 
         + ObtemNumeroFrutasComidasEsquerdaPacman(pacman) + ObtemNumeroFrutasComidasDireitaPacman(pacman);
}