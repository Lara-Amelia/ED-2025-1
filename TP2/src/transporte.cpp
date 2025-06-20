#include "Listas.hpp"
#include "transporte.hpp"
#include "Fila.hpp"
#include <iostream>

//construtor para a classe Transporte
Transporte::Transporte(int capacidade, int latencia, int intervalo, int numVert)
{
    capacidadeTransporte = capacidade;
    latenciaTransporte = latencia;
    intervaloTransporte = intervalo;
    numVertices = numVert;
}

//destrutor para a classe (chama os destrutores de seus outros membros, que são listas)
Transporte::~Transporte()
{}

//insere vértices na estrutura do grafo
void Transporte::InsereVertice()
{
    int size = armazens.tamanho;
    armazens.InsereVert(size, size);
}

//insere arestas na estrutura do grafo
void Transporte::InsereAresta(int v, int w)
{
    armazens.InsereAresta(v, w);
}

int Transporte::QuantidadeVertices()
{
    return armazens.tamanho;
}

int Transporte::QuantidadeArestas()
{
    int qtArestas = 0;
    NodeAdj* p = armazens.head;
    for(int i = 0; i < armazens.tamanho; i++)
    {
        p = p->prox;
        qtArestas += p->listaArestas.tamanho;
    }
    return qtArestas/2;
}

//insere a rota obtida com a busca em largura em uma lista encadeada recursivamente
void Transporte::insereCaminhoRec(ListaEncadeada& lista, int* pai, int atual, int origem)
{
    if (atual == -1) return;
    if (atual != origem)
        insereCaminhoRec(lista, pai, pai[atual], origem);
    lista.inserePosicao(atual, lista.getTamanho());
}

//obtém o menor caminho possível entre 2 vértices utilizando uma busca em largura no grafo
void Transporte::buscaLargura(int origem, int destino, ListaEncadeada& rota)
{
    int n = numVertices;

    if (origem < 0 || origem >= numVertices || destino < 0 || destino >= numVertices || numVertices == 0) 
    {
        throw std::out_of_range("Erro: Origem ou Destino inválidos para busca em largura");
    }
    if (origem == destino)  
    {
        rota.inserePosicao(origem, 0);
        return;
    }

    bool* visitado = new bool[n]; //array para marcar vértices visitados
    int* pai = new int[n];        //array para armazenar o pai de cada vértice no caminho mais curto
    Fila Q;

    for (int i = 0; i < n; ++i) 
    {
        visitado[i] = false;
        pai[i] = -1; // -1 indica que não tem pai (ou não foi visitado)
    }

    visitado[origem] = true; //marca o vértice de origem como visitado
    Q.Enfileira(origem);     //adiciona o vértice de origem à fila

    //variável para indicar se o destino foi encontrado 
    bool destino_encontrado = false;

    while (!Q.Vazia() && !destino_encontrado) 
    {
        int u = Q.Desenfileira(); //remove o vértice da frente da fila
        NodeAdj* node_u = armazens.PosicionaEmAdj(u); //obtém o NodeAdj correspondente ao vértice u
        
        if (node_u == nullptr) 
        {
            throw std::out_of_range("Aviso: Vertice não encontrado ListaAdjacencia");
            continue; 
        }
    
        Node* vizinho_atual = node_u->listaArestas.head->prox; 
        while (vizinho_atual != nullptr) 
        {
            int v = vizinho_atual->aresta; 
            if ((v >= 0) && (v < n) && (!visitado[v])) 
            { 
                visitado[v] = true; //marca 'v' como visitado
                pai[v] = u;         //define 'u' como pai de 'v' (para reconstruir o caminho)
                Q.Enfileira(v);     //adiciona 'v' à fila para ser processado

                //caminho encontrado/fim da rota
                if (v == destino) 
                {
                    destino_encontrado = true;
                    break; 
                }
            }
            vizinho_atual = vizinho_atual->prox; 
        }
    }

    //insere a rota obtida em uma lista encadeada recursivamente
    insereCaminhoRec(rota, pai, destino, origem);
    delete[] visitado;
    delete[] pai;
}

//métodos getters
int Transporte::getCapacTransp()
{
    return capacidadeTransporte;
}

int Transporte::getLatTransp()
{
    return latenciaTransporte;
}

int Transporte::getIntervTransp()
{
    return intervaloTransporte;
}
        
int Transporte::getNumVertices()
{
    return numVertices;
}