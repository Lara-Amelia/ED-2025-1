#ifndef ARVOREAVL_HPP
#define ARVOREAVL_HPP

#include <iostream>  // para debug, se precisar
#include <string>    // para std::string, se usar
#include <exception>
#include <stdexcept>

#include "evento.hpp"

// Função auxiliar para substituir std::max
template <typename T>
T max_val(T a, T b) {
    return (a > b) ? a : b;
}

//forward declaration da classe arvoreAVL
template <typename K, typename V>
class arvoreAVL;

// Classe Node (nó da árvore AVL)
template <typename K, typename V>
class Node 
{
    private:
        K chave;
        V valor;
        Node<K, V>* left;
        Node<K, V>* right;
        int altura;

    public:
        Node(K k, V v) : chave(k), valor(v), left(nullptr), right(nullptr), altura(1) {}
        // Se precisar destrutor para V ponteiro, faça aqui
        // ~Node() { ... }
        friend class arvoreAVL<K, V>;
        friend class indicePacs;
};

// Classe da Árvore AVL
template <typename K, typename V>
class arvoreAVL 
{
    private:
        Node<K, V>* root;

        void coletaApartirDe(Node<std::string, Evento*>* node, int idPacote, int tempoLimite, Evento** resultado, int& count) 
        {
            /*if (!node) return;

            // Visita os menores
            coletaApartirDe(node->left, idPacote, tempoLimite, resultado, count);

            Evento* e = node->valor;
            //como estamos processando as linhas à medida que elas são inseridas,
            //talvez não precisemos do tempoLimite (só estarão na árvore os que tiverem inseridos até o momento)
            if (e->getId() == idPacote && e->getTempo() <= tempoLimite) 
            {
                std::cout << "id pacote em coleta a partir de "<< e->getId() << std::endl;
                resultado[count++] = e;
                std::cout << "idPacote parâmetro em coletaApartir de " << idPacote << std::endl;
            } 
            else if (e->getId() != idPacote) 
            {
                return; // terminou
            }

            // Visita os maiores
            coletaApartirDe(node->right, idPacote, tempoLimite, resultado, count);*/

            if (!node) return;

            coletaApartirDe(node->left, idPacote, tempoLimite, resultado, count);

            Evento* e = node->valor;

            if (e->getId() == idPacote /*&& e->getTempo() <= tempoLimite*/) 
            {
                resultado[count++] = e;
            }

            // independente do resultado do if, sempre continua para a direita
            coletaApartirDe(node->right, idPacote, tempoLimite, resultado, count);
        }

        int altura(Node<K, V>* node) 
        {
            return node ? node->altura : 0;
        }

        void updateAltura(Node<K, V>* node) 
        {
            if (node) 
            {
                node->altura = 1 + max_val(altura(node->left), altura(node->right));
            }
        }

        int getBF(Node<K, V>* node) 
        {
            return node ? altura(node->left) - altura(node->right) : 0;
        }

        Node<K, V>* rotacaoDir(Node<K, V>* y) 
        {
            Node<K, V>* x = y->left;
            Node<K, V>* T2 = x->right;

            x->right = y;
            y->left = T2;

            updateAltura(y);
            updateAltura(x);

            return x;
        }

        Node<K, V>* rotacaoEsq(Node<K, V>* x) 
        {
            Node<K, V>* y = x->right;
            Node<K, V>* T2 = y->left;

            y->left = x;
            x->right = T2;

            updateAltura(x);
            updateAltura(y);

            return y;
        }

        Node<K, V>* insereRec(Node<K, V>* node, K key, V value) 
        {
            if (node == nullptr) 
            {
                return new Node<K, V>(key, value);
            }

            if (key < node->chave) 
            {
                node->left = insereRec(node->left, key, value);
            }
            else if (key > node->chave) 
            {
                node->right = insereRec(node->right, key, value);
            }
            else 
            { // chave já existe, atualiza o valor
                node->valor = value;
                return node;
            }

            updateAltura(node);
            int balance = getBF(node);

            // Left Left Case
            if (balance > 1 && key < node->left->chave) 
            {
                return rotacaoDir(node);
            }

            // Right Right Case
            if (balance < -1 && key > node->right->chave) 
            {
                return rotacaoEsq(node);
            }

            // Left Right Case
            if (balance > 1 && key > node->left->chave) 
            {
                node->left = rotacaoEsq(node->left);
                return rotacaoDir(node);
            }

            // Right Left Case
            if (balance < -1 && key < node->right->chave) 
            {
                node->right = rotacaoDir(node->right);
                return rotacaoEsq(node);
            }

            return node;
        }

        Node<K, V>* buscaRec(Node<K, V>* node, K key) const 
        {
            if (node == nullptr || node->chave == key) 
            {
                return node;
            }

            if (key < node->chave) 
            {
                return buscaRec(node->left, key);
            }
            else 
            {
                return buscaRec(node->right, key);
            }
        }

        void buscaInOrder(Node<K, V>* node, V* array, int& tam) const 
        {
            if (node == nullptr) return;

            buscaInOrder(node->left, array, tam);
            array[tam++] = node->valor;
            //Evento* evento = node->valor;
            //std::cout << "VALOR ID NODE BUSCA IN ORDER: " << evento->getId() << std::endl;
            //std::cout << "VALOR TEMPO BUSCA IN ORDER: " << evento->getTempo() << std::endl;
            //std::cout << "VALOR CHAVE BUSCA IN ORDER: " << node->chave << std::endl;
            buscaInOrder(node->right, array, tam);
        }

        void deleteArvore(Node<K, V>* node) 
        {
            if(node) 
            {
                deleteArvore(node->left);
                deleteArvore(node->right);
                delete node;
            }
        }

    public:
        arvoreAVL() : root(nullptr) {}

        void coletaEventosDoPacoteAteTempo(std::string chaveInicio, int idPacote, int tempoLimite, Evento** resultado, int& count) 
        {
            if (idPacote == 0) 
            {
                // Caso especial: começa da raiz, pois os eventos podem estar espalhados
                coletaApartirDe(root, idPacote, tempoLimite, resultado, count);
            }
            else
            {
                Node<std::string, Evento*>* startNode = buscaNode(chaveInicio);
                if (!startNode) /*return*/throw std::out_of_range("ERRO: chave não encontrada no índice pacoteTempo");

                // Função auxiliar que faz inorder a partir de um nó
                //std::cout << "tempo limite em coletaeventosdopacoteatetempo " << tempoLimite << std::endl;
                coletaApartirDe(startNode, idPacote, tempoLimite, resultado, count);
            }
        }

        ~arvoreAVL() 
        {
            deleteArvore(root);
        }

        void insere(K key, V value) 
        {
            root = insereRec(root, key, value);
        }

        V busca(K key) 
        {
            Node<K, V>* node = buscaRec(root, key);
            //if (node == nullptr) throw std::runtime_error("Chave não encontrada na árvore");
            //return node->valor;
            return node ? (node->valor) : nullptr;
        }

        bool existe(K key) const 
        {
            return buscaRec(root, key) != nullptr;
        }

        Node<K, V>* buscaNode(K key) const 
        {
            return buscaRec(root, key);
        }

        void inOrderTraversal(V* array, int& index) const 
        {
            buscaInOrder(root, array, index);
        }

        bool vazia() const 
        {
            return root == nullptr;
        }

    friend class indiceCli;
    friend class infoPacotes;
    friend class indicePacs;
};

template<>
inline
int arvoreAVL<int, int>::busca(int key)
{
    Node<int, int>* node = buscaRec(root, key);
    return node ? node->valor : 0; // Retorna 0 se não encontrado
}

#endif