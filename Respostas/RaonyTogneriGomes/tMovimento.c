#include "tMovimento.h"

tMovimento* CriaMovimento(int numeroDoMovimento, COMANDO comando, const char* acao) {
    tMovimento * movimento = (tMovimento *) malloc(sizeof(tMovimento));
    if (movimento == NULL) {
        printf("Alocacao impropria no tMovimento.c\n");
        exit(1);
    }

    movimento->numeroDoMovimento = numeroDoMovimento;
    movimento->comando = comando;
    strcpy(movimento->acao, acao);
    return movimento;
}

int ObtemNumeroMovimento(tMovimento* movimento) {
    return movimento->numeroDoMovimento;
}

COMANDO ObtemComandoMovimento(tMovimento* movimento) {
    return movimento->comando;
}

char* ObtemAcaoMovimento(tMovimento* movimento) {
    return movimento->acao;
}

void DesalocaMovimento(tMovimento* movimento) {
    if (movimento != NULL) free(movimento);
}