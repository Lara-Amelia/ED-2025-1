#ifndef LISTAADJACENCIA_HPP
#define LISTAADJACENCIA_HPP

#include "include/ListaEncadeada.hpp"
#include "include/graph.hpp"

class NodeAdj
{
    private:
    int vertice;
    ListaEncadeada listaArestas;
    NodeAdj* prox;

    public:
    NodeAdj();
    NodeAdj(int nroVer);
    void setVer(int nroVer);
    int getVer(int pos);
    friend class ListaAdjacencia;
};

class ListaAdjacencia
{
    private:
    int tamanho;
    NodeAdj *head;
    NodeAdj *tail;
    NodeAdj *PosicionaAntesAdj(int pos);
    NodeAdj *PosicionaEmAdj(int pos);

    public:
    ListaAdjacencia();
    ~ListaAdjacencia();
    void InsereVert(int nroVert, int pos);
    void InsereAresta(int v, int e);
    int pesquisaVert(int pesquisado);
    //int pesquisaAresta(int pesquisado); veremos se é útil
    void ImprimeAdj();
    void LimpaAdj();
    
    friend class Grafo;
};

#endif