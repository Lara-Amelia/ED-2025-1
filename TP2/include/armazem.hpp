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
    int destino;
    //checar se o tipo do destino deve ser índice (como na indexação de vértices) ou o armazém em si

    public:
    Secao();
    void Limpa();

    friend class Armazem;
};

//os armazéns são os vértices de um grafo
class Armazem
{
    private:
    Secao* secoes; //será usado como um vetor de seções com tamanho igual à quantidade de adjacencias 
    
    public:
    void armazenaPacote(Pacote item, int destino);
    //deve contabilizar o tempo necessário para recuperar o pacote de fato
    //o destino pode ser obtido a partir da rota
    Pacote recuperaPacote(int identificador, int destino);
    //transfere os pacotes da pilha principal para a auxiliar 
    void esvaziaPrincipal(Pilha principal, Pilha auxiliar, int destino); 
    //retir os capacidade primeiros elementos da pilha auxiliar
    void carregaTransporte(Pilha auxiliar, int capacidade, int destino);
    //retorna os elementos que ficaram na pilha auxiliar para a principal
    //talvez o parâmetro possa ser só a seção (em todos os lugares onde passamos ambas as pilhas)
    void retornaPrincipal(Pilha principal, Pilha auxiliar);
};

#endif