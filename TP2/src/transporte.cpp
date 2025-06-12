#include "Listas.hpp"
#include "transporte.hpp"
#include "Fila.hpp"
#include <iostream>

Transporte::Transporte(int capacidade, int latencia, int intervalo, int numVert)
{
    capacidadeTransporte = capacidade;
    latenciaTransporte = latencia;
    intervaloTransporte = intervalo;
    numVertices = numVert;
}

Transporte::~Transporte()
{}

void Transporte::InsereVertice()
{
    int size = armazens.tamanho;
    armazens.InsereVert(size, size);
}

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

int Transporte::GrauMinimo()
{
    int* gVertex = armazens.geraVetorTam();
    //percorrer gVertex, encontrar o menor elemento e o vertice associado
    int min = gVertex[0];
    for(int i = 1; i < armazens.tamanho; i++)
    {
        if(gVertex[i] < min)
        {
            min = gVertex[i];
        }
    }
    return min;
}

int Transporte::GrauMaximo()
{
    int* gVertex =armazens.geraVetorTam();
    int max = gVertex[0];
    for(int i = 0; i < armazens.tamanho; i++)
    {
        if(gVertex[i] > max)
        {
            max = gVertex[i];
        }
    }
    return max;
}

void Transporte::ImprimeVizinhos(int v)
{
    NodeAdj *p = armazens.PosicionaEmAdj(v);
    p->listaArestas.Imprime();
}

void Transporte::insereCaminhoRec(ListaEncadeada& lista, int* pai, int atual, int origem)
{
    if (atual == -1) return;

    if (atual != origem)
        insereCaminhoRec(lista, pai, pai[atual], origem);

    // insere no fim da lista
    lista.inserePosicao(atual, lista.getTamanho());
}

void Transporte::buscaLargura(int origem, int destino, ListaEncadeada& rota)
{
    int n = numVertices;

    //adicionar no tratamento de exceções, acesso a posições inválidas de vetor
    /*if (origem < 0 || origem >= N || destino < 0 || destino >= N || N == 0) 
    {
        std::cerr << "Erro: Origem (" << origem << ") ou Destino (" << destino << ") invalidos para grafo com " << N << " vertices (esperado 0 a " << N-1 << ")." << std::endl;
        return ListaEncadeada(); // Retorna uma lista vazia para indicar erro/caminho não encontrado.
    }*/
    if (origem == destino)  
    {
        rota.inserePosicao(origem, 0);
    }

    bool* visitado = new bool[n]; // Array para marcar vértices visitados
    int* pai = new int[n];        // Array para armazenar o pai de cada vértice no caminho mais curto
    Fila Q;

    for (int i = 0; i < n; ++i) 
    { // Loop de 0 a N-1
        visitado[i] = false;
        pai[i] = -1; // -1 indica que não tem pai (ou não foi visitado)
    }

    visitado[origem] = true; // Marca o vértice de origem como visitado
    Q.Enfileira(origem);     // Adiciona o vértice de origem à fila

    // Variável para indicar se o destino foi encontrado durante a BFS
    bool destino_encontrado = false;

    while (!Q.Vazia() && !destino_encontrado) 
    {
        int u = Q.Desenfileira(); // Remove o vértice da frente da fila

        // Para cada vizinho 'v' de 'u'
        // Primeiro, precisamos obter a ListaEncadeada de adjacências de 'u'.
        NodeAdj* node_u = armazens.PosicionaEmAdj(u); // Obtém o NodeAdj correspondente ao vértice u
        
    /* tratamento de exceções - verificando se o node existe
        if (node_u == nullptr) 
        {
            std::cerr << "Aviso: Vertice " << u << " na fila da BFS nao encontrado na ListaAdjacencia." << std::endl;
            continue; 
        }
    */
        // Percorre a lista de adjacências de 'u'
        Node* vizinho_atual = node_u->listaArestas.head->prox; // Pula o nó dummy head da lista encadeada
        while (vizinho_atual != nullptr) {
            int v = vizinho_atual->aresta; // ID do vizinho

            if ((v >= 0) && (v < n) && (!visitado[v])) 
            { // Se 'v' está dentro dos limites e não foi visitado
                visitado[v] = true; // Marca 'v' como visitado
                pai[v] = u;         // Define 'u' como pai de 'v' (para reconstruir o caminho)
                Q.Enfileira(v);     // Adiciona 'v' à fila para ser processado

                if (v == destino) 
                { // Se 'v' é o destino, o caminho mais curto foi encontrado.
                    destino_encontrado = true;
                    break; // Sai do loop de vizinhos
                }
            }
            vizinho_atual = vizinho_atual->prox; // Move para o próximo vizinho na lista
        }
    }
    insereCaminhoRec(rota, pai, destino, origem);
    //ListaEncadeada rota_final; // A lista encadeada que conterá os IDs dos armazéns na rota

    /*if (destino_encontrado) 
    { 
        int atual = destino;
        // Percorre de destino para origem usando o array 'pai', adicionando no início da rota
        while (atual != -1 && atual != origem) 
        { 
            rota_final.inserePosicao(atual, 0); 
            atual = pai[atual];
        }
        if (atual == origem) 
        {
            rota_final.inserePosicao(origem, 0);
        } 
        else //tratamento de erros - erro na obtenção de algum item
        {
            // Se 'atual' se tornou -1 antes de atingir a origem, significa que o caminho estava quebrado
            // ou a origem não tinha pai (-1). Isso não deveria acontecer se destino_encontrado é true.
            std::cerr << "Erro: Reconstrucao de rota inconsistente para " << origem << "->" << destino << std::endl;
            rota_final.Limpa(); // Limpa rota se houver inconsistência
        }
    } 
    else  //tratamento de exceções, caso a rota não seja encontrada
    {
        // O destino não foi alcançado a partir da origem.
        // A lista 'rota_final' já estará vazia.
        std::cerr << "Rota de " << origem << " para " << destino << " nao encontrada." << std::endl;
    }*/
    delete[] visitado;
    delete[] pai;
}

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