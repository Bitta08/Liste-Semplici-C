// Mattia Bittante - 29/12/2025 - version 1.7 - italian

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <math.h>

// Struttura base del nodo
struct s_nodo 
{
  int dato;
  struct s_nodo *next;
};
typedef struct s_nodo nodo;
   
typedef nodo *lista;      // puntatore alla lista (alla sua testa)
typedef nodo *puntaNodo;  // puntatore a nodo specifico

// Prototipi
puntaNodo sl_creaNodo(int valore);
lista sl_aggiungiInTesta(lista testa, int valore);
lista sl_aggiungiInMezzo(lista testa, int valore, int pos);
lista sl_aggiungiInCoda(lista testa, int valore);
lista sl_riempiRnd(lista testa, int dim, int range, int min, int div);
int sl_intInput();
lista sl_riempiManuale(lista testa, int dim);
void sl_stampaLista(lista testa);
lista sl_delLista(lista testa);
lista sl_delTesta(lista testa);
lista sl_delCoda(lista testa);
lista sl_delEleLista(lista testa, int pos);
int sl_nodoIncluso(lista testa, puntaNodo A);
int sl_datoIncluso(lista testa, int valore);
int sl_isVuota(lista testa);
int sl_posizione(lista testa, int valore);
void sl_swapDato(lista testa, puntaNodo A, puntaNodo B);
lista sl_bubbleSortLista(lista testa);
lista sl_mergeOrdinato(lista a, lista b);
lista sl_mergeSortLista(lista testa);
lista sl_copiaLista(lista testa);
lista sl_fondiListe(lista L1, lista L2);
lista sl_invertiLista(lista testa);
int sl_ripetizioni(lista testa, int valore);
int sl_modaLista(lista testa);
int sl_lenLista(lista testa);
int sl_sommaLista(lista testa);
int sl_maxLista(lista testa);
int sl_minLista(lista testa);
float sl_medLista(lista testa);
float sl_medianaLista(lista testa);
#endif
