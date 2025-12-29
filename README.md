
# Libreria Liste Semplici in C

**Autore:** Mattia Bittante  
**Versione:** 1.7  
**Data:** 29/12/2025  
**Linguaggio:** C (compatibile con C++)
**Compatibilità:** Windows / Linux / macOS

Una libreria semplice, didattica e completa per la gestione di **liste semplicemente concatenate** in C.  

**‼️La libreria è a solo scopo didattico e non è pensata per l'utilizzo professionale.**

---

## ❓Cos'è una lista semplice

Una lista semplicemente concatenata è una struttura dati dinamica composta da una sequenza di nodi.
ogni nodo contiene:

- un **dato** di tipo intero
- il **puntatore** al nodo successivo

>ℹ️ Ogni nodo potrebbe in realtà avere infiniti dati di qualunque tipo, per semplificare gestiamo solo nodi con un singolo dato di tipo intero.

La proprietà fondamentale delle liste semplici è quindi che **ogni nodo vede solo il nodo successivo** non il precedente.
La lista termina quando il puntatore di un nodo punta a NULL.

## 📁 Struttura del progetto

Prima di tutto scarica i file `linkedList.h` e `linkedList.c` e assicurati di posizionarli **nella stessa directory** assieme ad un altro file C (o C++) che sarà il programma che andrà ad utilizzare la libreria: in questo caso `main.c`.

```txt
/Cartella
│
├── linkedList.h      # Header della libreria
├── linkedList.c      # Implementazione
└── main.c            # Esempio di utilizzo
```

---

## 🔧 Compilazione

### Compilazione con Visual Studio Code

Per compilare programmi C in Visual Studio Code servono **due cose:**  

1. L’estensione ufficiale **C/C++ di Microsoft**  

2. Un compilatore C installato sul sistema (ad esempio `gcc`)

#### 1️⃣ Scaricare l'estensione C/C++

Apri VSC vai su **Extensions** o premi `Ctrl + Shift + X`, cerca C/C++ e scarica l'estensione ufficiale **C/C++ di Microsoft.**

#### 2️⃣ Scaricare il compilatore C

