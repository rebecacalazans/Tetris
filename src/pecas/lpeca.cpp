#include "lpeca.h"

Lpeca::
Lpeca(int m[20][10])
      {
        cor_ = 4;
        x_[0] = 4;
        y_[0] = -2;
        n_posicoes_ = 4;
        posicao_ = 0;
        formar();
        colorir(m);
      }

void Lpeca::
formar()
{
  switch(posicao_)
  {
    case 0:
      x_[1] = x_[0];
      y_[1] = y_[0] + 1;
      x_[2] = x_[0];
      y_[2] = y_[0] - 1;
      x_[3] = x_[0] + 1;
      y_[3] = y_[0] + 1;
      break;
    case 1:
      x_[1] = x_[0] - 1;
      y_[1] = y_[0] + 1;
      x_[2] = x_[0] - 1;
      y_[2] = y_[0];
      x_[3] = x_[0] + 1;
      y_[3] = y_[0];
      break;
    case 2:
      x_[1] = x_[0];
      y_[1] = y_[0] + 1;
      x_[2] = x_[0];
      y_[2] = y_[0] - 1;
      x_[3] = x_[0] - 1;
      y_[3] = y_[0] - 1;
      break;
    case 3:
      x_[1] = x_[0] + 1;
      y_[1] = y_[0] + 1;
      x_[2] = x_[0] - 1;
      y_[2] = y_[0];
      x_[3] = x_[0] + 1;
      y_[3] = y_[0];
      break;
  }
}
