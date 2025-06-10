#ifndef ARMAZEM_HPP
#define ARMAZEM_HPP
#include "pilha.hpp"
#include "pacote.hpp"

//classe que representa as seções presentes nos armazéns
//em cada armazém teremos um vetor de seções, correspondendo às arestas
//com diferentes vértices do grafo
class Secao
{
    private:
    Pilha principal; //pilha que recebe novos pacotes
    Pilha auxiliar;  //pilha para desempilar e carregar com pacotes mais antigos
    int destino;     //armazena a qual outro armazém a seção se refere

    public:
    Secao();
    void Limpa();

    friend class Armazem;
};

//os armazéns são os vértices de um grafo
class Armazem
{
    private:
    Secao* secoes; //será usado como um vetor de seções com tamanho igual à quantidade de adjacencias do vértice
    int nroAdj; //registra o número de adjacências do vértice/armazém - tamanho do vetor de seções
    int idGrafo; //armazena a id do armazem no grafo - pode facilitar pesquisas no grafo

    
    public:
    void armazenaPacote(Pacote item, int destino); //insere o pacote na pilha principal da seção correspondente

    //deve contabilizar o tempo necessário para recuperar o pacote de fato
    //o destino pode ser obtido a partir da rota
    Pacote recuperaPacote(int identificador, int destino);

    //transfere os pacotes da pilha principal para a auxiliar 
    void esvaziaPrincipal(Pilha principal, Pilha auxiliar, int destino); 

    //retira os capacidade primeiros elementos da pilha auxiliar
    void carregaTransporte(Pilha auxiliar, int capacidade, int destino);

    //retorna os elementos que ficaram na pilha auxiliar para a principal - pacote rearmazenado
    //talvez o parâmetro possa ser só a seção (em todos os lugares onde passamos ambas as pilhas)
    //é melhor do que sempre buscar a seção de referência
    void retornaPrincipal(Pilha principal, Pilha auxiliar);
};

#endif