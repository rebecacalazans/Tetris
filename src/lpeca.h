#ifndef SRC_LPECA_H
#define SRC_LPECA_H

#include "peca.h"

class Lpeca: public Peca
{
  public:
    Lpeca(int m[20][10]);
    ~Lpeca(){};
    void formar();
};

#endif //SRC_LPECA_H
