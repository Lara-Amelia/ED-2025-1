#ifndef PACOTE_HPP
#define PACOTE_HPP
#include "Listas.hpp"
#include <string>

//talvez criar uma struct que armazene o estado e o momento em que entrou e saiu dele,
//para facilitar a obtenção de estatísticas sobre o pacote

class Pacote
{
    private: 
    int identificador;

    int horaPostagem;
    std::string nomeRemetente;
    std::string nomeDestinatario;
    int armazemOrigem;
    int armazemDestino;
    //conferir qual é o valor dessa variavel
    int tipo;
    int estado; //utilizaremos uma legenda para significar cada estado
    int tempoArmazenado;
    int tempoTransporte;
    ListaEncadeada rota;

    public:
    Pacote(); //construtor default
    void setId(int id);
    //as principais operações necessárias para o TAD pacote tem a ver com o registro de tempo 
    friend class Pilha;
};


#endif