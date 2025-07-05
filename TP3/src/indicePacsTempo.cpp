#include "indicePacTempo.hpp"
#include "evento.hpp"

//gera as chaves do índice com base em id do pacote, tempo e tipo do evento
//para resolver o problema de eventos para um mesmo pacote em um mesmo tempo, 
//utilizamos o tipo do evento como critério de "desempate"
std::string indicePacTempo:: geraChave(int idPacote, int tempo, int tipo) 
{
    std::ostringstream oss;
    oss << std::setw(3) << std::setfill('0') << idPacote;
    oss << std::setw(7) << std::setfill('0') << tempo;
    oss << tipo;
    return oss.str();
}

//gera a chave e insere um novo evento no índice
void indicePacTempo::registraEvento(int idPacote, int tempo, int tipo, Evento* evento) 
{
    std::string chave = geraChave(idPacote, tempo, tipo);
    arvPacTempo.insere(chave, evento);
}

//busca por um determinado evento no índice a partir da chave que pode ser gerada para ele
Evento* indicePacTempo::buscaEvento(int idPacote, int tempo, int tipo) 
{
    return arvPacTempo.busca(geraChave(idPacote, tempo, tipo));
}

//percorre a árvore do índice a partir de um certo nó e obtém os eventos associados
void indicePacTempo::eventosDoPacoteAteTempo(std::string chave, int idPac, int tempoLim, Evento** buffer, int& qtd)
{
    arvPacTempo.coletaEventosDoPacoteAteTempo(chave, idPac, tempoLim, buffer, qtd);   
}

//imprime infos da travessia in order no índice
void indicePacTempo::inOrderPrint(Evento** array, int& index)
{
    arvPacTempo.inOrderTraversal(array, index);
}