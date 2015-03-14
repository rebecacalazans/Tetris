#include "grafico.h"

void iniciar(int m[20][10])
{
  for(int i = 0; i < 20; i++)
    for(int j = 0; j < 10; j++)
      m[i][j] = 0;
}
void iniciar(int m[7][7])
{
  for(int i = 0; i < 7; i++)
    for(int j = 0; j < 7; j++)
      m[i][j] = 0;
}

void imprimir_matriz_jogo(ALLEGRO_COLOR cor[10], ALLEGRO_BITMAP* img, float x, float y, int matriz[20][10])
{
  for(int i = 0; i < 20; i++)
    for(int j = 0; j < 10; j++)
    {
      al_draw_tinted_bitmap(img, cor[matriz[i][j]], x + j * 30,y + i * 30, 0);
    }
}

void imprimir_matriz_peca(ALLEGRO_COLOR cor[10],ALLEGRO_BITMAP* img, float x, float y, int matriz[7][7])
{
  for(int i = 0; i < 7; i++)
    for(int j = 0; j < 7; j++)
    {if(matriz[i][j] == 0)
      al_draw_tinted_scaled_bitmap (img, cor[9], 0,  0, 30, 30, x + j * 15,y + i * 15, 15, 15, 6);
      else
      al_draw_tinted_scaled_bitmap (img, cor[matriz[i][j]], 0,  0, 30, 30, x + j * 15,y + i * 15, 15, 15, 6);
    }
}

void iniciar_cores(ALLEGRO_COLOR cor[10])
{
  cor[0] = al_map_rgb(255, 255, 255);
  cor[1] = al_map_rgb(255, 215, 0);
  cor[2] = al_map_rgb(0, 100, 0);
  cor[3] = al_map_rgb(0, 191, 255);
  cor[4] = al_map_rgb(255, 0, 0);
  cor[5] = al_map_rgb(255, 140, 0);
  cor[6] = al_map_rgb(218, 112, 214);
  cor[7] = al_map_rgb(0, 0, 128);
  cor[8] = al_map_rgb(105, 105, 105);
  cor[9] = al_map_rgb(169, 169, 169);
}
