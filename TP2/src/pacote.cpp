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

Pacote::Pacote()
{
    identificador = -1;
    horaPostagem = 0;
    armazemOrigem = -1;
    armazemDestino = -1;
    
    // 'rota' é um objeto ListaEncadeada. O construtor default de ListaEncadeada
    // será chamado automaticamente para inicializar 'rota'.
    
    estadosPacote = nullptr; // MUITO IMPORTANTE: Inicializa o ponteiro para NULO.
                             // Isso evita que o destrutor tente deletar um endereço de memória lixo.
    tempoArmazenado = 0;
    tempoTransporte = 0;
}

Pacote::~Pacote()
{
    rota.Limpa();
    delete[] estadosPacote;
}

int Pacote::getId()
{
    return identificador;
}

void Pacote::setId(int n)
{
    identificador = n;
}

void Pacote::setRota(ListaEncadeada rotaCalculada)
{
    rota = rotaCalculada;
}