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

        //percorre a árvore a partir de um determinado nó
        void coletaApartirDe(Node<std::string, Evento*>* node, int idPacote, int tempoLimite, Evento** resultado, int& count) 
        {
            if (!node) return;

            //visita a árvore da esquerda
            coletaApartirDe(node->left, idPacote, tempoLimite, resultado, count);

            Evento* e = node->valor;

            if (e->getId() == idPacote) 
            {
                resultado[count++] = e;
            }

            //visita a árvore da direita
            coletaApartirDe(node->right, idPacote, tempoLimite, resultado, count);
        }

        //obtem a altura de um nó
        int altura(Node<K, V>* node) 
        {
            if(node == nullptr)
            {
                return 0;
            }
            else
            {
                return node->altura;
            }
        }

        //atualiza a altura de um nó
        void updateAltura(Node<K, V>* node) 
        {
            if (node) 
            {
                node->altura = 1 + max_val(altura(node->left), altura(node->right));
            }
        }

        //obtém o fator de balanceamento de um nó
        int getBF(Node<K, V>* node) 
        {
            return node ? altura(node->left) - altura(node->right) : 0;
        }

        //rotação a direita entre nós
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

        //rotação a esquerda entre nós
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

        //insere um novo nó na árvore
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
            { 
                // chave já existe, atualiza o valor
                node->valor = value;
                return node;
            }

            updateAltura(node);
            int balance = getBF(node);

            //caso esquerda esquerda
            if (balance > 1 && key < node->left->chave) 
            {
                return rotacaoDir(node);
            }

            //caso direita direita
            if (balance < -1 && key > node->right->chave) 
            {
                return rotacaoEsq(node);
            }

            //caso esquerda direita
            if (balance > 1 && key > node->left->chave) 
            {
                node->left = rotacaoEsq(node->left);
                return rotacaoDir(node);
            }

            //caso direita esquerda
            if (balance < -1 && key < node->right->chave) 
            {
                node->right = rotacaoDir(node->right);
                return rotacaoEsq(node);
            }

            return node;
        }

        //faz uma busca na árvore
        Node<K, V>* buscaRec(Node<K, V>* node, K key) const 
        {
            if (node == nullptr || node->chave == key) 
            {
                return node;
            }

            if (key < node->chave) 
            {
                //busca na árvore da esquerda
                return buscaRec(node->left, key);
            }
            else 
            {
                //busca na árvore da direita
                return buscaRec(node->right, key);
            }
        }

        //faz uma busca inOrder pela árvore
        void buscaInOrder(Node<K, V>* node, V* array, int& tam) const 
        {
            if (node == nullptr) return;

            buscaInOrder(node->left, array, tam);
            array[tam++] = node->valor;
            buscaInOrder(node->right, array, tam);
        }

        //limpa a árvore
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

        //faz a busca a partir de um certo nó
        void coletaEventosDoPacoteAteTempo(std::string chaveInicio, int idPacote, int tempoLimite, Evento** resultado, int& count) 
        {
            if (idPacote == 0) 
            {
                //caso especial: começa da raiz, pois os eventos podem estar espalhados
                coletaApartirDe(root, idPacote, tempoLimite, resultado, count);
            }
            else
            {
                Node<std::string, Evento*>* startNode = buscaNode(chaveInicio);
                if (!startNode) /*return*/throw std::out_of_range("ERRO: chave não encontrada no índice pacoteTempo");

                // Função auxiliar que faz inorder a partir de um nó
                coletaApartirDe(startNode, idPacote, tempoLimite, resultado, count);
            }
        }

        //destrutor da classe
        ~arvoreAVL() 
        {
            deleteArvore(root);
        }

        //método público para inserção na árvore
        void insere(K key, V value) 
        {
            root = insereRec(root, key, value);
        }

        //método público para busca de uma certa chave
        V busca(K key) 
        {
            Node<K, V>* node = buscaRec(root, key);
            return node ? (node->valor) : nullptr;
        }

        //checa se um evento existe na árvore ou não (retorna 1 se existe e 0 caso contrário)
        bool existe(K key) const 
        {
            return buscaRec(root, key) != nullptr;
        }

        //busca na árvore e retorna todo o item node com a chave associada
        Node<K, V>* buscaNode(K key) const 
        {
            return buscaRec(root, key);
        }

        //percorre a árvore inorder
        void inOrderTraversal(V* array, int& index) const 
        {
            buscaInOrder(root, array, index);
        }

        //checa se a árvore está vazia
        bool vazia() const 
        {
            return root == nullptr;
        }

    friend class indiceCli;
    friend class infoPacotes;
    friend class indicePacs;
};

//especialização de método para uso na árvore de tipo int, int 
template<>
inline
int arvoreAVL<int, int>::busca(int key)
{
    Node<int, int>* node = buscaRec(root, key);
    return node ? node->valor : 0; 
}

#endif