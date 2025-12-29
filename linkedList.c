// Mattia Bittante - 29/12/2025 - version 1.5 - italian

#include "linkedList.h"

puntaNodo creaNodo(int valore)
{
  puntaNodo n = (puntaNodo)malloc(sizeof(nodo)); //cast per compatibilita con C++
  if (n == NULL) return NULL;
  n->dato=valore;
  n->next=NULL;
  return n;
}

lista aggiungiInTesta(lista testa, int valore)
{
  puntaNodo n = creaNodo(valore);
  if(n==NULL) return testa;
  n->next = testa;
  return n;
}

lista aggiungiInMezzo(lista testa, int valore, int pos)
{
  int i;
  
  if(pos<0) return testa;
    
  if(testa == NULL) return creaNodo(valore);

  if(pos == 0) return aggiungiInTesta(testa,valore); 

  puntaNodo n = creaNodo(valore);
  puntaNodo corrente = testa;

  for(i=0; i<pos-1 && corrente->next != NULL; i++) //verifica che pos non sia > della dimesione della lista, se lo � aggiunge in coda
  {
  	corrente = corrente->next;
  }
  
  if(corrente->next == NULL) //se pos punta alla coda (o oltre)
  {
  	corrente->next = n;
  	return testa;
  }
  n->next = corrente->next;
  corrente->next = n;
  return testa;
}

lista aggiungiInCoda(lista testa, int valore)
{
  puntaNodo n = creaNodo(valore);
  if (testa == NULL) return n;

  puntaNodo corrente = testa;
  while(corrente->next != NULL)
  {
  	corrente = corrente->next;
  }
  corrente->next = n;
  return testa;
}

lista riempiRnd(lista testa, int dim, int range, int min, int div)
{
    int i, r;
    int valoriOccupati = 0; //valori del range già presenti nella lista

    if (div == 1) 
    {
        for (int v = min; v < min + range; v++) 
        {
            if (datoIncluso(testa, v)) valoriOccupati++;
        }
    }

    for (i = 0; i < dim; i++) 
    {
        if (div == 1 && valoriOccupati < range) //finché c'è spazio lo genera diverso, poi lo genera con ripetizioni
        {
            do {
                r = (rand() % range) + min;
            } while (datoIncluso(testa, r) == 1); 
            valoriOccupati++; 
        } 
        else r = (rand() % range) + min;
        testa = aggiungiInTesta(testa, r);
    }
    return testa;
}

void stampaLista(lista testa)
{
  puntaNodo corrente = testa;
  while(corrente != NULL)
  {
  	printf("[%d] -> ",corrente->dato);
  	corrente = corrente->next;
  }
  printf("NULL\n");
}

lista delLista(lista testa)
{
    puntaNodo corrente = testa;
    while (corrente != NULL)
    {
        puntaNodo temp = corrente;
        corrente = corrente->next;
        free(temp);
    }
    return NULL;
}


lista delTesta(lista testa)
{
  if(testa == NULL) return NULL;
  puntaNodo del = testa;
  testa = testa->next;
  free(del);

  return testa;
}

lista delCoda(lista testa)
{
    if (testa == NULL) return NULL;

    if (testa->next == NULL) //un solo nodo
    {
        free(testa);
        return NULL;
    }

    puntaNodo corrente = testa;
    while (corrente->next->next != NULL)
    {
        corrente = corrente->next;
    }

    free(corrente->next);
    corrente->next = NULL;

    return testa;
}

lista delEleLista(lista testa, int pos)
{
  int i;
  
  if(pos<0 || testa == NULL) return testa;

  if(pos == 0) return delTesta(testa); 

  puntaNodo corrente = testa;

  for(i=0; i<pos-1 && corrente->next != NULL; i++) //verifica che pos non sia > della dimesione della lista, se lo è ritorna testa
  {
  	corrente = corrente->next;
  }
  
  if(corrente->next == NULL) return testa;

 puntaNodo daEliminare = corrente->next; 
 corrente->next = daEliminare->next;
 free(daEliminare);

  return testa;
}

int nodoIncluso(lista testa, puntaNodo A)
{
  puntaNodo corrente = testa;
  while(corrente != NULL)
  {
  	if(A == corrente) return 1;
  	corrente = corrente->next;
  }
  return 0;
}

int datoIncluso(lista testa, int valore)
{
  puntaNodo corrente = testa;

  while(corrente != NULL)
  {
    if(corrente->dato==valore) return 1;
    corrente=corrente->next;
  }
  
  return 0;
}

int isVuota(lista testa)
{
  if(testa == NULL) return 1;
  else return 0;
}

int posizione(lista testa, int valore)
{
  if(testa == NULL) return -2;
  puntaNodo corrente = testa;
  int pos=0;

  while(corrente != NULL)
  {
    if(corrente->dato == valore) return pos;
    corrente = corrente->next;
    pos++;
  }
  
  return -1;
}

void swapDato(lista testa, puntaNodo A, puntaNodo B)
{
  if(nodoIncluso(testa,A) == 0 || nodoIncluso(testa,B) == 0) return;
  int temp = 0;
  temp = A->dato;
  A->dato = B->dato;
  B->dato = temp;
}

