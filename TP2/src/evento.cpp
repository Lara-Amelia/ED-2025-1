#include "evento.hpp" // Inclui o cabeçalho da própria classe
#include "pacote.hpp"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
//TODOS OS PRINTS DEVEM SER RELIZADOS NA CLASSE EVENTO

// Implementação do construtor de Evento (permanece o mesmo)
Evento::Evento(std::string chave, int tipo, int subtipo, int t, int id_p, int a_orig, int a_dest, Pacote* ptr) :
    chave_prioridade(chave),
    tipo_evento(tipo),
    subTipoEvento(subtipo),
    tempoInicio(t),
    id_pacote(id_p),
    armazem_origem_evento(a_orig),
    armazem_destino_evento(a_dest),
    pacote_ptr(ptr)
{
    
}

int Evento::getSubtipoEvento() const
{
    return subTipoEvento;
}

void Evento::setTempoFim(int n)
{
    tempoFim = n;
}

// Implementações dos métodos Getters (permanecem os mesmos)
std::string Evento::getChave() const 
{ 
    return chave_prioridade; 
}

int Evento::getTipoEvento() const
{ 
    return tipo_evento; 
}

int Evento::getTempoInicio() const 
{
    return tempoInicio; 
}

int Evento::getTempoFim() const
{
    return tempoFim;
}

int Evento::getIdPacote() const
{ 
    return id_pacote; 
}

int Evento::getArmazemOrigem() const 
{ 
    return armazem_origem_evento; 
}

int Evento::getArmazemDestino() const 
{ 
    return armazem_destino_evento; 
}

Pacote* Evento::getPacotePtr() const 
{ 
    return pacote_ptr; 
}

std::string Evento::construirChavePacote(int tempo, int id_pacote) 
{
    std::stringstream ss;
    ss << std::setfill('0'); // Preencher com zeros à esquerda

    // Parte 1: Tempo (6 dígitos)
    ss << std::setw(6) << tempo; 

    // Parte 2: ID do Pacote (6 dígitos)
    ss << std::setw(6) << id_pacote; 

    // Parte 3: Tipo (1 dígito)
    ss << std::setw(1) << 1; // Tipo 1 para Evento de Pacote

    std::string resultado = ss.str();
    // Converte a string formatada para long long
    return resultado;
}

// Função para construir a chave de prioridade para um Evento de Transporte (Tipo 2)
// Formato da Chave (13 dígitos): [Tempo(6)][Origem(3)][Destino(3)][Tipo(1)]
// Exemplo: 000401 002 001 2  =>  0004010020012
std::string Evento::construirChaveTransporte(int tempo, int origem_transp, int destino_transp) 
{
    std::stringstream ss;
    ss << std::setfill('0'); // Preencher com zeros à esquerda

    // Parte 1: Tempo (6 dígitos)
    ss << std::setw(6) << tempo;

    // Parte 2: Origem (3 dígitos)
    ss << std::setw(3) << origem_transp;

    // Parte 3: Destino (3 dígitos)
    ss << std::setw(3) << destino_transp;

    // Parte 4: Tipo (1 dígito)
    ss << std::setw(1) << 2; // Tipo 2 para Evento de Transporte

    std::string resultado = ss.str();
    // Converte a string formatada para long long
    return resultado;
}

// --- Funções para decodificar a chave (inverso das funções de construção) ---
// Ajustadas para o formato: [Tempo(6)][Dados(6)][Tipo(1)]

int Evento::decodificarTipoEvento(std::string chave) 
{
    // O tipo é o último dígito (o mais à direita)
    return std::stoi(chave.substr(12, 1)); 
}

int Evento::decodificarTempoEvento(std::string chave) 
{
    // O tempo são os 6 dígitos mais à esquerda de uma chave de 13 dígitos
    // Remover os 6 dígitos de dados e 1 dígito de tipo (total 7 dígitos da direita)
    return std::stoi(chave.substr(0, 6));  // Divide por 10^7
}

