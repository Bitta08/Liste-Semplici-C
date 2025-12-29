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
    l = sl_riempiRnd(l,5,10,1,1);
    sl_stampaLista(l);

    printf("aggiunta elementi:\n");
    l = sl_aggiungiInMezzo(l, 3, 5);
    sl_stampaLista(l);
    
    printf("cancellazione elementi:\n");
    l = sl_delEleLista(l,4);
    sl_stampaLista(l);
    printf("lista invertita:\n");
    l = sl_invertiLista(l);
    sl_stampaLista(l);
    printf("lista ordinata:\n");
    l = sl_bubbleSortLista(l);
    sl_stampaLista(l);

    printf("Lunghezza: %d\n", sl_lenLista(l));
    printf("Somma: %d\n", sl_sommaLista(l));
    printf("Min: %d\n", sl_minLista(l));
    printf("Max: %d\n", sl_maxLista(l));
    printf("Media: %.2f\n", sl_medLista(l));
    printf("Mediana: %.2f\n", sl_medianaLista(l));
    return 0;
}