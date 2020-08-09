#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int mat[3][3];
    int pos;
    int encerrou;
}Tpacote,*Ppacote;

Ppacote novo_pacote();
void atualiza(Ppacote jogo, int jogador);
void show(Ppacote jogo);
int verifica_jogada(Ppacote jogo);
int verifica_jogo(Ppacote jogo);