#include <string>
#include <exception>
#include <stdexcept>
#include "pacote.hpp"

//construtor default para classe Pacote
Pacote::Pacote()
{
    idPac = -1;
    remetente = "";
    destinatario = "";
}

//construtor com parâmetros para classe Pacote
Pacote::Pacote(int id, std::string rem, std::string dest)
{
    idPac = id;
    remetente = rem;
    dest = dest;
}

//getters para a classe Pacote
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

//encontra a posição de um pacote com um certo id no vetor de pacotes da main
int Pacote::encontraPacote(Pacote* pacotes, int tam, int id)
{
    for(int i = 0; i < tam; i++)
    {
        if(pacotes[i].idPac == id)
            return i;
    }
    throw std::out_of_range("ERRO: pacote não encontrado no vetor de pacotes");
}