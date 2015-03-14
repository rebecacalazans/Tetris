#include <iostream>
#include "jogo_funcoes.h"

Peca* nova_peca(int i, int m[20][10])
{
  Peca* aux;
  switch(i)
  {
    case 1:
      aux=new Opeca(m) ;
      break;
    case 2:
      aux=new Jpeca(m);
      break;
    case 3:
      aux=new Ipeca(m);
      break;
    case 4:
      aux=new Lpeca(m);
      break;
    case 5:
      aux=new Zpeca(m);
      break;
    case 6:
      aux=new Speca(m);
      break;
    case 7:
      aux=new Tpeca(m);
      break;
  }
  return aux;
}
Peca* nova_peca(int i, int m[7][7])
{
  Peca* aux;
  switch(i)
  {
    case 1:
      aux=new Opeca(m) ;
      break;
    case 2:
      aux=new Jpeca(m);
      break;
    case 3:
      aux=new Ipeca(m);
      break;
    case 4:
      aux=new Lpeca(m);
      break;
    case 5:
      aux=new Zpeca(m);
      break;
    case 6:
      aux=new Speca(m);
      break;
    case 7:
      aux=new Tpeca(m);
      break;
  }
  return aux;
}
void  hold(int matriz_jogo[20][10], int matriz_hold[7][7], int matriz_next[7][7],
    Peca* &peca_atual ,Peca* &peca_hold, Peca* &peca_next)
{
  peca_atual -> apagar(matriz_jogo);
  peca_hold -> apagar(matriz_hold);
  peca_next -> apagar(matriz_next);
  if(peca_hold)
  {
    Peca* aux;
    aux = peca_hold;
    peca_hold = peca_atual;
    peca_atual = aux;
  }
  else
  {
    peca_hold = peca_atual;
    peca_atual = peca_next;
    peca_next = nova_peca(3, matriz_jogo);
  }

  peca_atual -> redefinir(matriz_jogo);
  peca_hold -> criar_imagem(matriz_hold);
  peca_next -> criar_imagem(matriz_next);
}
void excliur_linha(int n, int m[20][10])
{
  int i, j;
  for(j=4; j>=0; j--)//
  {
    m[n][j]=0;
    m[n][9-j]=0;
  }
  for(j=0; j<10; j++)//
  {
    for(i=n; i>0; i--)//Faz cada quadro ser o de cima
    {
      m[i][j]=m[i-1][j];
    }
    m[i][j]=0;//Torna o quadro superior vazio
  }
}
int pontuar(int m[20][10])
{

  int cont=0;// conta as linhas tiradas na jogada
  int v=0;//conta os bloquinhos preenchidos em cada linha;
  for(int i=19; i>0; i--)
  {
    v=0;
    for(int j=0; j<10; j++)
    {
      if(m[i][j])
        v++;
      if(v==10)
      {
        excliur_linha(i, m);
        j=-1;
        v=0;
        cont++;
      }
    }
  }
  if(cont)
    switch(cont)//Pontua o jogo de acordo com o combo
    {
      case 1:
        return 1;
        break;
      case 2:
        return 3;
        break;
      case 3:
        return 5;
        break;
      case 4:
        return 8;
        break;
    }
        return 0;
}