// Para decodificar o ID do Pacote (para Tipo 1)
// ID está nos 6 dígitos do meio (entre Tempo e Tipo)
int Evento::decodificarIdPacote(std::string chave) 
{
    if (Evento::decodificarTipoEvento(chave) == 1) 
    { 
        return std::stoi(chave.substr(6, 6)); // 6 caracteres a partir do índice 6
    }
    return -1; // Retorna -1 se não for evento de pacote ou inválido
}

// Para decodificar Origem (para Tipo 2)
// Origem está nos 3 dígitos antes do Destino (que está antes do Tipo)
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
        return std::stoi(chave.substr(9, 3)); // 3 caracteres a partir do índice 6
    }
    return -1;
}

// Copy constructor
Evento::Evento(const Evento& other) 
{
    // Copy all members, including deep copy if needed
    chave_prioridade = other.chave_prioridade;
    tipo_evento = other.tipo_evento;
    subTipoEvento = other.subTipoEvento;
    tempoInicio = other.tempoInicio;
    tempoFim = other.tempoFim;
    id_pacote = other.id_pacote;
    armazem_origem_evento = other.armazem_origem_evento;
    armazem_destino_evento = other.armazem_destino_evento;
    pacote_ptr = other.pacote_ptr; // if Pacote supports copy ctor
}

// Copy assignment operator
Evento& Evento::operator=(const Evento& other)
{
    if (this != &other) {
        chave_prioridade = other.chave_prioridade;
        tipo_evento = other.tipo_evento;
        subTipoEvento = other.subTipoEvento;
        tempoInicio = other.tempoInicio;
        tempoFim = other.tempoFim;
        id_pacote = other.id_pacote;
        armazem_origem_evento = other.armazem_origem_evento;
        armazem_destino_evento = other.armazem_destino_evento;
        pacote_ptr = other.pacote_ptr;
    }
    return *this;
}

Evento::Evento() 
{
    chave_prioridade = "";
    tipo_evento = 0;
    subTipoEvento = 0;
    tempoInicio = 0;
    tempoFim = 0;
    id_pacote = 0;
    armazem_origem_evento = 0;
    armazem_destino_evento = 0;
    pacote_ptr = nullptr;
    // pacote_ptr será inicializado pelo construtor padrão do Pacote automaticamente
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
    chave_prioridade = chave;
    tipo_evento = tipo;
    subTipoEvento = subtipo;
    tempoInicio = tInicio;
    id_pacote = id_p;
    armazem_origem_evento = a_orig;
    armazem_destino_evento = a_dest;
    pacote_ptr = pacote; // supõe que Pacote tem copy constructor válido
}

void Evento::what()
{
    //se o evento for armazenamneto (postagem ou chegou a um novo armazém na rota)
    if(this->subTipoEvento == 1)
    {
         std::cout << std::setfill('0') << std::setw(7) << this->tempoInicio << " pacote " << std::setw(3) 
                   << this->id_pacote << " armazenado em " << std::setw(3) << this->pacote_ptr->getArmAtual() 
                   << " na secao " << std::setw(3) << this->pacote_ptr->getProximoRota() << std::endl;
    }

    else if(this->subTipoEvento == 2)
    {
        std::cout << std::setfill('0') << std::setw(7) << this->tempoInicio << " pacote " << std::setw(3) 
                  << this->id_pacote << " removido de " << std::setw(3) << this->pacote_ptr->getArmAtual() 
                  << " na secao " << std::setw(3) << this->pacote_ptr->getProximoRota() << std::endl;
    }

    else if(this->subTipoEvento == 3)
    {
        std::cout << std::setfill('0') << std::setw(7) << this->tempoInicio << " pacote " << std::setw(3) 
                  << this->id_pacote << " em transito de " << std::setw(3) << this->pacote_ptr->getArmAtual() 
                  << " para " << std::setw(3) << this->pacote_ptr->getProximoRota() << std::endl;
    }

    else if(this->subTipoEvento == 4)
    {
        std::cout << std::setfill('0') << std::setw(7) << this->tempoInicio << " pacote " << std::setw(3) 
                  << this->id_pacote << " rearmazenado em " << std::setw(3) << this->pacote_ptr->getArmAtual() 
                  << " na secao " << std::setw(3) << this->pacote_ptr->getProximoRota() << std::endl;
    }

    else if(this->subTipoEvento == 5)
    {
        std::cout << std::setfill('0') << std::setw(7) << this->tempoInicio << " pacote " << std::setw(3) 
                  << this->id_pacote << " entregue " << std::setw(3) << this->pacote_ptr->getArmAtual();
    }
}


