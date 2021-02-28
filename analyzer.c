#include "analyzer.h"

int main(int argc, string argv[]) {

  // l'analyzer viene eseguito solamente se il numero di argomenti passati è <=
  // a 4: comando, n, m ed almeno un path
  if (argc < 4) {
    printf("%s"
           "╔═════════════════════════════════════════════╗\n"
           "║ %sErrore di esecuzione, digita:%s               ║\n"
           "║ %s> bin/analyzer n m path/to/files%s            ║\n"
           "║ %sInserisci almeno un path.          n, m > 0%s ║\n"
           "╚═════════════════════════════════════════════╝%s\n",
           BOLD_RED, BOLD_NC, BOLD_RED, BOLD_NC, BOLD_RED, BOLD_NC, BOLD_RED,
           NC);
  } else {
    char input[MAXINPUT];
    int len, n;
    // controllo la validità del secondo argomento passato (n) e lo memorizzo
    if (isValidNumber(argv[1], strlen(argv[1]))) {
      n = strtol(argv[1], NULL, 10); // numero di processi P
    } else {
      do {
        printf("%s"
               "╔═════════════════════════════════════════════╗\n"
               "║ %sNumero (n) di processi P non valido%s         ║\n"
               "║ %sInserisci un nuovo numero:            n > 0%s ║\n"
               "╚═════════════════════════════════════════════╝\n"
               "%s> ",
               BOLD_RED, BOLD_NC, BOLD_RED, BOLD_NC, BOLD_RED, NC);
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';
        len = strlen(input);
        if (isValidNumber(input, len)) {
          n = strtol(input, NULL, 10);
          break;
        }
      } while (1);
    }

    // controllo la validità del terzo argomento passato (m) e lo memorizzo
    int m;
    if (isValidNumber(argv[2], strlen(argv[2]))) {
      m = strtol(argv[2], NULL, 10); // numero di processi P
    } else {
      do {
        printf("\n%s"
               "╔═════════════════════════════════════════════╗\n"
               "║ %sNumero (m) di processi Q non valido%s         ║\n"
               "║ %sInserisci un nuovo numero:            m > 0%s ║\n"
               "╚═════════════════════════════════════════════╝\n"
               "%s> ",
               BOLD_RED, BOLD_NC, BOLD_RED, BOLD_NC, BOLD_RED, NC);
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';
        len = strlen(input);
        if (isValidNumber(input, len)) {
          m = strtol(input, NULL, 10);
          break;
        }
      } while (1);
    }

    int x = argc - 3;  // memorizzo il numero di paths passati
    int p, q, f, i, j; // contatori

    printf("\n%s"
           "╔═════════════════════════════════════════════╗\n"
           "║ %sBenvenuto nell'Analyzer%s                     ║\n"
           "╚═════════════════════════════════════════════╝\n",
           YELLOW, BOLD_YELLOW, YELLOW);

    // controllo i path passati per verificarne l'esistenza, in caso il path
    // indichi una cartella procedo ad analizzarne ricorsivamente i contenuti
    FilePaths paths;
    constructor(&paths);
    for (f = 0; f < x; f++) {
      scanPath(&paths, argv[f + 3]);
    }
    x = paths.next; // numero di file presenti nei path passati

    printf("\n%s"
           "╔════════════════════════╦════════════════════╗\n"
           "║ %sFile da analizzare%s     ║ %s%-18d%s ║\n"
           "║ %sProcessi P%s             ║ %s%-18d%s ║\n"
           "║ %sProcessi Q%s             ║ %s%-18d%s ║\n"
           "╚════════════════════════╩════════════════════╝%s\n",
           YELLOW, BOLD_NC, YELLOW, BOLD_NC, x, YELLOW, BOLD_NC, YELLOW,
           BOLD_NC, n, YELLOW, BOLD_NC, YELLOW, BOLD_NC, m, YELLOW, NC);

    string filesName[x]; // array di stringhe contenente i nome dei file da
                         // analizzare
    int files[x][SIZE];  // matrice che conterrà le statistiche dei file da
                         // analizzare
    memset(files, 0, sizeof(files)); // inizializzo la matrice a 0

    if (x > 0) {
      printf("%s"
             "╔═════════════════════════════════════════════╗\n"
             "║ %sI path dei file da analizzare sono:%s         ║\n"
             "╠═════════╦═══════════════════════════════════╝%s\n",
             YELLOW, BOLD_NC, YELLOW, NC);
      for (f = 0; f < x; f++) {
        filesName[f] = paths.path[f];
        printf("%s║ %s%7d%s ║ %s%s\n", YELLOW, BOLD_NC, f, YELLOW, NC,
               filesName[f]);
      }
      printf("%s╚═════════╝%s\n", YELLOW, NC);
    } else {
      printf("%s"
             "╔═════════════════════════════════════════════╗\n"
             "║ %sI path da analizzare non contengono  %s       ║\n"
             "║ %sfile oppure non esistono. %s                  ║\n"
             "╚═════════════════════════════════════════════╝%s\n",
             YELLOW, BOLD_NC, YELLOW, BOLD_NC, YELLOW, NC);
    }

    // pipe per comunicazioni tra C e i processi P
    int pipeMatrixCP[n][2];

    // distribuisco i file ai vari processi
    int remainder =
        x % n; // il resto tra il numero di file e il numero di processi P
    int filesPerProcess[n]; // array di n int, ad ogni processo associa il
                            // numero di file da analizzare
    int fileIndex = 0;      // contatore di file assegnati

    // per ogni processo P
    for (p = 0; p < n; p++) {

      // per ogni processo generò un array di files di dimensione dei file che
      // deve analizzare calcolando il numero di processi da analizzare con il
      // resto della divisione etc ...
      filesPerProcess[p] = x / n;
      if (remainder > 0 && p < remainder) {
        filesPerProcess[p]++;
      }

      string
          filesPerProcessName[filesPerProcess[p]]; // array di stringhe che
                                                   // conterrà i nomi dei file
                                                   // che quel processo analizza
      int filesPerProcessNumber
          [filesPerProcess[p]]; // array di int che conterrà il numero
                                // identtificativo del file che quel processo
                                // analizza
      int filesPerP[filesPerProcess[p]]
                   [SIZE]; // matrice che per ogni file che il processo deve
                           // analizzare ne conterrà le statistiche
      memset(filesPerP, 0, sizeof(filesPerP)); // inizializzo la matrice

      // per ogni file che deve analizzare lo memorizzo sull'array dei file per
      // processo
      for (f = 0; f < filesPerProcess[p]; f++) {
        filesPerProcessName[f] = filesName[fileIndex]; // salvo il nome del file
        filesPerProcessNumber[f] =
            fileIndex; // salvo l'identtificativo del file
        filesPerP[f][0] =
            fileIndex; // salvo l'identtificativo del file nella matrice
        fileIndex++;   // incremento il contotore degli identtificativi dei file
      }

      // apro la pipe del processo p
      pipe(pipeMatrixCP[p]);
      // primo fork, genero n processi P
      pid_t pidP = fork();
      if (pidP == 0) { // inizio codice del processo figlio P

        close(pipeMatrixCP[p][READ]); // chiudo la parte di lettura dato che P
                                      // non riceve nulla da C

        if (filesPerProcess[p] > 0) { // se quel processo deve analizzare file
                                      // stampo delle informazioni utili
          printf("\n%s"
                 "┌─────────────────────────────────────────────┐\n"
                 "│ %sIl processo P%-14d%s                 │\n"
                 "│ %sanalizza i seguenti files:%s                  │\n"
                 "├─────────┬───────────────────────────────────┘%s\n",
                 YELLOW, BOLD_NC, p, YELLOW, BOLD_NC, YELLOW, NC);
          // per ogni file da analizzare
          for (f = 0; f < filesPerProcess[p]; f++) {
            printf("%s│ %s%7d%s │%s ", YELLOW, BOLD_NC,
                   filesPerProcessNumber[f], YELLOW, NC);
            printFilenameFromPath(filesPerProcessName[f]);
            printf("\n");
          }
          printf("%s└─────────┘%s\n", YELLOW, NC);
        } else {
          // DEBUGGING
          // codice commentato nel caso possa essere utile per mostrare il
          // funzionamento del codice
          // printf("\n"
          //        "┌─────────────────────────────────────────────┐\n"
          //        "│ Il processo P%-14d                 │\n"
          //        "│ non analizza files                          │\n"
          //        "└─────────────────────────────────────────────┘\n", p
          //       );
        }

        // pipe per comunicazioni tra P e i processi Q
        int pipeMatrixPQ[m][2];

        // creo una matrice di "split" di file, di dimensione
        // filesPerProcess[p]: numero di file che quel processo deve
        // analizzare m: numero di sottoprocessi che si divideranno i file
        SPLIT splitsMatrix[filesPerProcess[p]][m];

        // per ogni processo Q
        int q;
        for (q = 0; q < m; q++) {

          // per ogni file che quel progetto deve analiizare
          for (f = 0; f < filesPerProcess[p]; f++) {

            splitsMatrix[f][q].filename =
                filesPerProcessName[f]; // mi salvo il nome del file
            splitsMatrix[f][q].fileNumber =
                filesPerProcessNumber[f]; // e il numero

            int count = (int)fsize(
                splitsMatrix[f][q]
                    .filename); // calcolo il numero di caratteri di quel file
            int remainder = count % m; // calcolo il "resto" dei caratteri

            // calcolo le informazioni relative ad ogni split di file:
            // per ogni file, per ogni sottoprocesso, quanti caratteri, da dove
            // a dove
            int q; // contatore di processi q da usare solo in questo blocco
            for (q = 0; q < m; q++) {
              splitsMatrix[f][q].numOfChars = count / m;
              if (remainder > 0 && q < remainder) {
                splitsMatrix[f][q].numOfChars++;
              }
              if (splitsMatrix[f][q].numOfChars >
                  0) {        // se il processo ha dei caratteri da analizzare
                if (q == 0) { // il primo processo comincia dall'inizio del file
                  splitsMatrix[f][q].firstChar = 0;
                } else { // gli altri cominciano dal carattere che segue
                         // l'ultimo analizzato dal processo presente
                  splitsMatrix[f][q].firstChar =
                      splitsMatrix[f][q - 1].lastChar + 1;
                }
                splitsMatrix[f][q].lastChar = splitsMatrix[f][q].firstChar +
                                              splitsMatrix[f][q].numOfChars - 1;
              }
            }
          }

          // apro la pipe del processo q
          pipe(pipeMatrixPQ[q]);

          // genero m sottoprocessi q
          pid_t pidQ = fork();
          if (pidQ == 0) { // inizio codice del sottoprocesso figlio Q

            close(pipeMatrixPQ[q][READ]); // chiudo la parte di lettura dato che
                                          // Q non riceve nulla da P

            // per ogni file che devo analizzare ne calcolo le statistiche
            // e scrivo i valori ottenuti sulla pipe
            int split[SIZE];
            for (f = 0; f < filesPerProcess[p]; f++) {
              // passo lo splitsMatrix che contiente le informazioni,
              // e il vettore split che "ritornera" le statistiche calcolate
              // dalla funzione
              stats(splitsMatrix[f][q], split);
              write(pipeMatrixPQ[q][WRITE], split,
                    sizeof(split));
            }

            close(pipeMatrixPQ[q][WRITE]); // chiudo la parte di scrittura
            exit(0);                       // termino il sottoprocesso Q

          } else if (pidQ > 0) { // inizia il codice del processo P che gestisce i Q di sopra

            close(pipeMatrixPQ[q][WRITE]);

            // per ogni file che i Q devono analizzare ricevo le statistiche
            // nella pipe
            int receivedSplit[SIZE];
            for (f = 0; f < filesPerProcess[p]; f++) {
              read(pipeMatrixPQ[q][READ], receivedSplit, sizeof(receivedSplit));

              // per ogni split dello stesso file ne sommo le statistiche sulla
              // matrice di file filesPerP
              if (receivedSplit[0] == filesPerP[f][0]) {
                for (i = 1; i < SIZE; i++) { // i = 1 perchè il primo elemento è
                                             // l'identificativo del file
                  filesPerP[f][i] += receivedSplit[i];
                }
              }
            }

            // se il sottoprocesso è l'ultimo allora ho finito di sommare tutti
            // gli split e posso procedere a inviare le statistiche dei file
            // analizzati da quel P a C
            if (q == m - 1) {
              for (f = 0; f < filesPerProcess[p]; f++) {
                write(pipeMatrixCP[p][WRITE], filesPerP[f],
                      sizeof(filesPerP[f]));
              }
            }

            close(pipeMatrixPQ[q][READ]);
          } else {
            perror("fork failed");
            exit(-1);
          }

          // attendo l'esecuzione dei sottoprocessi Q
          for (i = 0; i < m; i++) {
            wait(NULL);
          }
        }

        close(pipeMatrixCP[p][WRITE]);
        exit(0); // termino il sottoprocesso P

      } else if(pidP > 0) { // inizia il codice del processo C che gestisce i P di sopra
        close(pipeMatrixCP[p][WRITE]);

        int receivedFile[SIZE];
        for (f = 0; f < filesPerProcess[p]; f++) {
          read(pipeMatrixCP[p][READ], receivedFile, sizeof(receivedFile));

          for (i = 0; i < x; i++) {
            if (receivedFile[0] == i) {
              for (j = 0; j < SIZE; j++) {
                files[i][j] = receivedFile[j];
              }
            }
          }
        }

        close(pipeMatrixCP[p][READ]);
      } else{
        perror("fork failed");
        exit(-1);
      }
    }

    // attendo l'esecuzione di tutti i processi P
    for (p = 0; p < n; p++) {
      wait(NULL);
    }

    // finito di lavorare coi processi c si ritova con l'arrey files pieno

    // total è l'array contenente la somma di tutte le statistiche dei file
    int total[SIZE];
    memset(total, 0, sizeof(total)); // inizializzo l'array a 0
    total[0] = x; // il primo elemento è il numero di file analizzati

    for (f = 0; f < x; f++) {
      // resoconto(files[f], 1, 1);
      // riempo l'array che conterrà la somma totale di tutti i file analizzati
      for (i = 1; i < SIZE; i++) {
        total[i] += files[f][i];
      }
    }

    int fd;
    char *myfifo = "/tmp/myfifo";
    mkfifo(myfifo, 0666);
    fd = open(myfifo, O_WRONLY);
    write(fd, &x, sizeof(x));        // invia il numero di file .txt in input
    write(fd, files, sizeof(files)); // invia il report dei singoli file
    write(fd, total, sizeof(total)); // invia il report complessivo dei file

    char txtFilesName[x][MAXFILENAME]; // vettore di stringhe contenenti i nomi
                                       // dei fil in input
    for (f = 0; f < x; f++) {
      strcpy(txtFilesName[f], paths.path[f]);
    }
    write(fd, txtFilesName, sizeof(txtFilesName)); // invio nome file

    close(fd);
  }
  return 0;
}

