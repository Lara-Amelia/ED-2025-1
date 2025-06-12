#include "evento.hpp" // Inclui o cabeçalho da própria classe
#include "pacote.hpp"
//TODOS OS PRINTS DEVEM SER RELIZADOS NA CLASSE EVENTO

// Implementação do construtor de Evento (permanece o mesmo)
Evento::Evento(long long chave, int tipo, int t, int id_p, int a_orig, int a_dest, Pacote* ptr) :
    chave_prioridade(chave),
    tipo_evento(tipo),
    tempoInicio(t),
    id_pacote(id_p),
    armazem_origem_evento(a_orig),
    armazem_destino_evento(a_dest),
    pacote_ptr(ptr)
{
    
}

void Evento::setTempoFim(int n)
{
    tempoFim = n;
}

// Implementações dos métodos Getters (permanecem os mesmos)
long long Evento::getChave() const 
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
