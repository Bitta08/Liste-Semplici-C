// Mattia Bittante - 29/12/2025 - version 1.7 - italian

#include "linkedList.h"

puntaNodo sl_creaNodo(int valore)
{
  puntaNodo n = (puntaNodo)malloc(sizeof(nodo)); //cast per compatibilita con C++
  if (n == NULL) return NULL;
  n->dato=valore;
  n->next=NULL;
  return n;
}

lista sl_aggiungiInTesta(lista testa, int valore)
{
  puntaNodo n = sl_creaNodo(valore);
  if(n==NULL) return testa;
  n->next = testa;
  return n;
}

lista sl_aggiungiInMezzo(lista testa, int valore, int pos)
{
  int i;
  
  if(pos<0) return testa;
    
  if(testa == NULL) return sl_creaNodo(valore);

  if(pos == 0) return sl_aggiungiInTesta(testa,valore); 

  puntaNodo n = sl_creaNodo(valore);
  puntaNodo corrente = testa;

  for(i=0; i<pos-1 && corrente->next != NULL; i++) //verifica che pos non sia > della dimesione della lista, se lo  aggiunge in coda
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

lista sl_aggiungiInCoda(lista testa, int valore)
{
  puntaNodo n = sl_creaNodo(valore);
  if (testa == NULL) return n;

  puntaNodo corrente = testa;
  while(corrente->next != NULL)
  {
  	corrente = corrente->next;
  }
  corrente->next = n;
  return testa;
}

lista sl_riempiRnd(lista testa, int dim, int range, int min, int div)
{
    int i, r, v;
    int valoriOccupati = 0; //valori del range già presenti nella lista
    
    if (range <= 0 || dim <= 0) return testa;

    if (div == 1) 
    {
        for (v = min; v < min + range; v++) 
        {
            if (sl_datoIncluso(testa, v)) valoriOccupati++;
        }
    }

    for (i = 0; i < dim; i++) 
    {
        if (div == 1 && valoriOccupati < range) //finché c'è spazio lo genera diverso, poi lo genera con ripetizioni
        {
            do {
                r = (rand() % range) + min;
            } while (sl_datoIncluso(testa, r) == 1); 
            valoriOccupati++; 
        } 
        else r = (rand() % range) + min;
        testa = sl_aggiungiInTesta(testa, r);
    }
    return testa;
}

int sl_intInput() 
{
    int numero;
    char ch;
    int valido, negativo, contatore_cifre;

    while (1) 
    {
        numero = 0;
        valido = 1;
        negativo = 0;
        contatore_cifre = 0;

        // Legge caratteri fino a newline o EOF
        while ((ch = getchar()) != '\n' && ch != EOF) 
        {
            if (ch == '-' && contatore_cifre == 0 && negativo == 0) 
            {
                negativo = 1;
            } 
            else if (ch >= '0' && ch <= '9') 
            {
                numero = numero * 10 + (ch - '0');
                contatore_cifre++;
            } 
            else 
            {
                valido = 0; // Lettera o simbolo non valido
            }
        }

        if (valido && contatore_cifre > 0) 
        {
            if (negativo) numero = -numero;
            return numero;
        }

        printf("Errore! Inserire un numero intero valido: ");
        // Se l'errore fosse causato da EOF (chiusura improvvisa input), esco per evitare loop infiniti
        if (ch == EOF) return 0; 
    }
}

lista sl_riempiManuale(lista testa, int dim)
{
  int i;
  int input;
  for(i=0; i<dim; i++)
  {
    printf("Elemento %d: ",i+1);
    input = sl_intInput();
    testa = sl_aggiungiInCoda(testa,input);
  }

  return testa;
}

void sl_stampaLista(lista testa)
{
  puntaNodo corrente = testa;
  while(corrente != NULL)
  {
  	printf("[%d] -> ",corrente->dato);
  	corrente = corrente->next;
  }
  printf("NULL\n");
}

lista sl_delLista(lista testa)
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


lista sl_delTesta(lista testa)
{
  if(testa == NULL) return NULL;
  puntaNodo del = testa;
  testa = testa->next;
  free(del);

  return testa;
}

lista sl_delCoda(lista testa)
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

lista sl_delEleLista(lista testa, int pos)
{
  int i;
  
  if(pos<0 || testa == NULL) return testa;

  if(pos == 0) return sl_delTesta(testa); 

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

int sl_nodoIncluso(lista testa, puntaNodo A)
{
  puntaNodo corrente = testa;
  while(corrente != NULL)
  {
  	if(A == corrente) return 1;
  	corrente = corrente->next;
  }
  return 0;
}

int sl_datoIncluso(lista testa, int valore)
{
  puntaNodo corrente = testa;

  while(corrente != NULL)
  {
    if(corrente->dato==valore) return 1;
    corrente=corrente->next;
  }
  
  return 0;
}

int sl_isVuota(lista testa)
{
  if(testa == NULL) return 1;
  else return 0;
}

int sl_posizione(lista testa, int valore)
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

void sl_swapDato(lista testa, puntaNodo A, puntaNodo B)
{
  if(sl_nodoIncluso(testa,A) == 0 || sl_nodoIncluso(testa,B) == 0) return;
  int temp = 0;
  temp = A->dato;
  A->dato = B->dato;
  B->dato = temp;
}

lista sl_bubbleSortLista(lista testa)
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
        sl_swapDato(testa, corrente, corrente->next);
        scambiato = 1;
      }
      corrente = corrente->next;
    }
  }while(scambiato);

  return testa;
}

