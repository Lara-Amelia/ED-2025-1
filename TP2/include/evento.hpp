#ifndef EVENTO_HPP
#define EVENTO_HPP

#include "pacote.hpp"

class Evento 
{
    private:
        // Atributos privados que descrevem o evento
        long long chave_prioridade; // Valor numérico para ordenação no Escalonador (Heap)
        int tipo_evento;            // Identifica o tipo de evento (1: Pacote, 2: Transporte)
        int tempoInicio;                  // Instante de tempo em que o evento ocorre
        int tempoFim;
        int id_pacote;              // Identificador do pacote envolvido (se for evento de pacote)
        int armazem_origem_evento;  // Armazém de origem do evento (e.g., postagem, origem de transporte)
        int armazem_destino_evento; // Armazém de destino do evento (e.g., destino final, destino de transporte)
        
        Pacote* pacote_ptr;         // Ponteiro para o objeto Pacote real, que é afetado por este evento.
                                    // NOTA: A classe Evento NÃO é responsável por deletar Pacote* aqui.

    public:
        // Construtor: Inicializa um objeto Evento com todos os seus detalhes.
        // A chave_prioridade é construída externamente ou por funções auxiliares.
        Evento(long long chave, int tipo, int t, int id_p, int a_orig, int a_dest, Pacote* ptr);

        // Getters: Métodos const para acessar os valores dos atributos privados.
        long long getChave() const;
        int getTipoEvento() const;
        int getTempoInicio() const;
        int getTempoFim() const;
        int getIdPacote() const;
        int getArmazemOrigem() const;
        int getArmazemDestino() const;
        Pacote* getPacotePtr() const; // Retorna o ponteiro para o Pacote associado.

        void setTempoFim(int n);

        // Não é necessário um destrutor definido pelo usuário se Evento não gerencia
        // memória dinamicamente alocada (como Pacote* é um ponteiro para algo externo).
        // O destrutor default é suficiente.

        static long long construirChavePacote(int tempo, int id_pacote);

        // Função para construir a chave de prioridade para um Evento de Transporte (Tipo 2)
        static long long construirChaveTransporte(int tempo, int origem_transp, int destino_transp);

        // Funções para decodificar a chave
        static int decodificarTipoEvento(long long chave);
        static int decodificarTempoEvento(long long chave);
        static int decodificarIdPacote(long long chave); // Útil para eventos de Pacote
        static int decodificarOrigemTransporte(long long chave); // Útil para eventos de Transporte
        static int decodificarDestinoTransporte(long long chave); 
};

#endif