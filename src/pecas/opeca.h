#ifndef SRC_OPECA_H
#define SRC_OPECA_H

#include "peca.h"

class Opeca: public Peca
{
  public:
    Opeca(int m[20][10]);
    Opeca(int m[7][7]);
    ~Opeca(){};
    void formar();
};

#endif //SRC_OPECA_H
