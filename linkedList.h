// Mattia Bittante - 27/12/2025 - version 1.2 - italian

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
puntaNodo creaNodo(int valore);
lista aggiungiInTesta(lista testa, int valore);
lista aggiungiInMezzo(lista testa, int valore, int pos);
lista aggiungiInCoda(lista testa, int valore);
lista riempiRnd(lista testa, int dim, int range, int min, int div);
void stampaLista(lista testa);
lista delLista(lista testa);
lista delTesta(lista testa);
lista delCoda(lista testa);
lista delEleLista(lista testa, int pos);
int nodoIncluso(lista testa, puntaNodo A);
int datoIncluso(lista testa, int valore);
void swapDato(lista testa, puntaNodo A, puntaNodo B);
lista bubbleSortLista(lista testa);
lista copiaLista(lista testa);
lista invertiLista(lista testa);
int ripetizioni(lista testa, int valore);
int modaLista(lista testa);
int lenLista(lista testa);
int sommaLista(lista testa);
int maxLista(lista testa);
int minLista(lista testa);
float medLista(lista testa);
float medianaLista(lista testa);
#endif
