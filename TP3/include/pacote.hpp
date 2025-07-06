/*#ifndef PACOTE_HPP
#define PACOTE_HPP

#include <string>

class Pacote
{
    private:
    int idPac;
    int remetente;
    int destinatario;

    public:
    Pacote();
    Pacote(int id, int rem, int dest);

    int getRem();
    int getDest();
    int getId();
    void setPacote(int id, int rem, int dest);
    //encontra o índice em que um pacote se encontra em um vetor de pacotes
    static int encontraPacote(Pacote* pacotes, int tam, int id);
};

#endif*/

#ifndef PACOTE_HPP
#define PACOTE_HPP

#include <string>

class Pacote
{
    private:
    int idPac;
    std::string remetente;
    std::string destinatario;

    public:
    Pacote();
    Pacote(int id, std::string rem, std::string dest);

    std::string getRem();
    std::string getDest();
    int getId();
    void setPacote(int id, std::string rem, std::string dest);
    //encontra o índice em que um pacote se encontra em um vetor de pacotes
    static int encontraPacote(Pacote* pacotes, int tam, int id);
};

#endif