#ifndef SRC_TPECA_H
#define SRC_TPECA_H

#include "peca.h"

class Tpeca: public Peca
{
  public:
    Tpeca(int m[20][10]);
    ~Tpeca(){};
    void formar();
};

#endif //SRC_TPECA_H
