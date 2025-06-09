#include "Set.hpp"
#include <string>

StringSet::StringSet(int tamanho)
{
    tamanhoOriginal = tamanho;
    tamanhoTabela = tamanho; 
    tamanhoConjunto = 0;     

    tabela = new ElementoTabela[tamanhoTabela];
    for (int i = 0; i < tamanhoTabela; ++i) 
    {
        tabela[i].dado = ""; // String vazia
        tabela[i].vazio = true; // Marca como vazio
        tabela[i].retirada = false; // Não foi removido
    }
}

StringSet::~StringSet()
{
    delete[] tabela;
}

void StringSet::Inserir(string s)
{
    if (tamanhoConjunto >= tamanhoTabela * 0.75) 
    { 
        Resize(tamanhoTabela * 2); 
    }

    int idx = Hash(s);
    int original_idx = idx; 

    do {
            if (tabela[idx].vazio || tabela[idx].retirada) 
            {
                
                tabela[idx].dado = s;
                tabela[idx].vazio = false;
                tabela[idx].retirada = false; 
                tamanhoConjunto++;
                return; 
            } 
            else if (tabela[idx].dado == s) 
            {
                
                return;
            }
            idx = (idx + 1) % tamanhoTabela; 
    } while (idx != original_idx); 
}

void StringSet::Remover(string s)
{
    int idx = Hash(s);
    int original_idx = idx;

    do {
        if (tabela[idx].vazio) 
        {    
            return;
        } 
        else if (tabela[idx].dado == s && !tabela[idx].retirada) 
        {    
            tabela[idx].retirada = true; 
            tamanhoConjunto--; 
            return; 
        }
        
        idx = (idx + 1) % tamanhoTabela; 
    } while (idx != original_idx);

    return;
}

bool StringSet::Pertence(string s)
{
    int idx = Hash(s);
    int original_idx = idx;

    do {
        if (tabela[idx].vazio) 
        {
            
            return false;
        } else if (tabela[idx].dado == s) 
        {   
            return !tabela[idx].retirada;
        }
        idx = (idx + 1) % tamanhoTabela; 
    } while (idx != original_idx); 
    return false;
}

StringSet* StringSet::Uniao(StringSet* S)
{
    StringSet* resultado = new StringSet(this->tamanhoTabela > S->tamanhoTabela ? this->tamanhoTabela : S->tamanhoTabela);

    for (int i = 0; i < this->tamanhoTabela; ++i) 
    {
        if (!this->tabela[i].vazio && !this->tabela[i].retirada) 
        {
            resultado->Inserir(this->tabela[i].dado);
        }
    }

    for (int i = 0; i < S->tamanhoTabela; ++i) 
    {
        if (!S->tabela[i].vazio && !S->tabela[i].retirada) 
        {
            resultado->Inserir(S->tabela[i].dado);
        }
    }
    return resultado; 
}

StringSet* StringSet::Intersecao(StringSet* S)
{
    StringSet* resultado = new StringSet(this->tamanhoTabela > S->tamanhoTabela ? this->tamanhoTabela : S->tamanhoTabela);
    for (int i = 0; i < this->tamanhoTabela; ++i) 
    {
        if (!this->tabela[i].vazio && !this->tabela[i].retirada) 
        {
            if (S->Pertence(this->tabela[i].dado)) 
            { 
                resultado->Inserir(this->tabela[i].dado);
            }
        }
    }
    return resultado; 
}

//união - interseção
StringSet* StringSet::DiferencaSimetrica(StringSet* S)
{
    StringSet* uniao_sets = this->Uniao(S);
    StringSet* intersecao_sets = this->Intersecao(S);
    StringSet* resultado_diferenca_simetrica = new StringSet(uniao_sets->tamanhoTabela);

    for (int i = 0; i < uniao_sets->tamanhoTabela; ++i) 
    {
        if (!uniao_sets->tabela[i].vazio && !uniao_sets->tabela[i].retirada) 
        {
            if (!intersecao_sets->Pertence(uniao_sets->tabela[i].dado)) 
            {
                resultado_diferenca_simetrica->Inserir(uniao_sets->tabela[i].dado);
            }
        }
    }
    delete uniao_sets;
    delete intersecao_sets;

    return resultado_diferenca_simetrica; 
}

void StringSet::Imprimir()
{
    std::cout << "Conteudo do Conjunto (Tamanho: " << tamanhoConjunto << ", Tabela: " << tamanhoTabela << "):" << std::endl;
    for (int i = 0; i < tamanhoTabela; ++i) {
        std::cout << "[" << i << "] ";
        if (tabela[i].vazio) {
            std::cout << "Vazio";
        } else if (tabela[i].retirada) {
            std::cout << "RETIRADO: " << tabela[i].dado;
        } else {
            std::cout << "OCUPADO: " << tabela[i].dado;
        }
        std::cout << std::endl;
    }
}

int StringSet::Hash(string s)
{
    unsigned long long hash_valor = 0;
    int peso_posicional = 1; 

    for (char caractere : s) 
    {
        unsigned long long valor_caractere = static_cast<unsigned long long>(caractere);
        hash_valor = (hash_valor + (valor_caractere * peso_posicional)) % tamanhoTabela;
        peso_posicional++; 
    }
    return static_cast<int>(hash_valor);
}

void StringSet::Rehash(int pos)
{
    
}
        
void StringSet::Resize(size_t tamanho)
{
    ElementoTabela* tabelaAntiga = tabela;
    int tamanhoAntigo = tamanhoTabela;

    tamanhoTabela = tamanho;
    tabela = new ElementoTabela[tamanhoTabela];
    tamanhoConjunto = 0; 

    for (int i = 0; i < tamanhoTabela; i++) 
    {
        tabela[i].dado = "";
        tabela[i].vazio = true;
        tabela[i].retirada = false;
    }

    for (int i = 0; i < tamanhoAntigo; ++i) 
    {
        if (!tabelaAntiga[i].vazio && !tabelaAntiga[i].retirada) 
        {
            Inserir(tabelaAntiga[i].dado);
        }
    }
    delete[] tabelaAntiga;
}