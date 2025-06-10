#ifndef PACOTE_HPP
#define PACOTE_HPP
#include "Listas.hpp"
#include <string>

//talvez criar uma struct que armazene o estado e o momento em que entrou e saiu dele,
//para facilitar a obtenção de estatísticas sobre o pacote
class registroEstado
{
    private:
    int estadoAtual;
    int tempoInicio;
    int tempoFim;
    int tempoPercorrido;

    public:
    registroEstado();

    void setEstado(int n); //identificadores de estado
    void setTempoInicio(int t);
    void setTempoFim(int t);
    void setTempoPercorrido();

    int getEstado();
    int getTempoInicio();
    int getTempoFim();
    int getTempoPercorrido();

    friend class Pacote;
};

class Pacote
{
    private: 
    int identificador;

    int horaPostagem;
    int armazemOrigem;
    int armazemDestino;
  
    ListaEncadeada rota; //rota a ser obtida via busca em largura no grafo

    //no construtor do TAD Pacote, deve ser inicializado de acordo com o tamanho da rota
    //a cada trânsito entre vértices, temos 2 estados e mais alguns extras
    //todos são inicializados da mesma forma e depois preenchidos
    registroEstado* estadosPacote;
    
    //estat´siticas a serem calculadas no fim do evento com base nos dados no vetor estadosPacote
    int tempoArmazenado;
    int tempoTransporte;

    public:
    //os valores não passados como parâmetro serão inicializados como 0 e preenchidos depois (sets)
    //construtor default oara inicialização de nós na fila - checar depois
    Pacote();
    Pacote(int id, int hora, int origem, int destino); //construtor default
    ~Pacote();

    void setId(int n);
    int calculaTempoArmazenado(registroEstado* estados);
    int calculaTempoTransporte(registroEstado* estados);
    
    friend class Pilha;
};


#endif