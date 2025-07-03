#include "indicePacTempo.hpp"
#include "evento.hpp"

std::string indicePacTempo:: geraChave(int idPacote, int tempo) 
{
    std::ostringstream oss;
    oss << std::setw(3) << std::setfill('0') << idPacote;
    oss << std::setw(7) << std::setfill('0') << tempo;
    return oss.str();
}

void indicePacTempo::registraEvento(int idPacote, int tempo, Evento* evento) 
{
    std::string chave = geraChave(idPacote, tempo);
    //std::cout << "chave em registraEvento: " << chave << std::endl;
    arvPacTempo.insere(chave, evento);
}

Evento* indicePacTempo::buscaEvento(int idPacote, int tempo) 
{
    return arvPacTempo.busca(geraChave(idPacote, tempo));
}

//talvez mudar o tipo de retorno mas, se passamos qtd por refer~encia, não será necessário - já é atualizado in place
void indicePacTempo::eventosDoPacoteAteTempo(std::string chave, int idPac, int tempoLim, Evento** buffer, int& qtd)
{
    arvPacTempo.coletaEventosDoPacoteAteTempo(chave, idPac, tempoLim, buffer, qtd);   
}