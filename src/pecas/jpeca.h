#ifndef SRC_JPECA_H
#define SRC_JPECA_H

#include "peca.h"

class Jpeca: public Peca
{
  public:
    Jpeca(int m[20][10]);
    Jpeca(int m[7][7]);
    ~Jpeca(){};
    void formar();
};

#endif //SRC_JPECA_H