void constructor(FilePaths *f) {
  f->size = 50;
  f->next = 0;
  f->path = (char **)malloc(50 * sizeof(char *));
  if (f->path == NULL) {
    printf("ERR: malloc()\n");
    exit(1);
  }
}

void addPath(FilePaths *f, char *path) {
  if (f->next >= f->size) {
    f->path = (char **)realloc(f->path, (f->size + 50) * sizeof(char *));
    if (f->path == NULL) {
      printf("ERR: malloc()\n");
      exit(1);
    }
    f->size += 50;
  }
  f->path[f->next] = path;
  f->next++;
}

void scanPath(FilePaths *f, char *path) {
  FILE *fp;
  char buffer[1024];

  char find_cmd[6] = "find ";
  char opt_cmd[51] = " -type f -exec grep -Iq . {} 2>/dev/null \\; -print;";

  char *command = concat3(find_cmd, path, opt_cmd);
  char *temp;

  fp = popen(command, "r");
  if (fp == NULL) {
    printf("ERR: popen()\n");
    exit(1);
  }

  free(command);

  int valid = 0;
  while (fgets(buffer, sizeof(buffer), fp) != NULL) {
    valid++;
    temp = copyString(buffer, strlen(buffer) - 1);
    addPath(f, temp);
  }

  if (!valid) {
    printf("%s║ %sPath inesistente o non valido: \n"
           "%s║ %s> %s \n",
           BOLD_RED, BOLD_NC, BOLD_RED, NC, path);
  }
  pclose(fp);
}

