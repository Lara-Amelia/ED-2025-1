#include "pacote.hpp"
#include <iostream>

Pacote::~Pacote()
{}

//constutor utilizado na leitura da main
Pacote::Pacote(int id, int hora, int origem, int destino, int estado)
{
    identificador = id;
    horaPostagem = hora;
    armazemOrigem = origem;
    armazemDestino = destino;
    estadoAtual = estado;
    //o construtor para a lista encadeada é chamado automaticamente
}

Pacote::Pacote() 
{
    identificador = 0;
    horaPostagem = 0;
    armazemOrigem = 0;
    armazemDestino = 0;
    armazemAtual = 0;
    estadoAtual = 0;
    tempoArmazenado = 0;
    tempoTransporte = 0;
    // rota será inicializada por seu próprio construtor padrão
}

void Pacote::setDados(int id, int hora, int origem, int destino, int estado) 
{
    identificador = id;
    horaPostagem = hora;
    armazemOrigem = origem;
    armazemDestino = destino;
    armazemAtual = origem; // geralmente começa no armazem de origem
    estadoAtual = estado;
}

void Pacote::setEstadoAtual(int n)
{
    estadoAtual = n;
}

void Pacote::setArmAtual(int n)
{
    armazemAtual = n;
}

void Pacote::setId(int n)
{
    identificador = n;
}

//métodos getters
int Pacote::getArmDestino()
{
    return armazemDestino;
}

int Pacote::getArmOrigem()
{
    return armazemOrigem;
}

int Pacote::getArmAtual()
{
    return armazemAtual;
}

int Pacote::getId()
{
    return identificador;
}

int Pacote::getHora()
{ 
    return horaPostagem;
}

int Pacote::getEstado()
{
    return estadoAtual;
}

//obtem o próximo vértice/armazem na rota do pacote
int Pacote::getProximoRota()
{
    if (this->rota.getTamanho() == 0) 
    {
        throw std::out_of_range ("ERRO: Rota esta vazia. Nao ha proximo armazem.");
    }
    
    Node* p = this->rota.head;
    while (p != nullptr) 
    {
        if (p->aresta == this->armazemAtual) 
        { 
            if (p->prox != nullptr) 
            {
                //não é o último armazém, retorna o valor do próximo nó
                return p->prox->aresta;
            } 
            else 
            {
                //é o último armazém na rota (o destino final).
                return -1; //retorna -1 como flag para indicar que o pacote já está no destino final.
            }
        }
        p = p->prox; 
    }   
    throw std::out_of_range ("ERRO: Armazem atual não encontrado na rota. Inconsistencia de dados.");
}

//construtor de cópia para a classe, caso seja necessário
Pacote::Pacote(const Pacote& outro)
{
    identificador = outro.identificador;
    horaPostagem = outro.horaPostagem;
    armazemOrigem = outro.armazemOrigem;
    armazemDestino = outro.armazemDestino;
    armazemAtual = outro.armazemAtual;
    estadoAtual = outro.estadoAtual;
    tempoArmazenado = outro.tempoArmazenado;
    tempoTransporte = outro.tempoTransporte;
    rota = outro.rota;  
}

//sobrecarga do operador de igualdade caso seja necessário para cópias
Pacote& Pacote::operator=(const Pacote& outro)
{
    if (this != &outro)
    {
        identificador = outro.identificador;
        horaPostagem = outro.horaPostagem;
        armazemOrigem = outro.armazemOrigem;
        armazemDestino = outro.armazemDestino;
        armazemAtual = outro.armazemAtual;
        estadoAtual = outro.estadoAtual;
        tempoArmazenado = outro.tempoArmazenado;
        tempoTransporte = outro.tempoTransporte;
        rota = outro.rota;
    }
    return *this;
}