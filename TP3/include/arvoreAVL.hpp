#ifndef ARVOREAVL_HPP
#define ARVOREAVL_HPP

#include <iostream>  // para debug, se precisar
#include <string>    // para std::string, se usar

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
};

// Classe da Árvore AVL
template <typename K, typename V>
class arvoreAVL 
{
    private:
        Node<K, V>* root;

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
            return node ? (node->valor) : nullptr;
        }

        bool existe(K key) const 
        {
            return buscaRec(root, key) != nullptr;
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
};

#endif 