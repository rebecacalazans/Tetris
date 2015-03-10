#ifndef SRC_SPECA_H
#define SRC_SPECA_H

#include "peca.h"

class Speca: public Peca
{
  public:
    Speca(int m[20][10]);
    Speca(int m[7][7]);
    ~Speca(){};
    void formar();
};

#endif //SRC_SPECA_H
