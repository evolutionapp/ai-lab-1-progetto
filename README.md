# README #


Questa repository contiene una modifica del seguente progetto [MCA-RMCA](https://github.com/nobodyczcz/MCA-RMCA).
Per ulteriori informazioni e librerie necessarie consultare il progetto originale.


## Compilazione

### Dipendenze

Per installare le librerie necessarie alla compilazione del codice è necessario eseguire i seguenti comandi:

```
$ sudo apt-get update
$ sudo apt-get install sparsehash
$ sudo apt-get install libboost-all-dev
```

Clona questa repository.

```
$ mkdir build
$ cd build
$ cmake ../
$ make
```

## Premessa 

Il progetto MCA-RMCA offre una soluzione alternativa al problema Path-Finding e Task Assignment eseguendo le operazioni contemporaneamente. Come si può vedere dai risultati mostrati dal paper di riferimento [Integrated Task Assignment and Path Planning for Capacitated Multi-Agent Pickup and Delivery](https://arxiv.org/abs/2110.14891), questa soluzione migliora le performance rispetto gli algoritmi classici. Il nostro progetto ha come obiettivo l'analisi dei singoli problemi (Path-Finding e Task Assignment).  

## Descrizione del progetto
Il progetto prende in input:
1. una mappa contenente informazioni riguardanti gli agenti, gli ostacoli e le stazioni
2. un insieme di task (start, goal)


Restituendo in output l'assegnamento che minimizza il Total-travel-delay.
Per farlo viene utilizzato un algoritmo di tipologia A* in cui la stima del percorso minimo che un robot deve fare per svolgere un task viene eseguita ignorando la posizione e il tragitto degli altri robot. In questo modo la stima sarà sempre minore o uguale al costo richiesto realmente per trasportare il task dallo start al goal. 

## Esempi d'uso e Argomenti
Mostriamo il comando di esecuzione:
```
./MAPD -m kiva-20-500-5.map
  -a kiva-20-500-5.map
  -t 0.task 
  --capacity 1
  -o output_PP_2.txt 
```

**-m [path]** indica la mappa da caricare 

**-a [path]** indica gli agenti da caricare

**-t [path]** indica i task da caricare

**--capacity** capacità massima degli agenti

**-o** specifica il file di output


## Output 
L' output generato si presenterà nella seguente forma:
```
20  //numero di agenti
100 //numero di task
0 15 31 37 41 70 79 98 -1   //assegnamento dei task all'agente 0
1 42 50 71 88 94 99 -1  
2 14 23 40 47 58 -1
3 10 61 83 91 -1
4 7 25 48 80 89 -1
5 67 69 78 81 -1
```
Dove i primi parametri rappresentano il numero di agenti e il numero di task. 
Mentre i valori successivi mostrano l'assegnamento dei task all'agente. 
Il -1 rappresenta la fine della riga di assegnamenti ad un agente (utile per la lettura facilitata da parte del [programma di Path-Finding e Conflict resolution](https://github.com/evolutionapp/secondo-progetto-ai-definitivo)).

### Vedi anche 
[secondo-progetto-ai-definitivo](https://github.com/evolutionapp/secondo-progetto-ai-definitivo)










