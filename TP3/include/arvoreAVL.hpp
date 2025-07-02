#ifndef ARVOREAVL_HPP
#define ARVOREAVL_HPP

template <typename T>
T max_val(T a, T b);

//formato do template a usar usado pela árvore - o primeiro campo é a chave
//e o segundo campo é o objeto associado
template <typename K, typename V>

class Node 
{
    private:
    K chave;
    V valor;
    Node<K, V>* left;
    Node<K, V>* right;
    int altura; // Height of the node in the tree

    public:
    // Constructor
    Node(K k, V v);

        // Destructor
        // IMPORTANT: If V is a pointer type (e.g., PackageInfo* or ClientPackageList*),
        // you MUST delete the pointed-to object here IF this Node owns that memory.
        // For primitive types or std::string, no special deletion is needed.
        // Example for pointer values (uncomment and adapt if needed):
        // ~Node(); // Declaration only
};

template <typename K, typename V>

class arvoreAVL 
{
    private:
    Node<K, V>* root;

    int altura(Node<K, V>* node);

    void updateAltura(Node<K, V>* node);

    int getBF(Node<K, V>* node);

    //rotações
    Node<K, V>* rotacaoDir(Node<K, V>* y);
    Node<K, V>* rotacaoEsq(Node<K, V>* x);

    Node<K, V>* insereRec(Node<K, V>* node, K key, V value);

    Node<K, V>* buscaRec(Node<K, V>* node, K key) const;

    void buscaInOrder(Node<K, V>* node, V* array, int& tam) const;
    void deleteArvore(Node<K, V>* node);

    public:
    arvoreAVL();
    ~arvoreAVL();

    void insere(K key, V value);

    // Public search method: Returns a pointer to the value if found, nullptr otherwise.
    V busca(K key);
    
    //método que checa se uma estreutura com uma chave específica existe na árvore
    bool existe(K key) const;

    void inOrderTraversal(V* array, int& index) const;

    // Check if the tree is empty
    bool vazia() const;
};

#endif 