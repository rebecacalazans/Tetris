#include "matriz_jogo.h"
void iniciar(int m[20][10])
{
  for(int i = 0; i < 20; i++)
    for(int j = 0; j < 10; j++)
      m[i][j] = 0;
}
void imprimir(int m[20][10])
{
  for(int i = 0; i < 12; i++)
    std::cout << '*';
  std::cout << '\n';
  for(int i = 0; i < 20; i++)
  {
    std::cout << '|';
    for(int j = 0; j < 10; j++)
    {
      if(m[i][j] == 0)
        std::cout << ' ';
      else
        std::cout << 'o';
    }
    std::cout << "|\n";
  }
  for(int i = 0; i < 12; i++)
    std::cout << '*';
  std::cout << '\n';
}
