// avl_tree.cpp
// This file contains the implementation of the AVLTree template class methods.
//
// IMPORTANT NOTE FOR COMPILATION:
// For template classes, the compiler needs to see the full definition
// (declarations and implementations) at the point of instantiation.
// This means you will typically need to:
// 1. Include this .cpp file at the end of avl_tree.hpp:
//    #include "avl_tree.cpp"
//    OR
// 2. Explicitly instantiate the templates for all types you use in your project
//    (e.g., template class AVLTree<int, int>;) at the end of this file.
//    Option 1 is generally more flexible for template libraries.

#include "arvoreAVL.hpp" // Include the header file with declarations
#include "evento.hpp"   // Required for Evento struct if used in main/testing
//#include "package_info.hpp" // Required for PackageInfo struct if used in main/testing
//#include "custom_vector.hpp" // Required for CustomVector if used in main/testing
#include <iostream>     // For std::cout, std::endl (for testing/debugging)
#include <string>       // For std::string


// Helper function to replace std::max
template <typename T>
T max_val(T a, T b) 
{
    return (a > b) ? a : b;
}

template <typename K, typename V>
Node<K, V>::Node(K k, V v) : chave(k), valor(v), left(nullptr), right(nullptr), altura(1) {}

// --- Node Template Class Destructor ---
/*template <typename K, typename V>
Node<K, V>::~Node() 
{
    // IMPORTANT: If V is a pointer type, and this Node owns that memory,
    // you must delete the pointed-to object here.
    // This requires <type_traits> for std::is_pointer and std::remove_pointer
    // which might not be allowed in your specific C++11 environment.
    // If not, you'll need a manual mechanism in AVLTree's delete_tree or ClientPackageList's destructor.
    // For now, leaving it commented as per previous instructions.
    // if constexpr (std::is_pointer_v<V>) { // C++17 feature
    //     delete value; // Assumes Node owns the memory of V
    // }
}*/

template <typename K, typename V>
arvoreAVL<K, V>::arvoreAVL() : root(nullptr) {}

// Destructor
template <typename K, typename V>
arvoreAVL<K, V>::~arvoreAVL() 
{
    delete_tree(root);
}

template <typename K, typename V>
int arvoreAVL<K, V>::altura(Node<K, V>* node) 
{
    return node ? node->altura : 0;
}

// Helper function to update the height of a node
template <typename K, typename V>
void arvoreAVL<K, V>::updateAltura(Node<K, V>* node) 
{
    if (node) 
    {
        node->altura = 1 + max_val(altura(node->left), altura(node->right));
    }
}

// Helper function to get the balance factor of a node
template <typename K, typename V>
int arvoreAVL<K, V>::getBF(Node<K, V>* node) 
{
    return node ? altura(node->left) - altura(node->right) : 0;
}

// Right rotation
template <typename K, typename V>
Node<K, V>* arvoreAVL<K, V>::rotacaoDir(Node<K, V>* y) 
{
    Node<K, V>* x = y->left;
    Node<K, V>* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateAltura(y);
    updateAltura(x);

    return x;
}

// Left rotation
template <typename K, typename V>
Node<K, V>* arvoreAVL<K, V>::rotacaoEsq(Node<K, V>* x) 
{
    Node<K, V>* y = x->right;
    Node<K, V>* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateAltura(x);
    updateAltura(y);

    return y;
}

// Recursive Insert Helper
template <typename K, typename V>
Node<K, V>* arvoreAVL<K, V>::insereRec(Node<K, V>* node, K key, V value) 
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
    { // Key already exists, update its value
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

// Public insert method
template <typename K, typename V>
void arvoreAVL<K, V>::insere(K key, V value) 
{
    root = insereRec(root, key, value);
}

// Recursive Search Helper
template <typename K, typename V>
Node<K, V>* arvoreAVL<K, V>::buscaRec(Node<K, V>* node, K key) const 
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

// Public search method
template <typename K, typename V>
V arvoreAVL<K, V>::busca(K key) 
{
    Node<K, V>* result_node = buscaRec(root, key);
    return result_node ? &(result_node->valor) : nullptr;
}

// Public method to check if a key exists
template <typename K, typename V>
bool arvoreAVL<K, V>::existe(K key) const 
{
    return buscaRec(root, key) != nullptr;
}

// Recursive In-Order Traversal Helper
template <typename K, typename V>
void arvoreAVL<K, V>::buscaInOrder(Node<K, V>* node, V* array, int& tam) const 
{
    if (node == nullptr) 
    {
        return;
    }

    buscaInOrder(node->left, array, index);
    //armazena os resultados obtidos com a travessia em um vetor
    //esse vetor será instanciado antes da chamada e passado como argumento 
    //após percorrer a árvore, imprimiremos os dados conforme desejado
    array[index++] = node->valor;
    buscaInOrder(node->right, array, index);
}

// Public in-order traversal method
template <typename K, typename V>
void arvoreAVL<K, V>::inOrderTraversal(V* array, int& index) const 
{
    buscaInOrder(root, array, index);
}

// Recursive Post-Order Traversal for Deletion
template <typename K, typename V>
void arvoreAVL<K, V>::deleteArvore(Node<K, V>* node) 
{
    if (node) 
    {
        deleteArvore(node->left);
        deleteArvore(node->right);
        // Manual deletion of value if it's a pointer and owned by the node
        // (as discussed, this might require specific C++11 compatible type_traits
        // or a manual approach in ClientPackageList's destructor)
        delete node;
    }
}

// Check if the tree is empty
template <typename K, typename V>
bool arvoreAVL<K, V>::vazia() const 
{
    return root == nullptr;
}