/*
// Função para construir a chave de prioridade para um Evento de Pacote (Tipo 1)
// Chave final: TT TTTT PP PPPP T (13 dígitos)
// Tempo (6), Pacote ID (6), Tipo (1)
long long Evento::construirChavePacote(int tempo, int id_pacote) 
{
    return (static_cast<long long>(tempo) * 10000000LL) // Tempo nos 6 dígitos mais à esquerda
           + (static_cast<long long>(id_pacote) * 10LL)     // ID do pacote nos próximos 6 dígitos
           + 1LL; // Tipo 1 para evento de Pacote (último dígito)
}

// Função para construir a chave de prioridade para um Evento de Transporte (Tipo 2)
// Chave final: TT TTTT OOO DDD T (13 dígitos)
// Tempo (6), Origem (3), Destino (3), Tipo (1)
long long Evento::construirChaveTransporte(int tempo, int origem_transp, int destino_transp) 
{
    return (static_cast<long long>(tempo) * 10000000LL) // Tempo nos 6 dígitos mais à esquerda
           + (static_cast<long long>(origem_transp) * 10000LL) // Origem nos próximos 3 dígitos
           + (static_cast<long long>(destino_transp) * 10LL)   // Destino nos próximos 3 dígitos
           + 2LL; // Tipo 2 para evento de Transporte (último dígito)
}

// Funções para decodificar a chave
int Evento::decodificarTipoEvento(long long chave) 
{
    return static_cast<int>(chave % 10LL); // Último dígito é o tipo
}

int Evento::decodificarTempoEvento(long long chave) {
    // Tempo está nos 6 dígitos mais à esquerda da chave de 13 dígitos
    return static_cast<int>(chave / 10000000LL); // Divide por 10^(6+1) = 10^7
}

// Para decodificar o ID do Pacote (para Tipo 1)
int Evento::decodificarIdPacote(long long chave) 
{
    // ID do pacote está nos dígitos 7-12 (6 dígitos)
    // Primeiro, verifica se o tipo é realmente Pacote (para evitar decodificação incorreta)
    if (Evento::decodificarTipoEvento(chave) == 1) { 
        return static_cast<int>((chave / 10LL) % 1000000LL); // Pega os 6 dígitos antes do tipo
    }
    return -1; // Retorna -1 se não for evento de pacote ou ID não for válida
}

// Para decodificar Origem (para Tipo 2)
int Evento::decodificarOrigemTransporte(long long chave) 
{
    // Origem está nos dígitos 7-9 (3 dígitos)
    if (Evento::decodificarTipoEvento(chave) == 2) { // Apenas se for evento de transporte
        return static_cast<int>((chave / 10000LL) % 1000LL); // Pega os 3 dígitos antes do destino
    }
    return -1;
}

// Para decodificar Destino (para Tipo 2)
int Evento::decodificarDestinoTransporte(long long chave) 
{
    // Destino está nos dígitos 10-12 (3 dígitos)
    if (Evento::decodificarTipoEvento(chave) == 2) { // Apenas se for evento de transporte
        return static_cast<int>((chave / 10LL) % 1000LL); // Pega os 3 dígitos antes do tipo
    }
    return -1;
}
*/