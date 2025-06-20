#ifndef FILA_HPP
#define FILA_HPP


class TipoCelula
{
    private:
    int item;
    TipoCelula* prox;

    public:
    TipoCelula();

    friend class Fila;
};

class Fila
{
    private:
    int tamanho;
    TipoCelula* frente;
    TipoCelula* tras;

    public:
    Fila();
    ~Fila();
    void Enfileira(int item);
    int Desenfileira();
    void Limpa();

    int getTamanho();
    bool Vazia();

    friend class Transporte;
};

#endif