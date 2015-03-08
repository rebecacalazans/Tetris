#ifndef ZRC_IPECA_H
#define ZRC_IPECA_H

#include "peca.h"

class Ipeca: public Peca
{
  public:
    Ipeca(int m[20][10]);
    ~Ipeca(){};
    void formar();
};

#endif //SRC_IPECA_H
