#ifndef PACOTE_HPP
#define PACOTE_HPP
#include "Listas.hpp"
#include <string>

class Pacote
{
    private: 
    int identificador;
    int horaPostagem;
    int armazemOrigem;
    int armazemDestino;
    int armazemAtual;
    int estadoAtual;
    int tempoArmazenado;
    int tempoTransporte;

    public:
    ListaEncadeada rota;
    Pacote(int id, int hora, int origem, int destino, int estado); //construtor default
    ~Pacote();
    Pacote();

    Pacote& operator=(const Pacote& outro);
    Pacote(const Pacote& outro);

    int getHora();
    int getEstado();
    int getId();
    int getArmAtual();
    int getArmDestino();
    int getArmOrigem();
    int getProximoRota();
    
    void setDados(int id, int hora, int origem, int destino, int estado);
    void setEstadoAtual(int n);
    void setArmAtual(int n);
    void setRota(ListaEncadeada rotaCalculada);
    void setId(int n);
    
    friend class Pilha;
};


#endif