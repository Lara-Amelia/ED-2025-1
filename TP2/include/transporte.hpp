#ifndef TRANSPORTE_HPP
#define TRANSPORTE_HPP

#include "Listas.hpp"

class Transporte{
    public:
        Transporte(int capacidade, int latencia, int intervalo, int numVert);
        ~Transporte();

        void InsereVertice();
        void InsereAresta(int v, int w);
        
        void buscaLargura(int origem, int destino, ListaEncadeada& rota);
        void insereCaminhoRec(ListaEncadeada& lista, int* pai, int atual, int origem);
        
        int QuantidadeVertices();
        int QuantidadeArestas();

        int getCapacTransp();
        int getLatTransp();
        int getIntervTransp();
        int getNumVertices();
        
    private:
        //parâmetros de transporte do sistema
        int capacidadeTransporte;
        int latenciaTransporte;
        int intervaloTransporte;
        int numVertices; //número de vértices/armazéns no grafo

        ListaAdjacencia armazens;

    friend class Armazem;
};

#endif