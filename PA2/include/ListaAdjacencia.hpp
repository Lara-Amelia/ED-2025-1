#ifndef LISTAADJACENCIA_HPP
#define LISTAADJACENCIA_HPP

#include "include/ListaEncadeada.hpp"

class NodeAdj
{
    private:
    int nroVertex;
    ListaEncadeada listaEdges;
    NodeAdj* prox;

    public:


    friend class ListaAdjacencia;
};

class ListaAdjacencia
{
    private:
    ListaEncadeada adjacentes; 

    int qtVertices;

    public:
    ListaAdjacencia(int qtVertices);
    void InsereVert(int nroVert);
    void InsereEdge(int v, int w);

};

#endif