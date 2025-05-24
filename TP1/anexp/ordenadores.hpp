#ifndef ORDENADORES_HPP
#define ORDENADORES_HPP
#include <cstdint>

typedef struct invencao
{
    int chave;
    //int nada3;
    //int64_t nadashort;
    //int64_t nada;
    //int64_t nada2;
}inventado;

typedef struct contador
{
  int cmp;
  int move;
  int calls;
} contador_t;

void resetcounter(contador_t &s);

void inccmp(contador_t &s, int num);

void incmove(contador_t &s, int num);

void inccalls(contador_t &s, int num);

void swap(inventado *xp, inventado *yp, contador_t &s);

void insercao(inventado v[], int tam, int r, contador_t &s);

int median (int a, int b, int c);

void partition3(inventado * A, int l, int r, int *i, int *j, contador_t &s);

void quickSort(inventado * A, int l, int r, contador_t &s, int limTamParticao);

#endif