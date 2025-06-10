#ifndef FILA_HPP
#define FILA_HPP

//link reddit busca em largura:
//https://www.reddit.com/r/scala/comments/6pmnig/functional_and_recursive_breadth_first_search_in/?tl=pt-br

class TipoCelula
{
    private:
    int item;
    TipoCelula* prox;

    public:
    TipoCelula();

    friend class Fila;
};

//a fila será utilizada somente para definir as rotas dos pacotes via busca em largura
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