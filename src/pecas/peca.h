#ifndef PECAS
#define PECAS

class Peca
{
  public:
    Peca();
    virtual ~Peca() {}
    virtual void formar() = 0;
    void imprimir();
    void apagar(int m[20][10]);
    void colorir(int m[20][10]);
    bool verificar_posicao(int m[20][10]);

    //Funções de movimento das peças
    bool mover_para_baixo(int m[20][10]);
    bool mover_para_direita(int m[20][10]);
    bool mover_para_esquerda(int m[20][10]);
    bool girar(int m[20][10]);
  protected:
    int x_[4], y_[4],
        cor_, posicao_,
        n_posicoes_;
};

#endif //PECAS