string copyString(char *str, int size) {
  int x;
  char *temp = malloc(size + 1 * sizeof(char));

  if (temp == NULL) {
    printf("ERR: malloc()\n");
    exit(1);
  }

  for (x = 0; x < size; x++) {
    temp[x] = str[x];
  }
  temp[size] = '\0';

  return temp;
}

string concat3(const char *a, const char *b, const char *c) {
  size_t alen = strlen(a);
  size_t blen = strlen(b);
  size_t clen = strlen(c);
  char *res = malloc(alen + blen + clen + 1);
  if (res) {
    memcpy(res, a, alen);
    memcpy(res + alen, b, blen);
    memcpy(res + alen + blen, c, clen + 1);
  }
  return res;
}

// dato il path ad un file ne ritorna la dimensione/il numero di char
off_t fsize(string filename) {
  struct stat st;
  if (stat(filename, &st) == 0)
    return st.st_size;
  return -1;
}

// funzione che analizza un pezzo di file e ne ritorna le statistiche sul
// vettore di int passato
void stats(SPLIT split, int *array) {
  // inizializzo l'array passato a 0
  // devo farlo sempre dato che lo ritorno
  int i;
  for (i = 0; i < SIZE; i++) {
    array[i] = 0;
  }

  // se il sottoprocesso Q ha dei caratteri da analizzare di quel file
  if (split.numOfChars > 0) {

    // nel primo elemento dell'array salvo il numero del file che sto
    // analizzando
    array[0] = split.fileNumber;

    FILE *fd = fopen(split.filename, "r"); // apro il file in modalità lettura
    if (fd != NULL) {
      char c;
      fseek(fd, split.firstChar,
            SEEK_SET); // mi posizione all'inizio dello split
      int i;
      for (i = split.firstChar; i <= split.lastChar;
           i++) { // analizzo ogni carattere dello split
        c = fgetc(fd);

        // se il carattere è un carattere ASCII procedo
        if (c <= ASCII &&
            (isprint(c) || c == 10)) {
          array[ASCIIOFFSET +
                c]++; // la frequenza di quel carattere ascii viene incrementato
          array[1]++; // il contatore di caratteri ascii dello split viene
                      // incrementato
          if (isdigit(c)) {
            array[2]++;
          } else if (isalpha(c)) {
            array[3]++;
            if (islower(c)) {
              array[4]++;
            } else if (isupper(c)) {
              array[5]++;
            }
          } else if (ispunct(c)) {
            array[6]++;
          } else if (isspace(c)) {
            array[7]++;
          } else {
            array[8]++;
          }
        }
      }
      fclose(fd);

      // DEBUGGING
      // codice commentato nel caso possa essere utile per mostrare il
      // funzionamento del codice
      // stampa l'analisi dello split del sottoprocesso
      /*
      printf("\nfilenumber %d: \n", array[0]);
      for(i=0; i<COUNTERS; i++){ // stampo le informazioni di ogni contatore
        if(array[i+1] > 0){ // solo se il contatore ha contato almeno un
      carattere printf("- %d ", array[1+i]); // 1 + i perchè il primo eleemento
      è il filenumber printf("[%s] \n", aliasArray[i]);
        }
      }
      for(i=0; i<ASCII; i++){ // stampo le informazioni sui singoli caratteri
        if(array[i+ASCIIOFFSET] > 0){
         // solo se il contatore ha contato almeno un carattere
         printf(">>> %c %d\n", i , array[i+ASCIIOFFSET]);
         // 1 + i + COUNTERS, perchè il primo eleemento è il filenumber, seguito dai contatori
        }
      }
      */

    } else {
      printf("\n%sErrore nell'apertura del file: '%s'%s\n", RED, split.filename,
             NC);
    }

  } else {
    // DEBUGGING
    // printf("\nil sottoprocesso non deve analizzare nessun carattere\n");
  }
}
