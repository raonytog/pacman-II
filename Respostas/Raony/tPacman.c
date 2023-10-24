#include "tPacman.h"
#include "tAuxiliares.h"
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

/**
 * Cria o pacman dinamicamente. Caso dê erro na alocação da estrutura tPacman, 
 * retorna NULL. 
 * Caso a posição passada como parâmetro seja NULL, retorna NULL.
 * Caso não dê erros, retorna o ponteiro para o tPacman alocado.
 * \param posicao Ponteiro para tPosicao
 */
tPacman* CriaPacman(tPosicao* posicao) {
    tPacman * pacman = (tPacman*)malloc(sizeof(tPacman));
    if (pacman == NULL || posicao == NULL) return NULL;
    AtualizaPosicao(pacman->posicaoAtual, posicao);

    pacman->trilha = (int **)malloc (pacman->nLinhasTrilha * sizeof(int *));
    for (int i = 0; i < pacman->nLinhasTrilha; i++) {
        pacman->trilha[i] = (int *) malloc(pacman->nColunasTrilha * sizeof(int));
    }

    // PROVAVELENTE ERRADO
    pacman->nMovimentosSignificativos = (tMovimento **) realoc (sizeof(tMovimento *));
    return pacman;
}

/**
 * Clona o pacman dinamicamente, apenas com relação a posição.
 * Aloca outro pacman apenas copiando as informações de linha e coluna do original (passado como parâmetro).
 * \param pacman pacman
 */
tPacman* ClonaPacman(tPacman* pacman) {
    tPacman * clone = (tPacman*)malloc(sizeof(tPacman));
    if (clone == NULL) return NULL;
    AtualizaPosicao(clone->posicaoAtual, pacman->posicaoAtual);
    return clone;
}

/**
 * Clona a lista historico de movimentos significativos do pacman.
 * Aloca dinamicamente todas as estruturas do histórico de
 * movimentos do pacman original (passado como parâmetro): a lista e os movimentos da lista.
 * E por fim copia as informações do histórico original para o clone.
 * Retorna um ponteiro para o tMovimento** clone.
 * \param pacman pacman
 */
tMovimento** ClonaHistoricoDeMovimentosSignificativosPacman(tPacman* pacman);

tPosicao* ObtemPosicaoPacman(tPacman* pacman) {
    return pacman->posicaoAtual;
}

int EstaVivoPacman(tPacman* pacman) {
    return pacman->estaVivo;
}

/**
 * Função que irá mover o pacman no mapa, atualizando sua posição.
 * Dado o pacman, o mapa, e o comando do jogador, a posição do pacman
 * é atualizada. Consultas ao mapa deverão ser feitas para ver se
 * a posição pode ser realmente atualizada ou não, como por exemplo,
 * se o pacman encontrou uma parede ele não se move.
 * 
 * \param pacman pacman
 * \param mapa o mapa que contem o pacman
 * \param comando o comando para onde irá o pacman
 */
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

/**
 * Aloca a trilha dinamicamente.
 * Caso a trilha seja igual a NULL, a matriz int** deverá ser
 * alocada dinamicamente com os valores de linha e coluna.
 * 
 * \param pacman pacman
 * \param nLinhas número de linhas da trilha
 * \param nColunas número de colunas da trilha
 */
void CriaTrilhaPacman(tPacman* pacman, int nLinhas, int nColunas) {
    if (pacman->trilha != NULL) return;

    pacman->trilha = (int **) malloc ( nLinhas * sizeof(int *));
    for (int i = 0; i < nLinhas; i++) {
        pacman->trilha[i] = (int *) malloc (nColunas * sizeof(int));
    }
}

/**
 * Atualiza na trilha a posição por onde passou o pacman.
 * Dado o pacman, com suas informações de posição e trilha na estrutura,
 * atualiza o item da trilha, referente a posição atual do pacman,
 * para o valor int correspondente ao número do movimento atual do pacman.
 * \param pacman pacman
 */
void AtualizaTrilhaPacman(tPacman* pacman);

/**
 * Salva a trilha em um arquivo na raíz junto com o binário.
 * 
 * \param pacman pacman
 */
void SalvaTrilhaPacman(tPacman* pacman);

/**
 * Insere na lista de movimentos um novo movimento significativo.
 * Dado o pacman, o comando do jogador, e a ação significativa,
 * cria um movimento significativo tMovimento com essas informações e
 * insere na lista de movimentos significativos do pacman.
 * 
 * \param pacman pacman
 * \param comando o comando do movimento
 * \param acao a ação do movimento
 */
void InsereNovoMovimentoSignificativoPacman(tPacman* pacman, COMANDO comando, const char* acao);

void MataPacman(tPacman* pacman) {
    pacman->estaVivo = 0;
}

void DesalocaPacman(tPacman* pacman) {
    if (pacman == NULL) return;

    DesalocaPosicao(pacman->posicaoAtual);

    for (int i = 0; i < pacman->nMovimentosSignificativos; i++) {
        free(pacman->historicoDeMovimentosSignificativos[i]);
    }
    free(pacman->historicoDeMovimentosSignificativos);

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