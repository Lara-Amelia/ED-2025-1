#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "ListaAdjacencia.hpp"
#include "ListaEncadeada.hpp"

class Grafo{
    public:
        Grafo();
        ~Grafo();

        void InsereVertice();
        void InsereAresta(int v, int w);

        int QuantidadeVertices();
        int QuantidadeArestas();

        int GrauMinimo();
        int GrauMaximo();

        void ImprimeVizinhos(int v);
        
    private:
        ListaAdjacencia vertices;
};

#endif