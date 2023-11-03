#include "tArquivos.h"

char RetornaTeclaComando (COMANDO comando) {
    switch (comando) {
        case MOV_BAIXO:
            return 's';
        
        case MOV_CIMA:
            return 'w';

        case MOV_ESQUERDA:
            return 'a';

        case MOV_DIREITA:
            return 'd';
    }
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

void GeraArquivos(tPacman * pacman) {
    // incializacao eh gerada antes do jogo
    GeraResumoPacman(pacman);
    SalvaTrilhaPacman(pacman);
    GeraEstatisticaPacman(pacman);
    GeraRankingPacman(pacman);
}

void GeraResumoPacman (tPacman * pacman) {
    FILE * fResumo = NULL;
    fResumo = fopen("resumo.txt", "w");
    if (!fResumo) {
        printf("diretorio da saida do resumo invalido\n");
        exit(1);
    }

    tMovimento ** historico = ClonaHistoricoDeMovimentosSignificativosPacman(pacman);
    for (int i = 0; i < ObtemNumeroMovimentosSignificativosPacman(pacman); i++) {
        fprintf(fResumo, "Movimento %d (%c) %s\n", 
                ObtemNumeroMovimento(historico[i]), 
                RetornaTeclaComando(ObtemComandoMovimento(historico[i])), 
                ObtemAcaoMovimento(historico[i]));
    }

    for (int i = 0; i < ObtemNumeroMovimentosSignificativosPacman(pacman); i++)
        DesalocaMovimento(historico[i]);
    free(historico);

    fclose(fResumo);
}

void GeraEstatisticaPacman (tPacman * pacman) {
    FILE * fEstatistica = NULL;
    fEstatistica = fopen("estatisticas.txt", "w");

    fprintf(fEstatistica, "Numero de movimentos: %d\n", ObtemNumeroAtualMovimentosPacman(pacman));
    fprintf(fEstatistica, "Numero de movimentos sem pontuar: %d\n", ObtemNumeroMovimentosSemPontuarPacman(pacman));
    fprintf(fEstatistica, "Numero de colisoes com parede: %d\n", ObtemNumeroColisoesParedePacman(pacman));
    fprintf(fEstatistica, "Numero de movimentos para baixo: %d\n", ObtemNumeroMovimentosBaixoPacman(pacman));
    fprintf(fEstatistica, "Numero de movimentos para cima: %d\n", ObtemNumeroMovimentosCimaPacman(pacman));
    fprintf(fEstatistica, "Numero de movimentos para esquerda: %d\n", ObtemNumeroMovimentosEsquerdaPacman(pacman));
    fprintf(fEstatistica, "Numero de movimentos para direita: %d\n", ObtemNumeroMovimentosDireitaPacman(pacman));

    fclose(fEstatistica);
}

void GeraRankingPacman (tPacman * pacman) {
    FILE * fRanking = NULL;
    fRanking = fopen("ranking.txt", "w");

    tAcao acao[4];

    acao[0].movimento = ESQUERDA;
    acao[0].qtdColisoes = ObtemNumeroColisoesParedeEsquerdaPacman(pacman);
    acao[0].qtdFrutasComidas = ObtemNumeroFrutasComidasEsquerdaPacman(pacman);
    acao[0].qtdUsado = ObtemNumeroMovimentosEsquerdaPacman(pacman);

    acao[1].movimento = DIREITA;
    acao[1].qtdColisoes = ObtemNumeroColisoesParedeDireitaPacman(pacman);
    acao[1].qtdFrutasComidas = ObtemNumeroFrutasComidasDireitaPacman(pacman);
    acao[1].qtdUsado = ObtemNumeroMovimentosDireitaPacman(pacman);

    acao[2].movimento = BAIXO;
    acao[2].qtdColisoes = ObtemNumeroColisoesParedeBaixoPacman(pacman);
    acao[2].qtdFrutasComidas = ObtemNumeroFrutasComidasBaixoPacman(pacman);
    acao[2].qtdUsado = ObtemNumeroMovimentosBaixoPacman(pacman);

    acao[3].movimento = CIMA;
    acao[3].qtdColisoes = ObtemNumeroColisoesParedeCimaPacman(pacman);
    acao[3].qtdFrutasComidas = ObtemNumeroFrutasComidasCimaPacman(pacman);
    acao[3].qtdUsado = ObtemNumeroMovimentosCimaPacman(pacman);

    tAcao aux;
    for (int i = 0; i < QTD_MOV_DIFERENTE; i++) {
        for (int j = i+1; j < QTD_MOV_DIFERENTE; j++) {
            if (OrdenaRanking(acao[i], acao[j])) {
                aux = acao[j];
                acao[j] = acao[i];
                acao[i] = aux;
            }
        }
    }

    for (int i = QTD_MOV_DIFERENTE - 1; i >= 0 ; i --) {
        fprintf(fRanking, "%c,%d,%d,%d\n", acao[i].movimento, acao[i].qtdFrutasComidas, 
                                           acao[i].qtdColisoes, acao[i].qtdUsado);
    }

    fclose(fRanking);
}

int CriterioAlfabetico (tAcao acao1, tAcao acao2) {
    return acao1.movimento < acao2.movimento;
}

int CriterioUso(tAcao acao1, tAcao acao2) {
    if (acao1.qtdUsado > acao2.qtdUsado) return 1;
    else if (acao1.qtdUsado == acao2.qtdUsado) return CriterioAlfabetico(acao1, acao2);
    return 0;
}

int CriterioColisao (tAcao acao1, tAcao acao2) {
    if (acao1.qtdColisoes < acao2.qtdColisoes) return 1;
    else if (acao1.qtdColisoes == acao2.qtdColisoes) return CriterioUso(acao1, acao2);
    return 0;
}

int OrdenaRanking (tAcao acao1, tAcao acao2) {
    if (acao1.qtdFrutasComidas > acao2.qtdFrutasComidas) return 1;
    else if (acao1.qtdFrutasComidas == acao2.qtdFrutasComidas) return CriterioColisao(acao1, acao2);
    return 0;
}

