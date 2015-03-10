# include "peca.h"
#include <iostream>

Peca::
Peca(){}

void Peca::
imprimir()
{
  for(int i = 0; i < 4; i++)
  {
    std::cout << "( " << x_[i] << " ), ( " << y_[i] << " )\n";
  }
  std::cout << "\n";
}

//Função que apaga, na matriz, a peça
void Peca::
apagar(int m[20][10])
{
  for(int i = 0; i < 4; i++)
    if(y_[i] >= 0)
      m[y_[i]][x_[i]] = 0;
}
void Peca::
apagar(int m[7][7])
{
  for(int i = 0; i < 4; i++)
    if(y_[i] >= 0)
      m[y_[i]][x_[i]] = 0;
}

//Função que cria, na matriz, a peça
void Peca::
colorir(int m[20][10])
{
  for(int i = 0; i < 4; i++)
    if(y_[i] >= 0)
      m[y_[i]][x_[i]] = cor_;
}
void Peca::
colorir(int m[7][7])
{
  for(int i = 0; i < 4; i++)
    if(y_[i] >= 0)
      m[y_[i]][x_[i]] = cor_;
}

//Função que verifica se a posição da peça é possível
bool Peca::
verificar_posicao(int m[20][10])
{
  for(int i = 0; i < 4; i++)
  {
    if(x_[i] < 0 || x_[i] > 9|| y_[i] > 19)
      return false;
    else if((m[y_[i]][x_[i]] > 0 &&
        m[y_[i]][x_[i]] < 8))
      return false;
  }
  return true;
}

bool Peca::
mover_para_baixo(int m[20][10])
{
  apagar(m);
  for(int i = 0; i < 4; i++)
    y_[i]++;
  if(verificar_posicao(m))
  {
    colorir(m);
    return true;
  }
  else
  {
    for(int i = 0; i < 4; i++)
      y_[i]--;
    colorir(m);
    return false;
  }
}

bool Peca::
mover_para_direita(int m[20][10])
{
  apagar(m);
  for(int i = 0; i < 4; i++)
    x_[i]++;
  if(verificar_posicao(m))
  {
    colorir(m);
    return true;
  }
  else
  {
    for(int i = 0; i < 4; i++)
      x_[i]--;
    colorir(m);
    return false;
  }
}

bool Peca::
mover_para_esquerda(int m[20][10])
{
  apagar(m);
  for(int i = 0; i < 4; i++)
    x_[i]--;
  if(verificar_posicao(m))
  {
    colorir(m);
    return true;
  }
  else
  {
    for(int i = 0; i < 4; i++)
      x_[i]++;
    colorir(m);
    return false;
  }
}

bool Peca::
girar(int m[20][10])
{
  bool aux;
  apagar(m);
  if(++posicao_ >= n_posicoes_) posicao_ = 0;

  if(verificar_posicao(m))
  {
    aux = true;
    goto formacao;
  }
  if(mover_para_esquerda(m))
  {
    aux = true;
    goto formacao;
  }
  if(mover_para_direita(m))
  {
    aux = true;
    goto formacao;
  }
  if(mover_para_baixo(m))
  {
    aux = true;
    goto formacao;
  }
  if(--posicao_ < 0) posicao_ = n_posicoes_ - 1;
  aux = false;
formacao:
  formar();
  colorir(m);
  return aux;
}
