#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#include "linkedList.h"

int main() {
    srand(time(NULL));
    lista l = NULL;
    
    printf("originale:\n");
    l = riempiRnd(l,5,10,1,1);
    stampaLista(l);

    printf("aggiunta elementi:\n");
    l = aggiungiInMezzo(l, 3, 5);
    stampaLista(l);
    
    printf("cancellazione elementi:\n");
    l=delEleLista(l,4);
    stampaLista(l);
    printf("lista invertita:\n");
    l = invertiLista(l);
    stampaLista(l);
    printf("lista ordinata:\n");
    l = bubbleSortLista(l);
    stampaLista(l);

    printf("Lunghezza: %d\n", lenLista(l));
    printf("Somma: %d\n", sommaLista(l));
    printf("Min: %d\n", minLista(l));
    printf("Max: %d\n", maxLista(l));
    printf("Media: %.2f\n", medLista(l));
    printf("Mediana: %.2f\n", medianaLista(l));
    return 0;
}