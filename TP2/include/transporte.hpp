#ifndef TRANSPORTE_HPP
#define TRANSPORTE_HPP

#include "Listas.hpp"

class Transporte{
    public:
        Transporte();
        ~Transporte();

        void InsereVertice();
        void InsereAresta(int v, int w);
        //determina a rota entre 2 vértices para um certo pacote
        //utilizaremos uma fila para obter a rota com a busca em largura e, posteriormente, inseriremos
        //o resultado em uma Lista Encadeada
        ListaEncadeada buscaLargura(int u, int v);

        //provavelmente não necessitaremos destes métodos
        int QuantidadeVertices();
        int QuantidadeArestas();

        int GrauMinimo();
        int GrauMaximo();

        void ImprimeVizinhos(int v);
        
    private:
        ListaAdjacencia armazens;
        ListaEncadeada* rotas;
};

#endif