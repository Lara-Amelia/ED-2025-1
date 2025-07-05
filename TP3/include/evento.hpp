#ifndef EVENTO_HPP
#define EVENTO_HPP

#include <string>

//para os tipos possíveis de eventos, utilizaremos uma legenda que associa
//cada um deles a um certo número (contornar o uso de strings), sendo
/*1. RG: Pacote ainda não foi postado (apenas registrado no sistema)
    2. AR: Pacote chegou no armazém e foi armazenado na respectiva seção
    3. RM: Pacote foi removido da seção para tentativa de transporte
    4. UR: Pacote foi rearmazenado por não ser possível transportá-lo
    5. TR: Pacote sendo transportado entre armazéns
    6. EN: Pacote entregue*/

class Evento 
{
    private:
    int tempoEvento;
    int tipoEvento;
    int idPacote;
    std::string remetente;
    std::string destinatario;
    int armOrigem;
    int armDestino;
    int secaoDestino;

    public:
    //construtor default para eventos
    Evento();

    //construtor para eventos do tipo RG
    Evento(int tempo, int tipo, int idPac, std::string rem, std::string dest, int origem, int destino);

    //construtor para eventos do tipo AR, RM, UR e TR
    Evento(int tempo, int tipo, int idPac, int armDest, int secaoDest);

    //cosntrutor para eventos do tipo EN
    Evento(int tempo, int tipo, int idPac, int armDest);

    int getTempo();
    int getTipo();
    int getId();
    std::string getRemetente();
    std::string getDestinatario();
    int getOrigem();
    int getDestino(); 
    int getSecao();
    static void geraResposta(Evento* eventoResultado);
    static int defineTipo(std::string tipoEv);
    static void ordenaPorTempoId(Evento** vetor, int n);
};

#endif