#ifndef SRC_JOGO_FUNCOES_H
#define SRC_JOGO_FUNCOES_H

#include "pecas/pecas.h"

Peca* nova_peca(int i, int m[20][10]);
Peca* nova_peca(int i, int m[7][7]);
void  hold(int matriz_jogo[20][10], int matriz_hold[7][7], int matriz_next[7][7],
    Peca* peca_atual ,Peca* peca_hold, Peca* peca_next);
void excliur_linha(int n, int m[20][10]);
int pontuar(int m[20][10]);

#endif //SRC_JOGO_FUNCOES_H
