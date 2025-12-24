#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include "linkedlist.h"

int main() {
    lista l = NULL;

    l = aggiungiInTesta(l, 5);
    l = aggiungiInCoda(l, 7);
    l = aggiungiInMezzo(l, 3, 1);

    stampaLista(l);

    printf("Lunghezza: %d\n", lenLista(l));
    printf("Somma: %d\n", sommaLista(l));
    printf("Min: %d\n", minLista(l));
    printf("Max: %d\n", maxLista(l));
    printf("Media: %.2f\n", medLista(l));
    printf("Mediana: %.2f\n", medianaLista(l));

    return 0;
}