#ifndef LISTAENCADEADA_HPP
#define LISTAENCADEADA_HPP

class Node
{
    private:
    int nroVertice;
    Node *prox;

    public:
    //construtor para nodes
    Node();
    Node (int valor);

    friend class ListaEncadeada;
};

class ListaEncadeada
{
    private:
    int tamanho;
    Node *head;
    Node *tail;
    Node *PosicionaAntes(int pos);
    Node *PosicionaEm(int pos);

    public:
    ListaEncadeada();
    ~ListaEncadeada();
    void setVert(int pos, int novoNode);
    int getVert(int pos);
    //void insereInicio(int item);
    //void insereFinal(int item);
    void inserePosicao(int item, int pos);
    int pesquisa(int pesquisado);
    void Imprime();
    void Limpa();

    friend class ListaAdjacencia;
};

#endif