lista bubbleSortLista(lista testa)
{
  if (testa == NULL) return testa;
  int scambiato;
  do 
  {
    scambiato = 0;
    puntaNodo corrente = testa;
    while (corrente->next != NULL)
    {
      if (corrente->dato > corrente->next->dato)
      {
        swapDato(testa, corrente, corrente->next);
        scambiato = 1;
      }
      corrente = corrente->next;
    }
  }while(scambiato);

  return testa;
}

// Funzione interna di supporto per fondere due sottoliste già ordinate
lista mergeOrdinato(lista a, lista b) 
{
  if (a == NULL) return b;
  if (b == NULL) return a;

  lista risultato = NULL;

  if (a->dato <= b->dato) 
  {
    risultato = a;
    risultato->next = mergeOrdinato(a->next, b);
  } 
  else 
  {
    risultato = b;
    risultato->next = mergeOrdinato(a, b->next);
  }
  return risultato;
}

// Funzione principale di Merge Sort
lista mergeSortLista(lista testa) 
{

  if (testa == NULL || testa->next == NULL) return testa;

  puntaNodo lento = testa;
  puntaNodo veloce = testa->next;

  while (veloce != NULL && veloce->next != NULL) 
  {
    lento = lento->next;
    veloce = veloce->next->next;
  }

  lista meta = lento->next;
  lento->next = NULL;

  return mergeOrdinato(mergeSortLista(testa), mergeSortLista(meta));
}

lista copiaLista(lista testa)
{
  lista copia = NULL;
  puntaNodo corrente = testa;
  while(corrente != NULL)
  {
    copia = aggiungiInCoda(copia,corrente->dato);
    corrente = corrente->next;
  }
  return copia;
}

lista fondiListe(lista L1, lista L2)
{
  if (L1 == NULL && L2 == NULL) return NULL;
  if (L1 == NULL) return copiaLista(L2);
  if (L2 == NULL) return copiaLista(L1);

  lista nuovaLista = copiaLista(L1);
  puntaNodo corrente = L2;

  while (corrente != NULL)
  {
    nuovaLista = aggiungiInCoda(nuovaLista, corrente->dato);
    corrente = corrente->next;
  }

  return nuovaLista;
}

lista invertiLista(lista testa)
{
  puntaNodo corrente = testa;
  lista listaInvertita = NULL;
  
  while(corrente != NULL)
  {
    listaInvertita = aggiungiInTesta(listaInvertita,corrente->dato);
    corrente = corrente->next;
  }

  return listaInvertita;
}

int ripetizioni(lista testa, int valore)
{
  int rip = 0;
  puntaNodo corrente = testa;
  while(corrente!=NULL)
  {
  	if(corrente->dato == valore) rip++;
  	corrente = corrente->next;
  }
  return rip;
}

int modaLista(lista testa)
{
  if(testa == NULL) return INT_MIN;
  puntaNodo corrente = testa;
  int rip = 0;
  int maxRip = ripetizioni(testa,corrente->dato);
  int valoreMax = corrente->dato;
  while(corrente != NULL)
  {
  	rip = ripetizioni(testa,corrente->dato);
  	if(rip>maxRip) 
	{
	  maxRip = rip;
	  valoreMax = corrente->dato;	
	}
  	corrente=corrente->next;
  }
  return valoreMax;
}

int lenLista(lista testa)
{
  puntaNodo corrente = testa;
  int len = 0;
  while(corrente!=NULL)
  {
  	len++;
  	corrente = corrente->next;
  }
  return len;
}

int sommaLista(lista testa)
{
  puntaNodo corrente = testa;
  int somma = 0;
  while(corrente!=NULL)
  {
  	somma += corrente->dato;
  	corrente = corrente->next;
  }
  return somma;
}

int maxLista(lista testa)
{
  if (testa == NULL) return INT_MIN;
  int max = testa->dato;
  puntaNodo corrente = testa;
  while(corrente!=NULL)
  {
  	if(corrente->dato > max) max = corrente->dato;
  	corrente = corrente->next;
  }
  return max;  
}

int minLista(lista testa)
{
  if (testa == NULL) return INT_MAX;
  int min = testa->dato;
  puntaNodo corrente = testa;
  while(corrente!=NULL)
  {
  	if(corrente->dato < min) min = corrente->dato;
  	corrente = corrente->next;
  }
  return min;  
}

float medLista(lista testa)
{
  int somma = sommaLista(testa);
  int len = lenLista(testa);
  if(len == 0) return NAN;
  return(float)somma / len; 
}

float medianaLista(lista testa)
{
  int i;
  float risultato;
  int len = lenLista(testa);
  if(len == 0) return NAN;

  //eseguo una copia della lista per non ordinare quella originale.
  lista copia = NULL;
  copia = copiaLista(testa);
  copia = bubbleSortLista(copia);
  
  puntaNodo corrente = copia;

  if(len%2==1)
  {
  	for(i=0; i<len/2; i++)
  	  corrente = corrente->next;	
	  risultato = (float)corrente->dato;
  }
  else if(len%2==0)
  {
  	for(i=0; i<(len/2)-1; i++)
  	  corrente = corrente->next;
    risultato = (float)(corrente->dato + corrente->next->dato) / 2;
  }
  copia = delLista(copia);
  return risultato;
}