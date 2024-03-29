(Unfortunately only available in italian for the moment)

Progetto per il corso di Sistemi Operativi, consistente in un analizzatore di file di testo (implementato in C), che utilizza le principali funzioni di creazione e comunicazione di processi.

IMPLEMENTAZIONE

L’applicazione è compresa da 3 processi: Main, Analyzer e Report.

Il Main ha funzione di interfaccia-utente, richiama opportunamente l’Analyzer e il Report come sottoprocessi creati grazie a dei `fork()`, e ne esegue il codice tramite `execv()`.  
Il Main gestisce inoltre le modifiche “on-the-fly” dei parametri.

L’Analyzer, grazie ai processi P e Q, analizza i file e ne calcola le statistiche da comunicare al Report.  
Le comunicazioni tra il processo Analyzer e i sottoprocessi avviene grazie all’utilizzo di pipe anonime.  
Mentre la comunicazione tra l’Analyzer e il Report utilizza una fifo (named pipe).

INDICAZIONI

Makefile

- `make build`,  per effettuare la compilazione dell’applicazione.
- `make clean`,  per resettare la cartella dell’applicazione allo stato iniziale.
- `make help`, per stampare a video delle breve indicazioni per avviare l’applicazione.


Modalità “Main”

Posizionati nella directory di lavoro e digita `bin/main` per eseguire il progetto in un unico terminale con una shell interattiva.  
Segui le istruzioni a schermo per analizzare i file desiderati.


Modalità “Analyzer e Report”

Apri due terminali e posizionati nella directory di lavoro.  

In un terminale digita `bin/analyzer n m path` per avviare il processo dell'Analyzer.  

- `n`: numero di processi P;
- `m`: numero di processi Q;
- `path`:  percorso ad un file.txt o a una cartella. È possibile inserire multipli `path` divisi da uno spazio, es. `path1 path2 path3`.

Nell’altro terminale digita `bin/report` per avviare il processo del Report.
