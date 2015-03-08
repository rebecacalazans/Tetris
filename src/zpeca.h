#ifndef SRC_ZPECA_H
#define SRC_ZPECA_H

#include "peca.h"

class Zpeca: public Peca
{
  public:
    Zpeca(int m[20][10]);
    ~Zpeca(){};
    void formar();
};

#endif //SRC_ZPECA_H
