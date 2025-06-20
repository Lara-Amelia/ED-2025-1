#include "evento.hpp" 
#include "pacote.hpp"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

//construtor de cópia para evento, caso seja necessário
Evento::Evento(const Evento& other) 
{
    chavePrioridade = other.chavePrioridade;
    tipoEvento = other.tipoEvento;
    tempoInicio = other.tempoInicio;
    idPacote = other.idPacote;
    armazemOrigemEvento = other.armazemOrigemEvento;
    armazemDestinoEvento = other.armazemDestinoEvento;
    pacotePtr = other.pacotePtr; 
}

//sobrecarga do operador de = para cópias
Evento& Evento::operator=(const Evento& other)
{
    if (this != &other) {
        chavePrioridade = other.chavePrioridade;
        tipoEvento = other.tipoEvento;
        tempoInicio = other.tempoInicio;
        idPacote = other.idPacote;
        armazemOrigemEvento = other.armazemOrigemEvento;
        armazemDestinoEvento = other.armazemDestinoEvento;
        pacotePtr = other.pacotePtr;
    }
    return *this;
}

Evento::Evento() 
{
    chavePrioridade = "";
    tipoEvento = 0;
    tempoInicio = 0;
    idPacote = 0;
    armazemOrigemEvento = 0;
    armazemDestinoEvento = 0;
    pacotePtr = nullptr;
}

//implementação do construtor user defined de Evento
Evento::Evento(std::string chave, int tipo, int t, int idPacote, int aOrig, int aDest, Pacote* ptr)
{
    chavePrioridade = chave;
    tipoEvento = tipo;
    tempoInicio = t;
    idPacote = idPacote;
    armazemOrigemEvento = aOrig;
    armazemDestinoEvento = aDest;
    pacotePtr = ptr;
}

//implementações dos métodos getters da classe
std::string Evento::getChave() const 
{ 
    return chavePrioridade; 
}

int Evento::getTipoEvento() const
{ 
    return tipoEvento; 
}

int Evento::getTempoInicio() const 
{
    return tempoInicio; 
}

int Evento::getIdPacote() const
{ 
    return idPacote; 
}

int Evento::getArmazemOrigem() const 
{ 
    return armazemOrigemEvento; 
}

int Evento::getArmazemDestino() const 
{ 
    return armazemDestinoEvento; 
}

Pacote* Evento::getPacotePtr() const 
{ 
    return pacotePtr; 
}

void Evento::setEvento(
    const std::string& chave, 
    int tipo, 
    int subtipo, 
    int tInicio, 
    int id_p, 
    int a_orig, 
    int a_dest, 
    Pacote* pacote)
{
    chavePrioridade = chave;
    tipoEvento = tipo;
    tempoInicio = tInicio;
    idPacote = id_p;
    armazemOrigemEvento = a_orig;
    armazemDestinoEvento = a_dest;
    pacotePtr = pacote; // supõe que Pacote tem copy constructor válido
}

//constrói a chave de eventos relacionados a pacote (armazenamento e entrega)
std::string Evento::construirChavePacote(int tempo, int idPacote) 
{
    std::stringstream ss;

    ss << std::setfill('0'); //preencher com zeros à esquerda

    //parte 1: Tempo (6 dígitos)
    ss << std::setw(6) << tempo; 

    //parte 2: ID do Pacote (6 dígitos)
    ss << std::setw(6) << idPacote; 

    //parte 3: Tipo (1 dígito)
    ss << std::setw(1) << 1; //tipo 1 para Evento de Pacote

    std::string resultado = ss.str();

    return resultado;
}

//constrói chave para eventos de transporte
std::string Evento::construirChaveTransporte(int tempo, int origemTransp, int destinoTransp) 
{
    std::stringstream ss;

    ss << std::setfill('0'); //preencher com zeros à esquerda

    //parte 1: Tempo (6 dígitos)
    ss << std::setw(6) << tempo;

    //parte 2: Origem (3 dígitos)
    ss << std::setw(3) << origemTransp;

    //parte 3: Destino (3 dígitos)
    ss << std::setw(3) << destinoTransp;

    //parte 4: Tipo (1 dígito)
    ss << std::setw(1) << 2; //tipo 2 para Evento de Transporte

    std::string resultado = ss.str();

    return resultado;
}

//funções para decodificar a chave (inverso das funções de construção) ---
int Evento::decodificarTipoEvento(std::string chave) 
{
    return std::stoi(chave.substr(12, 1)); 
}

int Evento::decodificarTempoEvento(std::string chave) 
{
    return std::stoi(chave.substr(0, 6));  
}

//para decodificar o ID do Pacote (para Tipo 1)
int Evento::decodificarIdPacote(std::string chave) 
{
    if (Evento::decodificarTipoEvento(chave) == 1) 
    { 
        return std::stoi(chave.substr(6, 6)); // 6 caracteres a partir do índice 6
    }
    return -1; // Retorna -1 se não for evento de pacote ou inválido
}

//para decodificar origem (para Tipo 2)
int Evento::decodificarOrigemTransporte(std::string chave) 
{
    if (Evento::decodificarTipoEvento(chave) == 2) 
    { 
        return std::stoi(chave.substr(6, 3)); // 3 caracteres a partir do índice 6
    }
    return -1;
}

// Para decodificar Destino (para Tipo 2)
// Destino está nos 3 dígitos antes do Tipo
int Evento::decodificarDestinoTransporte(std::string chave) 
{
    if (Evento::decodificarTipoEvento(chave) == 2) 
    { 
        return std::stoi(chave.substr(9, 3)); 
    }
    return -1;
}