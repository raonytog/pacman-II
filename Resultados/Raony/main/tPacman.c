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

#define BAIXO 
#define CIMA 
#define ESQUERDA 
#define DIREITA 

tPacman* CriaPacman(tPosicao* posicao) {
    tPacman * pacman = (tPacman*)malloc(sizeof(tPacman));
    if (pacman == NULL || posicao == NULL) return NULL;
    AtualizaPosicao(pacman->posicaoAtual, posicao);

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

    pacman->nMovimentosSignificativos = (tMovimento **) realoc (sizeof(tMovimento *));
    return pacman;
}

tPacman* ClonaPacman(tPacman* pacman) {
    tPacman * clone = CriaPacman(pacman->posicaoAtual);
    AtualizaPosicao(clone->posicaoAtual, pacman->posicaoAtual);
    return clone;
}

tMovimento** ClonaHistoricoDeMovimentosSignificativosPacman(tPacman* pacman) {
    tMovimento ** clone = *(pacman->historicoDeMovimentosSignificativos); 
    return *clone;
}

tPosicao* ObtemPosicaoPacman(tPacman* pacman) {
    return pacman->posicaoAtual;
}

int EstaVivoPacman(tPacman* pacman) {
    return pacman->estaVivo;
}


void MovePacman(tPacman* pacman, tMapa* mapa, COMANDO comando) {
    switch (comando) {
        case 0:
            tPosicao * pClone = ClonaPosicao(pacman->posicaoAtual);
            pClone->coluna--;
            if (!EstaForaDosLimites(mapa, pClone) && EncontrouParedeMapa(mapa, pClone)) {
                AtualizaPosicao(pacman->posicaoAtual, pClone);
            }
            DesalocaPosicao(pClone);
            break;
        
        case 1:
            tPosicao * pClone = ClonaPosicao(pacman->posicaoAtual);
            pClone->linha--;
            if (!EstaForaDosLimites(mapa, pClone) && EncontrouParedeMapa(mapa, pClone)) {
                AtualizaPosicao(pacman->posicaoAtual, pClone);
            }
            DesalocaPosicao(pClone);
            break;

        case 2:
            tPosicao * pClone = ClonaPosicao(pacman->posicaoAtual);
            pClone->linha++;
            if (!EstaForaDosLimites(mapa, pClone) && EncontrouParedeMapa(mapa, pClone)) {
                AtualizaPosicao(pacman->posicaoAtual, pClone);
            }
            DesalocaPosicao(pClone);
            break;

        case 3:
            tPosicao * pClone = ClonaPosicao(pacman->posicaoAtual);
            pClone->coluna++;
            if (!EstaForaDosLimites(mapa, pClone) && EncontrouParedeMapa(mapa, pClone)) {
                AtualizaPosicao(pacman->posicaoAtual, pClone);
            }
            DesalocaPosicao(pClone);
            break;
    }

    AtualizaTrilhaPacman(pacman);
}

void CriaTrilhaPacman(tPacman* pacman, int nLinhas, int nColunas) {
    if (pacman->trilha != NULL) return;

    pacman->trilha = (int **) malloc ( nLinhas * sizeof(int *));
    for (int i = 0; i < nLinhas; i++) {
        pacman->trilha[i] = (int *) malloc (nColunas * sizeof(int));
    }
}

void AtualizaTrilhaPacman(tPacman* pacman) {

}

void SalvaTrilhaPacman(tPacman* pacman);

void InsereNovoMovimentoSignificativoPacman(tPacman* pacman, COMANDO comando, const char* acao) {
    tMovimento * novoMov = CriaMovimento(ObtemNumeroAtualMovimentosPacman(pacman), comando, acao);
    pacman->nMovimentosSignificativos++;
    pacman->historicoDeMovimentosSignificativos = (tMovimento **) realloc (pacman->historicoDeMovimentosSignificativos, pacman->nMovimentosSignificativos * sizeof(tMovimento *));
    pacman->historicoDeMovimentosSignificativos[ObtemNumeroMovimentosSignificativosPacman(pacman) - 1] = novoMov;
}

void MataPacman(tPacman* pacman) {
    pacman->estaVivo = 0;
}

void DesalocaPacman(tPacman* pacman) {
    if (pacman == NULL) return;

    // desaloca posi
    DesalocaPosicao(pacman->posicaoAtual);

    // desaloca movimento
    for (int i = 0; i < pacman->nMovimentosSignificativos; i++) {
        DesalocaMovimento(pacman->historicoDeMovimentosSignificativos);
    }
    free(pacman->historicoDeMovimentosSignificativos);

    // desaloca trilha
    for (int i = 0; i < pacman->nLinhasTrilha; i++) {
        free(pacman->trilha[i]);
    }
    free(pacman->trilha);
}

int ObtemNumeroAtualMovimentosPacman(tPacman* pacman) {
    return ObtemNumeroMovimentosBaixoPacman(pacman) + ObtemNumeroMovimentosCimaPacman(pacman) + 
           ObtemNumeroMovimentosEsquerdaPacman(pacman) + ObtemNumeroColisoesParedeDireitaPacman(pacman);
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
    return pacman->nMovimentosSignificativos;
}

int ObtemPontuacaoAtualPacman(tPacman* pacman) {
    return ObtemNumeroFrutasComidasBaixoPacman(pacman) + ObtemNumeroFrutasComidasCimaPacman(pacman) +
           ObtemNumeroFrutasComidasEsquerdaPacman(pacman) + ObtemNumeroFrutasComidasDireitaPacman(pacman);
}