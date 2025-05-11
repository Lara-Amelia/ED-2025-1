#ifndef ORDENADORES_HPP
#define ORDENADORES_HPP

typedef struct contador
{
  int cmp;
  int move;
  int calls;
} contador_t;

void resetcounter(contador_t * s);

void inccmp(contador_t * s, int num);

void incmove(contador_t * s, int num);

void inccalls(contador_t * s, int num);

void swap(int *xp, int *yp, contador_t *s);

void insercao(int v[], int tam, contador_t * s);

int median (int a, int b, int c);

// quicksort partition using median of 3
void partition3(int * A, int l, int r, int *i, int *j, contador_t *s);

// quicksort with median of 3
void quickSort(int * A, int l, int r, contador_t *s);

#endif