// Funzione interna di supporto per fondere due sottoliste già ordinate
lista sl_mergeOrdinato(lista a, lista b) 
{
  if (a == NULL) return b;
  if (b == NULL) return a;

  lista risultato = NULL;

  if (a->dato <= b->dato) 
  {
    risultato = a;
    risultato->next = sl_mergeOrdinato(a->next, b);
  } 
  else 
  {
    risultato = b;
    risultato->next = sl_mergeOrdinato(a, b->next);
  }
  return risultato;
}

// Funzione principale di Merge Sort
lista sl_mergeSortLista(lista testa) 
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

  return sl_mergeOrdinato(sl_mergeSortLista(testa), sl_mergeSortLista(meta));
}

lista sl_copiaLista(lista testa)
{
  lista copia = NULL;
  puntaNodo corrente = testa;
  while(corrente != NULL)
  {
    copia = sl_aggiungiInCoda(copia,corrente->dato);
    corrente = corrente->next;
  }
  return copia;
}

lista sl_fondiListe(lista L1, lista L2)
{
  if (L1 == NULL && L2 == NULL) return NULL;
  if (L1 == NULL) return sl_copiaLista(L2);
  if (L2 == NULL) return sl_copiaLista(L1);

  lista nuovaLista = sl_copiaLista(L1);
  puntaNodo corrente = L2;

  while (corrente != NULL)
  {
    nuovaLista = sl_aggiungiInCoda(nuovaLista, corrente->dato);
    corrente = corrente->next;
  }

  return nuovaLista;
}

lista sl_invertiLista(lista testa)
{
  puntaNodo corrente = testa;
  lista listaInvertita = NULL;
  
  while(corrente != NULL)
  {
    listaInvertita = sl_aggiungiInTesta(listaInvertita,corrente->dato);
    corrente = corrente->next;
  }

  return listaInvertita;
}

int sl_ripetizioni(lista testa, int valore)
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

int sl_modaLista(lista testa)
{
  if(testa == NULL) return INT_MIN;
  puntaNodo corrente = testa;
  int rip = 0;
  int maxRip = sl_ripetizioni(testa,corrente->dato);
  int valoreMax = corrente->dato;
  while(corrente != NULL)
  {
  	rip = sl_ripetizioni(testa,corrente->dato);
  	if(rip>maxRip) 
	{
	  maxRip = rip;
	  valoreMax = corrente->dato;	
	}
  	corrente=corrente->next;
  }
  return valoreMax;
}

int sl_lenLista(lista testa)
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

int sl_sommaLista(lista testa)
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

int sl_maxLista(lista testa)
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

int sl_minLista(lista testa)
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

float sl_medLista(lista testa)
{
  int somma = sl_sommaLista(testa);
  int len = sl_lenLista(testa);
  if(len == 0) return NAN;
  return(float)somma / len; 
}

float sl_medianaLista(lista testa)
{
  int i;
  float risultato;
  int len = sl_lenLista(testa);
  if(len == 0) return NAN;

  //eseguo una copia della lista per non ordinare quella originale.
  lista copia = NULL;
  copia = sl_copiaLista(testa);
  copia = sl_bubbleSortLista(copia);
  
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
  copia = sl_delLista(copia);
  return risultato;
}