
# Libreria Liste Semplici in C

**Autore:** Mattia Bittante  
**Versione:** 1.0  
**Data:** 23/12/2025  
**Linguaggio:** C (compatibile con C++)

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

Prima di tutto scarica i file `linkedlist.h` e `linkedlist.c` e assicurati di posizionarli **nella stessa directory** assieme ad un altro file C (o C++) che sarà il programma che andrà ad utilizzare la libreria: in questo caso `main.c`.

```txt
/Cartella
│
├── linkedlist.h      # Header della libreria
├── linkedlist.c      # Implementazione
└── main.c            # Esempio di utilizzo
```

---

## 🔧 Compilazione

### Compilazione con Visual Studio Code

Per compilare programmi C in Visual Studio Code servono **due cose:**  

1. L’estensione ufficiale **C/C++ di Microsoft**  

2. Un compilatore C installato sul sistema (ad esempio `gcc.exe`)

#### 1️⃣ Scaricare l'estensione C/C++

Apri VSC vai su **Extensions** o premi `Ctrl + Shift + X`, cerca C/C++ e scarica l'estensione ufficiale **C/C++ di Microsoft.**

#### 2️⃣ Scaricare il compilatore C

Per compilare un codice C in VSC è necessario aver installato un compilatore come `gcc.exe` (o `g++.exe` per compilare anche in C++). se hai già programmi come **Dev-C++** dovresti trovare già entrambi nella cartella `bin` del programma, in alternativa puoi seguire [la guida ufficiale](https://code.visualstudio.com/docs/languages/cpp) per scaricare un compilatore adatto.

Una volta che hai scaricato il compilatore, vai sul terminale di VSC e lancia:

```bash
gcc --version
g++ --version
gdb --version
```

Se tutto funziona correttamente, non ti resta che aprire la cartella del progetto su VSC, scrivere il proprio programma nel file `main.c` e poi lanciare sul terminale:

```bash
gcc main.c linkedlist.c -o main.exe
.\main.exe
```

>‼️Non compilare con il tasto Run di VSC in quanto compilerà solo il file `main.c` generando errori di linking.

### Compilazione con Dev-C++

Se usi Dev-C++, crea un progetto vuoto (`New` > `Progetto` > `Empty Project`) seleziona linguaggio e nome e salva.
A questo punto premi tasto destro sul progetto creato e seleziona `Aggiungi al Progetto` e apri i 2 file `linkedlist.h` e `linkedlist.c`.
Ora apri il file iniziale del progetto (solitamente `SenzaTitolo1.c`). Questo sarà il corrispondente di `main.c` , scrivi quindi il programma e premi `Compila & Esegui` o `F11` per compilare.

>ℹ️ Puoi anche eliminare il file `SenzaTitolo1.c` e aggiungere al progetto `main.c`

---

## 🔵 Esempio di main.c

```c
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
```

**Output atteso:**

```bash
[5] -> [3] -> [7] -> NULL
Lunghezza: 3
Somma: 15
Min: 3
Max: 7
Media: 5.00
Mediana: 5.00
```

>‼️Alcune funzione della libreria utilizzano `<limits.h>` e `<math.h>`, assicurati di includerle nel tuo `main.c` per garantire l'autosufficienza del codice. Il programma compilerebbe anche senza, ma è buona pratica farlo.

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

### `puntaNodo creaNodo(int valore);`

Crea un nuovo nodo allocando memoria dinamicamente e gli assegna il valore specificato.

**Parametri:**

- **`int valore`**: Il dato intero da memorizzare nel nodo.

**Ritorno:**

- Il **puntatore** al nuovo nodo creato.
- **`NULL`** se non è stato possibile allocare la memoria (Heap overflow).

**Esempio di utilizzo:**

```c
puntaNodo nuovo = creaNodo(5);
if (nuovo != NULL) {
    // utilizzo del nodo
}
```

**Note:**

- Il puntatore al nodo successivo (`next`) viene impostato a `NULL`.
- Questa funzione è principalmente utilizzata internamente dalle funzioni di inserimento, ma può essere usata per creare nodi isolati.

---

### `lista aggiungiInTesta(lista testa, int valore);`

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
nuovaLista = aggiungiInTesta(nuovaLista,6);
```

**Note:**

- Il nuovo nodo diventa la testa della lista.
- `next` punta alla vecchia testa.

---

### `lista aggiungiInMezzo(lista testa, int valore, int pos);`

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
miaLista = aggiungiInMezzo(miaLista, 15, 2);

```

**Note:**

- Se `pos == 0`, richiama `aggiungiInTesta`.
- Se `pos` è maggiore della lunghezza attuale, il nodo viene aggiunto alla fine.

---

### `lista aggiungiInCoda(lista testa, int valore);`

Inserisce un nuovo nodo alla fine della lista.

**Parametri:**

- **`lista testa`**: La lista a cui aggiungere il nodo.
- **`int valore`**: Il dato intero da memorizzare nel nodo.

**Ritorno:**

- Il **puntatore** alla testa della lista.
- Se la lista era vuota, ritorna il puntatore al nuovo nodo (nuova testa).

**Esempio di utilizzo:**

```c
miaLista = aggiungiInCoda(miaLista, 42);

```

---

### `void stampaLista(lista testa);`

Stampa a video il contenuto della lista nel formato `[dato] -> [dato] -> NULL`.

**Parametri:**

- **`lista testa`**: La lista da stampare.

**Esempio di utilizzo:**

```c
stampaLista(miaLista); // Output: [10] -> [20] -> NULL
```

### `lista delLista(lista testa);`

Elimina l'intera lista deallocando la memoria di ogni singolo nodo.

**Parametri:**

- **`lista testa`**: La lista da eliminare.

**Ritorno:**

- Sempre **`NULL`**, per indicare che la lista è ora vuota.

**Esempio di utilizzo:**

```c
miaLista = delLista(miaLista);
```

**Note:**

- È fondamentale utilizzare questa funzione per prevenire memory leak prima di chiudere il programma o prima di riutilizzare il puntatore della testa per una nuova lista.

---

### `lista delTesta(lista testa);`

Rimuove il primo elemento della lista.

**Parametri:**

- **`lista testa`**: La lista da cui eliminare il primo nodo.

**Ritorno:**

- Il **puntatore** alla nuova testa della lista (il vecchio secondo elemento).
- **`NULL`** se la lista conteneva un solo elemento o era già vuota.

**Esempio di utilizzo:**

```c
miaLista = delTesta(miaLista);
```

---

### `lista delCoda(lista testa);`

Rimuove l'ultimo elemento della lista.

**Parametri:**

- **`lista testa`**: La lista da cui eliminare l'ultimo nodo.

**Ritorno:**

- Il **puntatore** alla testa della lista.
- **`NULL`** se la lista conteneva un solo elemento che è stato eliminato.

**Esempio di utilizzo:**

```c
miaLista = delCoda(miaLista);
```

---

### `lista delEleLista(lista testa, int pos);`

Elimina un nodo in una posizione specifica della lista.

**Parametri:**

- **`lista testa`**: La lista da cui eliminare il nodo.
- **`int pos`**: L'indice (base 0) del nodo da rimuovere.

**Ritorno:**

- Il **puntatore** alla testa della lista aggiornata.
- La **testa originale** se `pos < 0` o se la posizione indicata è fuori dai limiti della lista.

**Esempio di utilizzo:**

```c
miaLista = delEleLista(miaLista, 3);
```

**Note:**

- Se `pos == 0`, la funzione richiama internamente `delTesta`.
- Se la posizione fornita è maggiore del numero di elementi presenti, la funzione non apporta alcuna modifica.

---

### `int incluso(lista testa, puntaNodo A);`

Verifica se un determinato nodo appartiene alla lista specificata.

**Parametri:**

- **`lista testa`**: La lista in cui cercare.
- **`puntaNodo A`**: Il puntatore al nodo da cercare.

**Ritorno:**

- **`1`**: Se il nodo è presente nella lista.
- **`0`**: Se il nodo non è presente o la lista è vuota.

**Esempio di utilizzo:**

```c
isIncluded = incluso(miaLista,A);
if(isIncluded) printf("A è presente nella lista");
```

---

### `void swapDato(lista testa, puntaNodo A, puntaNodo B);`

Scambia i valori contenuti in due nodi della stessa lista.

**Parametri:**

- **`lista testa`**: La lista contenente i nodi.
- **`puntaNodo A`**: Puntatore al primo nodo.
- **`puntaNodo B`**: Puntatore al secondo nodo.

**Esempio di utilizzo:**

```c
swapDato(miaLista,A,B);
```

**Note:**

- La funzione verifica l'effettiva appartenenza di entrambi i nodi alla lista tramite `incluso` prima di procedere.

---

### `lista bubbleSortLista(lista testa);`

Ordina la lista in modo crescente utilizzando l'algoritmo Bubble Sort tramite lo scambio dei dati.

**Parametri:**

- **`lista testa`**: La lista da ordinare.

**Ritorno:**

- Il **puntatore** alla testa della lista ordinata.

**Esempio di utilizzo:**

```c
listaOrdinata = bubbleSortLista(listaOrdinata);
```

---

### `lista copiaLista(lista testa);`

Crea una copia indipendente dell'intera lista specificata, allocando nuovi nodi per ogni elemento.

**Parametri:**

- **`lista testa`**: La lista originale da duplicare.

**Ritorno:**

- Il **puntatore** alla testa della nuova lista creata.
- **`NULL`** se la lista originale è vuota o se l'allocazione di memoria fallisce.

**Esempio di utilizzo:**

```c
lista miaCopia = copiaLista(listaOriginale);
```

**Note:**

- La funzione effettua una "deep copy": le modifiche ai valori o alla struttura della copia non influenzano in alcun modo la lista originale.
- Utilizza internamente la funzione `aggiungiInCoda` per mantenere lo stesso ordine degli elementi.
- La memoria allocata per la copia deve essere successivamente liberata tramite `delLista` per evitare memory leak.

---

### `int ripetizioni(lista testa, int valore);`

Conta quante volte un determinato valore compare nella lista.

**Parametri:**

- **`lista testa`**: La lista in cui contare.
- **`int valore`**: Il valore da cercare.

**Ritorno:**

- Il numero di occorrenze del valore.

**Esempio di utilizzo:**

```c
rip = ripetizioni(miaLista,8);
printf("Nella lista 8 è ripetuto %d volte",rip);
```

---

### `int modaLista(lista testa);`

Individua il valore che compare più frequentemente nella lista (Moda).

**Parametri:**

- **`lista testa`**: La lista da analizzare.

**Ritorno:**

- Il **valore** più frequente.
- **`INT_MIN`** se la lista è vuota.

**Esempio di utilizzo:**

```c
moda = modaLista(miaLista);
printf("il valore più frequente nella lista è %d",moda);
```

---

### `int lenLista(lista testa);`

Calcola il numero di elementi (nodi) presenti nella lista.

**Parametri:**

- **`lista testa`**: La lista da misurare.

**Ritorno:**

- Il numero intero di nodi.

**Esempio di utilizzo:**

```c
len = lenLista(miaLista);
printf("la lista è composta da %d nodi",len);
```

---

### `int sommaLista(lista testa);`

Calcola la somma algebrica di tutti i valori contenuti nella lista.

**Parametri:**

- **`lista testa`**: La lista su cui sommare.

**Ritorno:**

- La somma totale dei dati.

**Esempio di utilizzo:**

```c
somma = sommaLista(miaLista);
printf("Il totale della lista è %d",somma);
```

---

### `int maxLista(lista testa);`

Trova il valore massimo contenuto nella lista.

**Parametri:**

- **`lista testa`**: La lista da analizzare.

**Ritorno:**

- Il valore massimo.
- **`INT_MIN`** se la lista è vuota.

**Esempio di utilizzo:**

```c
max = maxLista(miaLista);
printf("il valore maggiore nella lista è %d",max);
```

---

### `int minLista(lista testa);`

Trova il valore minimo contenuto nella lista.

**Parametri:**

- **`lista testa`**: La lista da analizzare.

**Ritorno:**

- Il valore minimo.
- **`INT_MAX`** se la lista è vuota.

**Esempio di utilizzo:**

```c
min = minLista(miaLista);
printf("il valore minore nella lista è %d",min);
```

---

### `float medLista(lista testa);`

Calcola la media aritmetica dei valori nella lista.

**Parametri:**

- **`lista testa`**: La lista da analizzare.

**Ritorno:**

- Valore **`float`** della media.
- **`NAN`** se la lista è vuota.

**Esempio di utilizzo:**

```c
med = medLista(miaLista);
printf("il valore medio nella lista è %.2f",med);
```

---

### `float medianaLista(lista testa);`

Calcola la mediana dei valori contenuti nella lista senza alterare l'ordine degli elementi nella lista originale.

**Parametri:**

- **`lista testa`**: La lista da analizzare.

**Ritorno:**

- Il valore **mediano** (tipo `float`).
- **`NAN`** se la lista è vuota.

**Esempio di utilizzo:**

```c
float m = medianaLista(miaLista);
if(!isnan(m)) printf("La mediana è: %.2f", m);
```

**Note:**

- La funzione è di tipo "non distruttivo": crea internamente una copia della lista tramite `copiaLista` per poterla ordinare.
- La memoria della copia viene interamente deallocata prima della restituzione del risultato per evitare memory leak.
- Per liste con un numero pari di elementi, la mediana è calcolata come media aritmetica dei due valori centrali.
