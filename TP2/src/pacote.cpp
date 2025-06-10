#include "pacote.hpp"
#include <iostream>

registroEstado::registroEstado()
{
    estadoAtual = -1;
    tempoInicio = -1;
    tempoFim = -1;
    tempoPercorrido = -1;
}

void registroEstado::setEstado(int n)
{
    estadoAtual = n;
}

void registroEstado::setTempoFim(int t)
{
    tempoFim = t;
}

void registroEstado::setTempoInicio(int t)
{
    tempoInicio = t;
}

//este método set não recebe parametros, mas utiliza atributos da classe para obter o resultado
void registroEstado::setTempoPercorrido()
{
    tempoPercorrido = tempoFim - tempoInicio;
}

int registroEstado::getEstado()
{
    return estadoAtual;
}

int registroEstado::getTempoFim()
{
    return tempoFim;
}

int registroEstado::getTempoInicio()
{
    return tempoInicio;
}

int registroEstado::getTempoPercorrido()
{
    return tempoPercorrido;
}

//constutor utilizado na leitura da main
Pacote::Pacote(int id, int hora, int origem, int destino)
{
    identificador = id;
    horaPostagem = hora;
    armazemOrigem = origem;
    armazemDestino = destino;
    //será inicializado após o cálculo da rota
    estadosPacote = nullptr;
    //o construtor para a lista encadeada é chamado automaticamente
}

Pacote::~Pacote()
{
    rota.Limpa();
    delete[] estadosPacote;
}
