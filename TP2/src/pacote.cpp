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

/*ListaEncadeada Pacote::getRota()
{
    return rota;
}*/

//constutor utilizado na leitura da main
Pacote::Pacote(int id, int hora, int origem, int destino, int estado)
{
    identificador = id;
    horaPostagem = hora;
    armazemOrigem = origem;
    armazemDestino = destino;
    //será inicializado após o cálculo da rota
    estadosPacote = nullptr;
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

    estadosPacote = nullptr;  // ainda não alocado, pode ser alocado depois conforme necessidade

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

/*Pacote::Pacote()
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
}*/

int Pacote::getArmDestino()
{
    return armazemDestino;
}

int Pacote::getArmOrigem()
{
    return armazemOrigem;
}

void Pacote::setArmAtual(int n)
{
    armazemAtual = n;
}

int Pacote::getArmAtual()
{
    return armazemAtual;
}

Pacote::~Pacote()
{
    //rota.Limpa();
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

int Pacote::getProximoRota()
{
    //tratamento de exceções caso a rota do pacote esteja vazia
    /*if (this->rota.getTamanho() == 0) 
    {
        std::cerr << "ERRO (Pacote " << identificador << "): Rota esta vazia. Nao ha proximo armazem." << std::endl;
        return -1; // Retorna -1 para indicar que não há próximo na rota.
    }*/
    
    Node* p = this->rota.head;
    while (p != nullptr) 
    {
        if (p->aresta == this->armazemAtual) 
        { 
            if (p->prox != nullptr) 
            {
                // Não é o último armazém, retorna o valor do próximo nó
                return p->prox->aresta;
            } 
            else 
            {
                // É o último armazém na rota (o destino final).
                // Não há mais armazéns na rota de TRÂNSITO.
                return -1; // Retorna -1 para indicar que o pacote já está no destino final.
            }
        }
        p = p->prox; // Move para o próximo nó na rota
    }  
    //substituir por tratamento de exceções depois 
    std::cerr << "ERRO (Pacote " << identificador << "): Armazem atual (" << this->armazemAtual << ") nao encontrado na rota. Inconsistencia de dados." << std::endl;
    return -1; // Retorna -1 para indicar erro. 
}

int Pacote::getEstado()
{
    return estadoAtual;
}

Pacote::Pacote(const Pacote& outro)
{
    identificador = outro.identificador;
    horaPostagem = outro.horaPostagem;
    armazemOrigem = outro.armazemOrigem;
    armazemDestino = outro.armazemDestino;
    armazemAtual = outro.armazemAtual;
    estadoAtual = outro.estadoAtual;
    estadosPacote = outro.estadosPacote;
    tempoArmazenado = outro.tempoArmazenado;
    tempoTransporte = outro.tempoTransporte;
    rota = outro.rota;  // agora funciona porque ListaEncadeada tem cópia profunda
}

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
        estadosPacote = outro.estadosPacote;
        tempoArmazenado = outro.tempoArmazenado;
        tempoTransporte = outro.tempoTransporte;
        rota = outro.rota;
    }
    return *this;
}

int Pacote::getHora()
{ 
    return horaPostagem;
}