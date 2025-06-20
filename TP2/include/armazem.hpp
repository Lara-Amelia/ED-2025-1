#ifndef ARMAZEM_HPP
#define ARMAZEM_HPP
#include "pilha.hpp"
#include "pacote.hpp"

//classe que representa as seções presentes nos armazéns
//em cada armazém teremos um vetor de seções, correspondendo a cada destino possível para os pacotes
class Secao
{
    private:
    Pilha principal; //pilha que recebe novos pacotes
    Pilha auxiliar;  //pilha para desempilhar e carregar com pacotes mais antigos
    int destino;     //armazena a qual outro armazém a seção se refere

    public:
    Secao();                  //construtor default para seções  
    Secao(int dest);          //construtor que inicializa seções com o devido valor de destino
    void Limpa();             //método para limpar as pilhas da seção
    void setDestino(int n);   //método setter para o destino das seções

    friend class Armazem;
};

class Armazem
{
    private:
    Secao* secoes;      //será usado como um vetor de seções 
    int nroAdj;         //registra o número de adjacências do vértice/armazém 
    int* vizinhos;      //vetor para registrar os vizinhos armazém - a partir dele chamaremos os construtores para seções
    int idGrafo;        //armazena a id do armazem no grafo - pode facilitar
    int custoRemocao;   //armazena o custo de remoção 

    public:
    Armazem(int nAdj, int idG, int custo);
    Armazem();          
    ~Armazem();         

    void setArmazem(int nAdj, int idG, int custo);
    void setDestinoSecao(int destino, int posicao);
    void setVizinho(int vizinho, int posicao);
    
    void armazenaPacote(Pacote* item, int posSecao); //insere o pacote na pilha principal da seção correspondente

    //método que definirá com qual seção estamos lidando
    //deve ser chamado antes do início de operações que utilizaram uma certa seção,
    //para que não precisemos rebuscar a seção sempre
    int encontraSecao(int destino);

    //deve contabilizar o tempo necessário para recuperar o pacote de fato
    //o destino pode ser obtido a partir da rota
    //Pacote recuperaPacote(int identificador, int destino);

    //o custo de remoção é o tamanho da pilha vezes o custo de remoção dado na entrada
    //transfere os pacotes da pilha principal para a auxiliar 
    Pacote* esvaziaPrincipal(int posSecao); 

    int tamSecaoAux(int posSecao);
    bool checaVaziaAux(int posSecao);
    //retira os capacidade primeiros elementos da pilha auxiliar
    Pacote* carregaTransporte(int capacidade, int destino, int posSecao);

    //retorna os elementos que ficaram na pilha auxiliar para a principal - pacote rearmazenado
    //talvez o parâmetro possa ser só a seção (em todos os lugares onde passamos ambas as pilhas)
    //é melhor do que sempre buscar a seção de referência
    Pacote* retornaPrincipal(int posSecao);
    int tamSecaoPrincipal(int posSecao);
    bool checaVazia(int posSecao);

    void setAdj(int n);
};

#endif