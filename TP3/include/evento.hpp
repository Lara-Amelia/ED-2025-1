#ifndef EVENTO_HPP
#define EVENTO_HPP

#include <string>

//no gerador de respostas, apenas reimprimimos o que foi recebido dos eventos na entrada - 
//armazenamos um vetor com eventos e apenas imprimimos os 
//atributos do objeto sempre que necessário/da forma requerida

//o vetor de eventos é ordenado por ordem cronológica, ou seja, pelo atributo tempoEvento

//para os tipos possíveis de eventos, utilizaremos uma legenda que associa
//cada um deles a um certo número (contornar o uso de strings)

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

    //depois eliminar construtores que façam as mesmas atribuições
    //construtor para eventos do tipo RG
    Evento(int tempo, int tipo, int idPac, std::string rem, std::string dest, int origem, int destino);
    //construtor para eventos do tipo AR, RM e UR
    Evento(int tempo, int tipo, int idPac, int armDest, int secaoDest);
    //construtor para eventos do tipo TR
    //a lista de atrobutos é a mesma, mas o signficado muda - talvez seja resolvível com a implementação
    //Evento(int tempo, int tipo, int idPac, int armOrigem, int armDest);
    //cosntrutor para eventos do tipo EN
    Evento(int tempo, int tipo, int idPac, int armDest);

};

#endif