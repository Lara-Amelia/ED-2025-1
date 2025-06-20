#ifndef EVENTO_HPP
#define EVENTO_HPP

#include "pacote.hpp"

class Evento 
{
    private:
        std::string chavePrioridade;//chave numérico para ordenação no Escalonador (Heap)
        int tipoEvento;             //identifica o tipo de evento (1: Pacote, 2: Transporte)
        int tempoInicio;            //instante de tempo em que o evento ocorre
        int idPacote;               //identificador do pacote envolvido (se for evento de pacote)
        int armazemOrigemEvento;    //armazém de origem do evento (postagem, origem de transporte)
        int armazemDestinoEvento;   //armazém de destino do evento (destino final, destino de transporte)
        Pacote* pacotePtr;         //ponteiro para o objeto Pacote real que é afetado pelo evento

    public:
        //construtores
        Evento(std::string chave, int tipo, int t, int idPacote, int aOrig, int aDest, Pacote* ptr);
        Evento& operator=(const Evento& other);
        Evento(const Evento& other); 
        Evento();

        //getters
        std::string getChave() const;
        int getTipoEvento() const;
        int getTempoInicio() const;
        int getIdPacote() const;
        int getArmazemOrigem() const;
        int getArmazemDestino() const;
        Pacote* getPacotePtr() const; 

        //setters
        void setEvento(const std::string& chave, int tipo, int subtipo, int tInicio, int idPacote, int aOrig, int aDest, Pacote* pacote);

        //métodos que lidam com a construção e extração de informações da chave
        static std::string construirChavePacote(int tempo, int id_pacote);
        static std::string construirChaveTransporte(int tempo, int origem_transp, int destino_transp);
        static int decodificarTipoEvento(std::string chave);
        static int decodificarTempoEvento(std::string chave);
        static int decodificarIdPacote(std::string chave); 
        static int decodificarOrigemTransporte(std::string chave); 
        static int decodificarDestinoTransporte(std::string chave); 
};

#endif