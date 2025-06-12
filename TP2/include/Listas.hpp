#ifndef LISTAS_HPP
#define LISTAS_HPP

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//Implementação da Lista Encadeada que será utilizada no sistema
//teremos de usar para Transporte (grafo) e definição de rotas
//se os aramazéns forem indexados como vértices (1, 2, ..., n), podemos manter como está
class Node
{
    private:
    int aresta;
    Node *prox;

    public:
    //construtor para nodes
    Node();
    Node (int valor);

    friend class Transporte;
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
    void setAresta(int pos, int novoNode);
    int getAresta(int pos);
    int getTamanho();
    //void insereInicio(int item);
    //void insereFinal(int item);
    void inserePosicao(int item, int pos);
    int pesquisa(int pesquisado);
    void Imprime();
    void Limpa();

    friend class Transporte;
    friend class ListaAdjacencia;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//Implementaçaõ da Lista de Adjacencia que será utilizada na implementação 
//(especificamente, para o TAD Transporte, que é, em si, um grafo)
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

    friend class Transporte;
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
    int* geraVetorTam();

    friend class Transporte;
};

#endif