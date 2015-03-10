#ifndef SRC_IPECA_H
#define SRC_IPECA_H

#include "peca.h"

class Ipeca: public Peca
{
  public:
    Ipeca(int m[20][10]);
    Ipeca(int m[7][7]);
    ~Ipeca(){};
    void formar();
};

#endif //SRC_IPECA_H
