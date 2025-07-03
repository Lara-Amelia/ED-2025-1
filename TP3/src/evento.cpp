#include "evento.hpp"
#include <string>

Evento::Evento()
{
    tempoEvento = -1;
    tipoEvento = -1;
    idPacote = -1;
    remetente = "";
    destinatario = "";
    armOrigem = -1;
    armDestino = -1;
    secaoDestino = -1;
}

//construtor para eventos do tipo RG (registro)
Evento::Evento(int tempo, int tipo, int idPac, std::string rem, std::string dest, int origem, int destino)
{
    tempoEvento = tempo;
    tipoEvento = tipo;
    idPacote = idPac;
    remetente = rem;
    destinatario = dest;
    armOrigem = origem;
    armDestino = destino;
}

//construtor para eventos dos tipos AR, RM, UR, TR
//se comporta diferente dependendo do tipo do evento (tinha gerado 2 construtores com a mesma assinatura)
Evento::Evento(int tempo, int tipo, int idPac, int armDest, int secaoDest)
{
    if((tipo == 2) || (tipo == 3) || (tipo == 4))
    {
        tempoEvento = tempo;
        tipoEvento = tipo;
        idPacote = idPac;
        armDestino = armDest;
        secaoDestino = secaoDest;
    }

    else if(tipo == 5)
    {
        tempoEvento = tempo;
        tipoEvento = tipo;
        idPacote = idPac;
        armOrigem = armDest;
        armDestino = secaoDest;
    }
}

//construtor para eventos do tipo EN (6)
Evento::Evento(int tempo, int tipo, int idPac, int armDest)
{
    tempoEvento = tempo;
    tipoEvento = tipo;
    idPacote = idPac;
    armDestino = armDest;
}
