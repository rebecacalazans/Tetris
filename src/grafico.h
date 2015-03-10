#ifndef SRC_GRAFICO_H
#define SRC_GRAFICO_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

void iniciar(int m[20][10]);
void iniciar(int m[7][7]);
void imprimir_matriz_jogo(ALLEGRO_COLOR cor[10], ALLEGRO_BITMAP* img,float x, float y, int matriz[20][10]);
void imprimir_matriz_peca(ALLEGRO_COLOR cor[10], ALLEGRO_BITMAP* img,float x, float y, int matriz[7][7]);
void iniciar_cores(ALLEGRO_COLOR cor[10]);

#endif //SRC_GRAFICO_H
