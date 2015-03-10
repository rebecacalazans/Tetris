#include <iostream>
#include <chrono>
#include <random>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "pecas/pecas.h"
#include "grafico.h"
#include "jogo_funcoes.h"

const int largura_tela = 30*22;
const int altura_tela = 30*24;

ALLEGRO_BITMAP *img = NULL;
ALLEGRO_BITMAP *objeto[8];
ALLEGRO_DISPLAY *janela = NULL;
ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
ALLEGRO_COLOR cor[10];

bool iniciar();
bool carregarArquivos();
void finalizar();
void imprimir(int jogo[20][10], int hold[7][7], int next[7][7]);

int main(void)
{
  if (!iniciar())
    return -1;
  if (!carregarArquivos())
    return -1;
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::minstd_rand0 generator (seed);//Usar generator()

  int matriz_jogo[20][10],
      matriz_hold[7][7],
      matriz_next[7][7];

  iniciar(matriz_jogo);
  iniciar(matriz_hold);
  iniciar(matriz_next);

  iniciar_cores(cor);

  Peca* peca_atual,* peca_next,* peca_hold;
  peca_atual = nova_peca((generator() % 7 + 1), matriz_jogo);
  peca_next = nova_peca((generator() % 7 + 1), matriz_next);
  peca_hold = nova_peca((generator() % 7 + 1), matriz_hold);


  imprimir(matriz_jogo, matriz_hold, matriz_next);
  al_rest(5);
  finalizar();
}

bool iniciar()
{
  if (!al_init())
  {
    std::cout<< "Falha ao iniciar allegro.\n";
    finalizar();
    return false;
  }

  if (!al_init_image_addon())
  {
    std::cout << "Falha ao iniciar allegro_image.\n";
    finalizar();
    return false;
  }
  if (!al_install_keyboard())
  {
    std::cout << "Falha ao inicializar teclado.\n";
    finalizar();
    return false;
  }

  janela = al_create_display(largura_tela, altura_tela);
  if (!janela)
  {
    std::cout << "Falha ao criar janela.\n";
    finalizar();
    return false;
  }

  al_set_window_title(janela, "Tetris");

  fila_eventos = al_create_event_queue();
  if (!fila_eventos)
  {
    std::cout << "Falha ao criar fila de eventos.\n";
    finalizar();
    return false;
  }

  if (!al_install_mouse())
  {
    std::cout << "Falha ao iniciar mouse.\n";
    finalizar();
    return false;
  }
  if (!al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT))
  {
    std::cout << "Falha ao atribuir ponteiro do mouse.\n";
    finalizar();
    return false;
  }

  al_register_event_source(fila_eventos, al_get_keyboard_event_source());
  al_register_event_source(fila_eventos, al_get_display_event_source(janela));
  al_register_event_source(fila_eventos, al_get_mouse_event_source());
  return true;
}
bool carregarArquivos()
{
  img = al_load_bitmap("img.png");
  if (!img)
  {
    std::cout << "Falha ao carregar imagem.\n";
    finalizar();
    return false;
  }
  return true;
}
void finalizar()
{
  if(img)
    al_destroy_bitmap(img);
  if(fila_eventos)
    al_destroy_event_queue(fila_eventos);
  if(janela)
    al_destroy_display(janela);
}
void imprimir(int jogo[20][10], int hold[7][7], int next[7][7])
{
  for(int i = 0; i < altura_tela/30; i++)
    for(int j = 0; j < largura_tela/30; j++)
      al_draw_tinted_bitmap(img, cor[9], j * 30.0, i * 30.0, 0);
  imprimir_matriz_jogo(cor, img, 30.0 * 6, 30.0 * 3, jogo);
  imprimir_matriz_peca(cor, img, 30.0 + 7, 30.0 * 5 + 7, hold);
  imprimir_matriz_peca(cor, img, 30.0 * 17 + 7, 30.0 * 5 + 7, next);
  al_flip_display();
}
