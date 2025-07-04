#include "evento.hpp"
#include <string>
#include <exception>
#include <stdexcept>
#include <iostream>
#include <iomanip>

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

int Evento::getTempo()
{
    return tempoEvento;
}

int Evento::getTipo()
{
    return tipoEvento;
}

int Evento::getId()
{
    return idPacote;
}

std::string Evento::getRemetente()
{
    return remetente;
}
    
std::string Evento::getDestinatario()
{
    return destinatario;
}

int Evento::getOrigem()
{
    return armOrigem;
}

int Evento::getDestino()
{
    return armDestino;
}

int Evento::getSecao()
{
    return secaoDestino;
}

void Evento::geraResposta(Evento* eventoResultado)
{
    if(eventoResultado->getTipo() == 1)
    {
        std::cout << std::setfill('0') << std::setw(7) << eventoResultado->getTempo() << " EV RG " << std::setw(3) << eventoResultado->getId() <<
              " " << eventoResultado->getRemetente() << " " << eventoResultado->getDestinatario() << " " 
                  << std::setw(3) << eventoResultado->getOrigem() << " " << std::setw(3) << eventoResultado->getDestino() << std::endl;
    }
    else if(eventoResultado->getTipo() == 2)
    {
        std::cout << std::setfill('0') << std::setw(7) << eventoResultado->getTempo() << " EV AR " << std::setw(3) << eventoResultado->getId() <<
              " " << std::setw(3) << eventoResultado->getDestino() << " " << std::setw(3) << eventoResultado->getSecao() << std::endl;
    }
    else if(eventoResultado->getTipo() == 3)
    {
        std::cout << std::setfill('0') << std::setw(7) << eventoResultado->getTempo() << " EV RM " << std::setw(3) << eventoResultado->getId() <<
              " " << std::setw(3) << eventoResultado->getDestino() << " " << std::setw(3) << eventoResultado->getSecao() << std::endl;   
    }
    else if(eventoResultado->getTipo() == 4)
    {
        std::cout << std::setfill('0') << std::setw(7) << eventoResultado->getTempo() << " EV UR " << std::setw(3) << eventoResultado->getId() <<
              " " << std::setw(3) << eventoResultado->getDestino() << " " << std::setw(3) << eventoResultado->getSecao() << std::endl;
    }
    else if(eventoResultado->getTipo() == 5)
    {
        std::cout << std::setfill('0') << std::setw(7) << eventoResultado->getTempo() << " EV TR " << std::setw(3) << eventoResultado->getId() <<
              " " << std::setw(3) << eventoResultado->getOrigem() << " " << std::setw(3) << eventoResultado->getDestino() << std::endl;
    }
    else if(eventoResultado->getTipo() == 6)
    {
        std::cout << std::setfill('0') << std::setw(7) << eventoResultado->getTempo() << " EV EN " << std::setw(3) << eventoResultado->getId() <<
              " " << std::setw(3) << eventoResultado->getDestino() << std::endl;   
    }
}

int Evento::defineTipo(std::string tipoEv)
{
    int tipoEvento = -1;
    if(tipoEv == "RG")
    {
        tipoEvento = 1;
    }
    else if(tipoEv == "AR")
    {
        tipoEvento = 2;
    }
    else if(tipoEv == "RM")
    {
        tipoEvento = 3;
    }
    else if(tipoEv == "UR")
    {
        tipoEvento = 4;
    }
    else if(tipoEv == "TR")
    {
        tipoEvento = 5;
    }
    else if(tipoEv == "EN")
    {
        tipoEvento = 6;
    }
    return tipoEvento;
}

Pacote::Pacote()
{
    idPac = -1;
    remetente = "";
    destinatario = "";
}

Pacote::Pacote(int id, std::string rem, std::string dest)
{
    idPac = id;
    remetente = rem;
    dest = dest;
}

int Pacote::getId()
{
    return idPac;
}

std::string Pacote::getDest()
{
    return destinatario;
}

std::string Pacote::getRem()
{
    return remetente;
}

void Pacote::setPacote(int id, std::string rem, std::string dest)
{
    idPac = id;
    remetente = rem;
    destinatario = dest;
}

int Pacote::encontraPacote(Pacote* pacotes, int tam, int id)
{
    for(int i = 0; i < tam; i++)
    {
        if(pacotes[i].idPac == id)
            return i;
    }
    throw std::out_of_range("ERRO: pacote não encontrado no vetor de pacotes");
}

void Evento::ordenaPorTempoId(Evento** vetor, int n) 
{
    for (int i = 1; i < n; ++i) {
        Evento* key = vetor[i];
        int j = i - 1;

        int tempoKey = key->getTempo();
        int idKey = key->getId();

        while (j >= 0) {
            int tempoJ = vetor[j]->getTempo();
            int idJ = vetor[j]->getId();

            if (tempoJ > tempoKey || (tempoJ == tempoKey && idJ > idKey)) {
                vetor[j + 1] = vetor[j];
                j--;
            } else {
                break;
            }
        }

        vetor[j + 1] = key;
    }
}