Per compilare un codice C in VSC è necessario aver installato un compilatore come `gcc` (o `g++` per compilare anche in C++). se hai già programmi come **Dev-C++** dovresti trovare già entrambi nella cartella `bin` del programma, in alternativa puoi seguire [la guida ufficiale](https://code.visualstudio.com/docs/languages/cpp) per scaricare un compilatore adatto.

Una volta che hai scaricato il compilatore, vai sul terminale di VSC e lancia:

```bash
gcc --version
g++ --version
gdb --version
```

Se tutto funziona correttamente, non ti resta che aprire la cartella del progetto su VSC, scrivere il proprio programma nel file `main.c` e poi lanciare sul terminale:

```bash
gcc main.c linkedList.c -o main.exe
.\main.exe
```

Se stai utlizzando Linux o macOS, assicurati di aggiungere -lm nella compilazione per collegare la libreria `math.h`, in questo modo:

```bash
gcc main.c linkedList.c -o main -lm
./main
```

>‼️Non compilare con il tasto Run di VSC in quanto compilerà solo il file `main.c` generando errori di linking.

### Compilazione con Dev-C++

Se usi Dev-C++, crea un progetto vuoto (`New` > `Progetto` > `Empty Project`) seleziona linguaggio e nome e salva.
A questo punto premi tasto destro sul progetto creato e seleziona `Aggiungi al Progetto` e apri i 2 file `linkedList.h` e `linkedList.c`.
Ora apri il file iniziale del progetto (solitamente `SenzaTitolo1.c`). Questo sarà il corrispondente di `main.c` , scrivi quindi il programma e premi `Compila & Esegui` o `F11` per compilare.

>ℹ️ Puoi anche eliminare il file `SenzaTitolo1.c` e aggiungere al progetto `main.c`

---

## 🔵 Esempio di main.c

```c
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
```

**Esempio output:**

```bash
originale:
[3] -> [7] -> [4] -> [8] -> [9] -> NULL
aggiunta elementi:
[3] -> [7] -> [4] -> [8] -> [9] -> [3] -> NULL
cancellazione elementi:
[3] -> [7] -> [4] -> [8] -> [3] -> NULL
lista invertita:
[3] -> [8] -> [4] -> [7] -> [3] -> NULL
lista ordinata:
[3] -> [3] -> [4] -> [7] -> [8] -> NULL
Lunghezza: 5
Somma: 25
Min: 3
Max: 8
Media: 5.00
Mediana: 4.00
```

>‼️Alcune funzione della libreria utilizzano `<limits.h>`, `<math.h>`, `<stdlib.h>`, assicurati di includerle nel tuo `main.c` per garantire l'autosufficienza del codice. Il programma compilerebbe anche senza, ma è buona pratica farlo.

---

## 📄 Documentazione delle funzioni

### Struttura del nodo

```c
// Struttura base del nodo
struct s_nodo 
{
  int dato; //dato del nodo
  struct s_nodo *next;  //puntatore al nodo successivo
};
typedef struct s_nodo nodo;
   
typedef nodo *lista;      // puntatore alla lista (alla sua testa)
typedef nodo *puntaNodo;  // puntatore a nodo specifico
```

La struttura `s_nodo` rappresenta l’elemento fondamentale della lista:
ogni nodo contiene un valore (`dato`) e un puntatore al nodo successivo (`*next`).

con `typedef struct s_nodo nodo` creo l'alias `nodo` per evitare di scrivere ogni volta `struct s_nodo`

Per leggibilità aggiungo inoltre due alias a `*nodo`:

- `lista` usato esclusivamente per indicare la testa della lista.
- `puntaNodo` usato per riferirsi a un nodo generico della lista.

>ℹ️ I due tipi sono del tutto equivalenti (puntano entrambi a nodo), ma distinguerli semanticamente rende il codice più chiaro: lista identifica la struttura nel suo insieme, mentre puntaNodo rappresenta un singolo elemento.

---

### `puntaNodo sl_creaNodo(int valore);`

Crea un nuovo nodo allocando memoria dinamicamente e gli assegna il valore specificato.

**Parametri:**

- **`int valore`**: Il dato intero da memorizzare nel nodo.

**Ritorno:**

- Il **puntatore** al nuovo nodo creato.
- **`NULL`** se non è stato possibile allocare la memoria (Heap overflow).

**Esempio di utilizzo:**

```c
puntaNodo nuovo = sl_creaNodo(5);
if (nuovo != NULL) {
    // utilizzo del nodo
}
```

**Note:**

- Il puntatore al nodo successivo (`next`) viene impostato a `NULL`.
- Questa funzione è principalmente utilizzata internamente dalle funzioni di inserimento, ma può essere usata per creare nodi isolati.

---

### `lista sl_aggiungiInTesta(lista testa, int valore);`

Crea un nuovo nodo e lo inserisce come primo elemento della lista specificata.

**Parametri:**

- **`lista testa`**: La lista a cui aggiungere il nodo.
- **`int valore`**: Il dato intero da memorizzare nel nodo.

**Ritorno:**

- Il **puntatore** alla nuova testa della lista (il nodo appena creato).
- La **testa originale** se malloc fallisce, senza apportare modifiche.

**Esempio di utilizzo:**

```c
lista nuovaLista = NULL;
nuovaLista = sl_aggiungiInTesta(nuovaLista,6);
```

**Note:**

- Il nuovo nodo diventa la testa della lista.
- `next` punta alla vecchia testa.

---

### `lista sl_aggiungiInMezzo(lista testa, int valore, int pos);`

Inserisce un nuovo nodo in una posizione specifica della lista. Se la posizione indicata supera la lunghezza della lista, il nodo viene inserito in coda.

**Parametri:**

- **`lista testa`**: La lista in cui inserire il nodo.
- **`int valore`**: Il dato intero da memorizzare nel nodo.
- **`int pos`**: L'indice (base 0) dove inserire il nodo.

**Ritorno:**

- Il **puntatore** alla testa della lista (può cambiare se `pos` è 0).
- La **testa originale** se `pos < 0` o se l'allocazione fallisce.

**Esempio di utilizzo:**

```c
miaLista = sl_aggiungiInMezzo(miaLista, 15, 2);
```

**Note:**

- Se `pos == 0`, richiama `sl_aggiungiInTesta`.
- Se `pos` è maggiore della lunghezza attuale, il nodo viene aggiunto alla fine.

---

### `lista sl_aggiungiInCoda(lista testa, int valore);`

Inserisce un nuovo nodo alla fine della lista.

**Parametri:**

- **`lista testa`**: La lista a cui aggiungere il nodo.
- **`int valore`**: Il dato intero da memorizzare nel nodo.

**Ritorno:**

- Il **puntatore** alla testa della lista.
- Se la lista era vuota, ritorna il puntatore al nuovo nodo (nuova testa).

**Esempio di utilizzo:**

```c
miaLista = sl_aggiungiInCoda(miaLista, 42);
```

---

### `lista sl_riempiRnd(lista testa, int dim, int range, int min, int div);`

Aggiunge in testa a una lista `dim` numeri casuali da `min` a `min + range`.

**Parametri:**

- **`int dim`**: Quantità di numeri da generare e aggiungere alla lista.
- **`int range`**: L'ampiezza dell'intervallo (quanti valori diversi sono possibili).
- **`int min`**: Il valore minimo possibile (il limite inferiore dell'intervallo).
- **`int div`**: Valore booleano:
  - **`1`**: Forza la generazione di numeri univoci.
  - **`0`**: Permette la generazione di numeri duplicati.

**Ritorno:**

- Il **puntatore** alla testa della lista.

**Esempio di utilizzo:**

```c
miaLista = sl_riempiRnd(miaLista, 5,10,1,1);
sl_stampaLista(miaLista);
// es. di output (5 numeri da 1 a 10 tutti diversi)
[6] -> [8] -> [2] -> [4] -> [5] -> NULL
```

**Note:**

- Se `div = 1`, la funzione utilizza `sl_datoIncluso`, il quale scorre l'intera lista, per ogni nuovo numero. Se `dim` è troppo alto i tempi di elaborazione posso diventare molto lunghi.
- per `div`, ogni valore diverso da `1` permette numeri duplicati.
- I numeri generati vengono inseriti nella lista tramite `sl_aggiungiInTesta` per questioni di ottimizzazione. (Aggiungendo in coda bisognerebbe scorrere la lista per ogni numero).
- Se non esistono abbastanza numeri univoci, vengono inseriti finché disponibili, poi vengono accettati duplicati.

---

### `int sl_intInput();`

Legge un input intero da tastiera, garantendo che il programma non vada in crash o in loop infinito se vengono inseriti caratteri non numerici.

**Funzionamento:**

- Svuota il buffer di input a ogni tentativo.
- Gestisce correttamente il segno negativo (`-`) solo se posto all'inizio.
- Richiede nuovamente l'inserimento finché non viene digitato un numero intero valido.

**Ritorno:**

- Il valore **intero** inserito dall'utente.
- **`0`**: In caso di terminazione forzata dell'input.

**Esempio di utilizzo:**

```c
int n = sl_intInput();
```

---

### `lista sl_riempiManuale(lista testa, int dim);`

Permette il popolamento di una lista tramite inserimenti manuali da parte dell'utente per un numero definito di volte.

**Parametri:**

- **`lista testa`**: La testa della lista (può essere `NULL`).
- **`int dim`**: Il numero di elementi da inserire.

**Ritorno:**

- La **nuova testa** della lista aggiornata.

**Esempio di utilizzo:**

```c
miaLista = sl_riempiManuale(miaLista, 5);
```

---

### `void sl_stampaLista(lista testa);`

Stampa a video il contenuto della lista nel formato `[dato] -> [dato] -> NULL`.

**Parametri:**

- **`lista testa`**: La lista da stampare.

**Esempio di utilizzo:**

```c
sl_stampaLista(miaLista); // Output: [10] -> [20] -> NULL
```

---

### `lista sl_delLista(lista testa);`

Elimina l'intera lista deallocando la memoria di ogni singolo nodo.

**Parametri:**

- **`lista testa`**: La lista da eliminare.

**Ritorno:**

- Sempre **`NULL`**, per indicare che la lista è ora vuota.

**Esempio di utilizzo:**

```c
miaLista = sl_delLista(miaLista);
```

**Note:**

- È fondamentale utilizzare questa funzione per prevenire memory leak prima di chiudere il programma o prima di riutilizzare il puntatore della testa per una nuova lista.

---

### `lista sl_delTesta(lista testa);`

Rimuove il primo elemento della lista.

**Parametri:**

- **`lista testa`**: La lista da cui eliminare il primo nodo.

**Ritorno:**

- Il **puntatore** alla nuova testa della lista (il vecchio secondo elemento).
- **`NULL`** se la lista conteneva un solo elemento o era già vuota.

**Esempio di utilizzo:**

```c
miaLista = sl_delTesta(miaLista);
```

---

### `lista sl_delCoda(lista testa);`

Rimuove l'ultimo elemento della lista.

**Parametri:**

- **`lista testa`**: La lista da cui eliminare l'ultimo nodo.

**Ritorno:**

- Il **puntatore** alla testa della lista.
- **`NULL`** se la lista conteneva un solo elemento che è stato eliminato.

**Esempio di utilizzo:**

```c
miaLista = sl_delCoda(miaLista);
```

---

### `lista sl_delEleLista(lista testa, int pos);`

Elimina un nodo in una posizione specifica della lista.

**Parametri:**

- **`lista testa`**: La lista da cui eliminare il nodo.
- **`int pos`**: L'indice (base 0) del nodo da rimuovere.

**Ritorno:**

- Il **puntatore** alla testa della lista aggiornata.
- La **testa originale** se `pos < 0` o se la posizione indicata è fuori dai limiti della lista.

**Esempio di utilizzo:**

```c
miaLista = sl_delEleLista(miaLista, 3);
```

**Note:**

- Se `pos == 0`, la funzione richiama internamente `sl_delTesta`.
- Se la posizione fornita è maggiore del numero di elementi presenti, la funzione non apporta alcuna modifica.

---

### `int sl_nodoIncluso(lista testa, puntaNodo A);`

Verifica se un determinato nodo appartiene alla lista specificata.

**Parametri:**

- **`lista testa`**: La lista in cui cercare.
- **`puntaNodo A`**: Il puntatore al nodo da cercare.

**Ritorno:**

- **`1`**: Se il nodo è presente nella lista.
- **`0`**: Se il nodo non è presente o la lista è vuota.

**Esempio di utilizzo:**

```c
isIncluded = sl_nodoIncluso(miaLista,A);
if(isIncluded) printf("A è presente nella lista");
```

---

### `int sl_datoIncluso(lista testa, int valore);`

Verifica se un determinato valore è presente nella lista specificata.

**Parametri:**

- **`lista testa`**: La lista in cui cercare.
- **`int valore`**: Il valore del dato da cercare.

**Ritorno:**

- **`1`**: Se il valore è già presente nella lista.
- **`0`**: Se il valore non è presente o la lista è vuota.

**Esempio di utilizzo:**

```c
isIncluded = sl_datoIncluso(miaLista,7);
if(isIncluded) printf("7 è presente nella lista");
```

---

### `int sl_isVuota(lista testa);`

Verifica se una lista è vuota.

**Parametri:**

- **`lista testa`**: la lista da verificare

**Ritorno:**

- **`1`**: Se la lista è vuota.
- **`0`**: Se la lista non è vuota.

**Esempio di utilizzo:**

```c
if(sl_isVuota(miaLista)) printf("lista vuota");
```

---

### `int sl_posizione(lista testa, int valore);`

Restituisce la posizione della prima occorrenza del valore dato.

**Parametri:**

- **`lista testa`**: la lista dove cercare.
- **`int valore`**: il numero da cercare.

**Ritorno:**

- la **posizione** del valore nella lista.
- **`-1`**: Se il valore non è presente nella lista.
- **`-2`**: Se la lista è vuota.

**Esempio di utilizzo:**

```c
int pos = sl_posizione(miaLista,3);
printf("3 è il %d della lista",pos+1);
```

---

### `void sl_swapDato(lista testa, puntaNodo A, puntaNodo B);`

Scambia i valori contenuti in due nodi della stessa lista.

**Parametri:**

- **`lista testa`**: La lista contenente i nodi.
- **`puntaNodo A`**: Puntatore al primo nodo.
- **`puntaNodo B`**: Puntatore al secondo nodo.

**Esempio di utilizzo:**

```c
sl_swapDato(miaLista,A,B);
```

**Note:**

- La funzione verifica l'effettiva appartenenza di entrambi i nodi alla lista tramite `sl_nodoIncluso` prima di procedere.

---

### `lista sl_bubbleSortLista(lista testa);`

Ordina la lista in modo crescente utilizzando l'algoritmo Bubble Sort tramite lo scambio dei dati.

**Parametri:**

- **`lista testa`**: La lista da ordinare.

**Ritorno:**

- Il **puntatore** alla testa della lista ordinata.

**Esempio di utilizzo:**

```c
listaOrdinata = sl_bubbleSortLista(listaOrdinata);
```

---

### `lista sl_mergeOrdinato(lista a, lista b);`

‼️**Funzione di supporto a `sl_mergeSortLista`.**
Fonde due sottoliste già ordinate in un'unica lista ordinata.

**Parametri:**

- **`lista a`**: Puntatore alla testa della prima sottolista ordinata.
- **`lista b`**: Puntatore alla testa della seconda sottolista ordinata.

**Ritorno:**

- Il puntatore alla testa della lista risultante dalla fusione dei nodi delle due liste originali.

---

### `lista sl_mergeSortLista(lista testa);`

Ordina la lista in modo crescente utilizzando l'algoritmo Merge Sort con complessità temporale $O(n \log n)$.

**Parametri:**

- **`lista testa`**: La lista disordinata da ordinare.

**Ritorno:**

- Il puntatore alla nuova testa della lista ordinata.

---

### `lista sl_fondiListe(lista L1, lista L2);`

Crea una nuova lista che è la concatenazione di due liste esistenti. A differenza di altre funzioni di unione, questa non modifica le liste originali ma ne crea una copia profonda.

**Parametri:**

- **`lista L1`**: La prima lista da copiare.
- **`lista L2`**: La seconda lista i cui elementi verranno aggiunti in coda alla copia di `L1`.

**Ritorno:**

- Il puntatore alla testa di una nuova lista contenente tutti gli elementi di `L1` seguiti da quelli di `L2`.
- `NULL` se entrambe le liste di partenza sono vuote.

**Esempio di utilizzo:**

```c
lista listaA = // [1, 2]
lista listaB = // [3, 4]
lista listaUnita = sl_fondiListe(listaA, listaB);
// listaA e listaB rimangono invariate. listaUnita è [1, 2, 3, 4]
```

**Note:**

- Questa funzione alloca nuova memoria per ogni singolo nodo. È responsabilità dell'utente liberare la memoria della lista restituita tramite la funzione di deallocazione dedicata.

---

### `lista sl_copiaLista(lista testa);`

Crea una copia indipendente dell'intera lista specificata, allocando nuovi nodi per ogni elemento.

**Parametri:**

- **`lista testa`**: La lista originale da duplicare.

**Ritorno:**

- Il **puntatore** alla testa della nuova lista creata.
- **`NULL`** se la lista originale è vuota o se l'allocazione di memoria fallisce.

**Esempio di utilizzo:**

```c
lista miaCopia = sl_copiaLista(listaOriginale);
```

**Note:**

- La funzione effettua una "deep copy": le modifiche ai valori o alla struttura della copia non influenzano in alcun modo la lista originale.
- Utilizza internamente la funzione `sl_aggiungiInCoda` per mantenere lo stesso ordine degli elementi.
- La memoria allocata per la copia deve essere successivamente liberata tramite `sl_delLista` per evitare memory leak.

---

### `lista sl_invertiLista(lista testa);`

Crea una nuova lista che contiene gli stessi elementi della lista originale, ma in ordine invertito.

**Parametri:**

- **`lista testa`**: La lista originale da invertire.

**Ritorno:**

- **`lista`**: Il puntatore alla testa della nuova lista invertita.
- **`NULL`**: Se la lista originale è vuota.

**Esempio di utilizzo:**

```c
lista listaSpeculare = sl_invertiLista(miaLista);
// Se miaLista era [1, 2, 3], listaSpeculare sarà [3, 2, 1]
```

**Note:**

- Questa funzione alloca nuova memoria per ogni nodo della lista risultante. Ricordarsi di liberare la memoria della lista restituita quando non più necessaria.

---

### `int sl_ripetizioni(lista testa, int valore);`

Conta quante volte un determinato valore compare nella lista.

**Parametri:**

- **`lista testa`**: La lista in cui contare.
- **`int valore`**: Il valore da cercare.

**Ritorno:**

- Il numero di occorrenze del valore.

**Esempio di utilizzo:**

```c
rip = sl_ripetizioni(miaLista,8);
printf("Nella lista 8 è ripetuto %d volte",rip);
```

---

### `int sl_modaLista(lista testa);`

Individua il valore che compare più frequentemente nella lista (Moda).

**Parametri:**

- **`lista testa`**: La lista da analizzare.

**Ritorno:**

- Il **valore** più frequente.
- **`INT_MIN`** se la lista è vuota.

**Esempio di utilizzo:**

```c
moda = sl_modaLista(miaLista);
printf("il valore più frequente nella lista è %d",moda);
```

---

### `int sl_lenLista(lista testa);`

Calcola il numero di elementi (nodi) presenti nella lista.

**Parametri:**

- **`lista testa`**: La lista da misurare.

**Ritorno:**

- Il numero intero di nodi.

**Esempio di utilizzo:**

```c
len = sl_lenLista(miaLista);
printf("la lista è composta da %d nodi",len);
```

---

### `int sl_sommaLista(lista testa);`

Calcola la somma algebrica di tutti i valori contenuti nella lista.

**Parametri:**

- **`lista testa`**: La lista su cui sommare.

**Ritorno:**

- La somma totale dei dati.

**Esempio di utilizzo:**

```c
somma = sl_sommaLista(miaLista);
printf("Il totale della lista è %d",somma);
```

---

### `int sl_maxLista(lista testa);`

Trova il valore massimo contenuto nella lista.

**Parametri:**

- **`lista testa`**: La lista da analizzare.

**Ritorno:**

- Il valore massimo.
- **`INT_MIN`** se la lista è vuota.

**Esempio di utilizzo:**

```c
max = sl_maxLista(miaLista);
printf("il valore maggiore nella lista è %d",max);
```

---

### `int sl_minLista(lista testa);`

Trova il valore minimo contenuto nella lista.

**Parametri:**

- **`lista testa`**: La lista da analizzare.

**Ritorno:**

- Il valore minimo.
- **`INT_MAX`** se la lista è vuota.

**Esempio di utilizzo:**

```c
min = sl_minLista(miaLista);
printf("il valore minore nella lista è %d",min);
```

---

### `float sl_medLista(lista testa);`

Calcola la media aritmetica dei valori nella lista.

**Parametri:**

- **`lista testa`**: La lista da analizzare.

**Ritorno:**

- Valore **`float`** della media.
- **`NAN`** se la lista è vuota.

**Esempio di utilizzo:**

```c
med = sl_medLista(miaLista);
printf("il valore medio nella lista è %.2f",med);
```

---

### `float sl_medianaLista(lista testa);`

Calcola la mediana dei valori contenuti nella lista senza alterare l'ordine degli elementi nella lista originale.

**Parametri:**

- **`lista testa`**: La lista da analizzare.

**Ritorno:**

- Il valore **mediano** (tipo `float`).
- **`NAN`** se la lista è vuota.

**Esempio di utilizzo:**

```c
float m = sl_medianaLista(miaLista);
if(!isnan(m)) printf("La mediana è: %.2f", m);
```

**Note:**

- La funzione è di tipo "non distruttivo": crea internamente una copia della lista tramite `sl_copiaLista` per poterla ordinare.
- La memoria della copia viene interamente deallocata prima della restituzione del risultato per evitare memory leak.
- Per liste con un numero pari di elementi, la mediana è calcolata come media aritmetica dei due valori centrali.
