#ifndef TRANSPORTE_HPP
#define TRANSPORTE_HPP

#include "Listas.hpp"

class Transporte{
    public:
        Transporte(int capacidade, int latencia, int intervalo, int numVert);
        ~Transporte();

        void InsereVertice();
        void InsereAresta(int v, int w);
        //determina a rota entre 2 vértices para um certo pacote
        //utilizaremos uma fila para obter a rota com a busca em largura e, posteriormente, inseriremos
        //o resultado em uma Lista Encadeada
        ListaEncadeada buscaLargura(int origem, int destino);

        //provavelmente não necessitaremos destes métodos
        int QuantidadeVertices();
        int QuantidadeArestas();

        int GrauMinimo();
        int GrauMaximo();

        void ImprimeVizinhos(int v);

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
        //ListaEncadeada* rotas;

    friend class Armazem;
};

#endif