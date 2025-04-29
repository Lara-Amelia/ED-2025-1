#include <iostream>
#include <string>
#include <sstream>
#include "graph.hpp"
#include "ListaAdjacencia.hpp"
#include "ListaEncadeada.hpp"

int main(int argc, char **argv)
{
    std::string opcao = argv[1];
    int n, m;
    std::cin >> n; std::cin.ignore();
    Grafo grafo; //cria um novo grafo
    /*lê as n linhas com os dados de cada vértice do grafo
      e insere os dados no grafo                          */
    for(int i = 0; i < n; i++)
    {
        std::string linha;
        std::getline(std::cin, linha);
        std::istringstream iss(linha);
        iss >> m;
        int* vizinhos = new int[m];
        grafo.InsereVertice();
        for(int j = 0; j < m; j++)
        {
            iss >> vizinhos[j];
            grafo.InsereAresta(i, vizinhos[j]);
        }
        delete[] vizinhos;
    }

    //dados básicos
    if(opcao == "-d")
    {
        int qtVertices = grafo.QuantidadeVertices();
        int qtArestas = grafo.QuantidadeArestas();
        int gMin = grafo.GrauMinimo();
        int gMax = grafo.GrauMaximo();
        std::cout << qtVertices << std::endl << qtArestas << std::endl
                  << gMin << std::endl << gMax << std::endl; 
    }
    //vizinhanças
    else if(opcao == "-n")
    {
        //checar limites de intervalo
        for(int i = 0; i < n; i++)
        {
            grafo.ImprimeVizinhos(i);
        }
    }
    //é ou não grafo completo - checar usando os demais métodos 
    else if(opcao == "-k")
    {
        //int gMin = grafo.GrauMinimo(); int gMax = grafo.GrauMaximo();
        int qArestas = grafo.QuantidadeArestas();
        if(qArestas != (n*(n-1))/2)
            std::cout << "0" << std::endl;
        else
            std::cout << "1" << std::endl;
    }
}