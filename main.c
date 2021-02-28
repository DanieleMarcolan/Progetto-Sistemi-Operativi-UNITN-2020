#include "main.h"

int main(int argc, string argv[]) {
  int len;

  // memorizzo da input il valore n di processi P, controllandone la validità
  char n[MAXINPUT];
  printf("\n%s"
         "╔═════════════════════════════════════════════╗\n"
         "║ %sBenvenuto nel Main%s                          ║\n"
         "╠═════════════════════════════════════════════╣\n"
         "║ %sInserisci il numero (n) di processi P%s       ║\n"
         "║ %sdesiderati:                           n > 0%s ║\n"
         "╚═════════════════════════════════════════════╝%s\n"
         "> ",
         CYAN, BOLD_CYAN, CYAN, BOLD_NC, CYAN, BOLD_NC, CYAN, NC);
  do {
    fgets(n, sizeof(n), stdin);
    n[strcspn(n, "\n")] = '\0';
    len = strlen(n);
    if (!isValidNumber(n, len)) {
      printf("%s"
             "╔═════════════════════════════════════════════╗\n"
             "║ %sValore non riconosciuto.%s                    ║\n"
             "║ %sInserisci un nuovo numero:%s                  ║\n"
             "╚═════════════════════════════════════════════╝\n"
             "%s> ",
             BOLD_RED, BOLD_NC, BOLD_RED, BOLD_NC, BOLD_RED, NC);
    } else {
      break;
    }
  } while (1);

  // memorizzo da input il valore m di processi Q, controllandone la validità
  char m[MAXINPUT];
  printf("\n%s"
         "╔═════════════════════════════════════════════╗\n"
         "║ %sInserisci il numero (m) di processi Q%s       ║\n"
         "║ %sdesiderati:                           m > 0%s ║\n"
         "╚═════════════════════════════════════════════╝\n"
         "%s> ",
         CYAN, BOLD_NC, CYAN, BOLD_NC, CYAN, NC);
  do {
    fgets(m, sizeof(m), stdin);
    m[strcspn(m, "\n")] = '\0';
    len = strlen(m);
    if (!isValidNumber(m, len)) {
      printf("%s"
             "╔═════════════════════════════════════════════╗\n"
             "║ %sValore non riconosciuto.%s                    ║\n"
             "║ %sInserisci un nuovo numero:%s                  ║\n"
             "╚═════════════════════════════════════════════╝\n"
             "%s> ",
             BOLD_RED, BOLD_NC, BOLD_RED, BOLD_NC, BOLD_RED, NC);
    } else {
      break;
    }
  } while (1);

  // memorizzo da input una serie di path ai file e cartelle da analizzare
  // controllo che venga passato almeno un path,
  // fornisco un esempio di utilizzo tramite 'help'
  // termino l'input e procedo ad analizzare i files tramite 'end'
  // i path sono salvati in un array di stringhe 'files',
  // sono ammessi fino a 1024 paths in input
  string files[MAXPATHS];
  char file[MAXINPUT];
  int i = 0;
  printf("\n%s"
         "╔═════════════════════════════════════════════╗\n"
         "║ %sInserisci i path dei file e delle cartelle%s  ║\n"
         "║ %sda analizzare.%s                              ║\n"
         "║ %sVai a capo dopo ogni path.%s                  ║\n"
         "║ %sDigita 'end' per terminare.%s                 ║\n"
         "║ %sDigita 'help' per un esempio.%s               ║\n"
         "╚═════════════════════════════════════════════╝\n"
         "%s> ",
         CYAN, BOLD_NC, CYAN, BOLD_NC, CYAN, BOLD_NC, CYAN, BOLD_NC, CYAN,
         BOLD_NC, CYAN, NC);
  do {
    fgets(file, sizeof(file), stdin);
    file[strcspn(file, "\n")] = '\0';
    if (!strcmp(file, "end")) {
      if (i == 0) {
        printf("%s"
               "╔═════════════════════════════════════════════╗\n"
               "║ %sInserisci almeno un path.%s                   ║\n"
               "╚═════════════════════════════════════════════╝\n"
               "%s> ",
               BOLD_RED, BOLD_NC, BOLD_RED, NC);
      } else {
        break;
      }
    } else if (!strcmp(file, "help")) {
      printf("\n%s"
             "╔═════════════════════════════════════════════╗\n"
             "║ %s> filename%s                                  ║\n"
             "║ %s> filename.txt%s                              ║\n"
             "║ %s> path/to/filename.txt%s                      ║\n"
             "║ %s> \"file name with spaces.txt\"%s               ║\n"
             "║                                             ║\n"
             "║ %s> foldername%s                                ║\n"
             "║ %s> path/to/foldername%s                        ║\n"
             "║                                             ║\n"
             "║ %s> end%s                                       ║\n"
             "╠═════════════════════════════════════════════╣\n"
             "║ %sInserisci i path dei file da analizzare.%s    ║\n"
             "╚═════════════════════════════════════════════╝\n"
             "%s> ",
             CYAN, BOLD_NC, CYAN, BOLD_NC, CYAN, BOLD_NC, CYAN, BOLD_NC, CYAN,
             BOLD_NC, CYAN, BOLD_NC, CYAN, BOLD_NC, CYAN, BOLD_NC, CYAN, NC);
    } else {
      files[i] = malloc(strlen(file) + 1);
      if(files[i]==NULL){
        printf("Errore allocazione memoria\n");
        return 2;
      }
      strcpy(files[i], file);
      i++;
      printf("> ");
    }
  } while (1);
  nl();

  // procedo a chiamare l'analyzer e il report passandogli un array di stringhe
  // 'pargv' contenente
  // n nella posizione 1
  // m nella posizione 2
  // i path passati nelle posizioni a seguire
  // 'parc' è il contatore di eleementi dell'array 'parv'
  int j;
  int parc = i + 2;
  string parv[MAXPATHS + 2]; // il massimo numero di argomenti passati

  parv[0] = "bin/main";

  parv[1] = malloc(strlen(n) + 1);
  if(parv[1]==NULL){
    printf("Errore allocazione memoria\n");
    return 2;
  }
  strcpy(parv[1], n);

  parv[2] = malloc(strlen(m) + 1);
  if(parv[2]==NULL){
    printf("Errore allocazione memoria\n");
    return 2;
  }
  strcpy(parv[2], m);

  // copio ogni path
  for (j = 3; j <= parc; j++) {
    parv[j] = malloc(strlen(files[j - 3]) + 1);
    if(parv[j]==NULL){
      printf("Errore allocazione memoria\n");
      return 2;
    }
    strcpy(parv[j], files[j - 3]);
  }

  // richiamo la funzione che richiamerà a sua volta l'analyzer e il report
  mainFunction(parc, parv);

  // al termine dell'esecuzione del report e dell'analyzer mostro all'utente
  // una shell interattiva per le modifiche on-the fly dei parametri
  char input[MAXINPUT];
  do {
    printf("\n\n%s"
           "╔═════════════════════════════════════════════╗\n"
           "║ %sParametri attuali%s                           ║\n"
           "╠════════════════════════╦════════════════════╣\n"
           "║ %sPaths da analizzare%s    ║ %s%-18d%s ║\n"
           "║ %sProcessi P%s             ║ %s%-18s%s ║\n"
           "║ %sProcessi Q%s             ║ %s%-18s%s ║\n"
           "╠════════════════════════╩════════════════════╣\n"
           "║ %sDigita%s                                      ║\n"
           "╠═══╦═════════════════════════════════════════╣\n"
           "║ %s1%s ║ %sModifica il numero di processi P%s        ║\n"
           "║ %s2%s ║ %sModifica il numero di processi Q%s        ║\n"
           "║ %s3%s ║ %sAggiungi path da analizzare%s             ║\n"
           "║ %s4%s ║ %sRimuovi path%s                            ║\n"
           "║ %s5%s ║ %sVisualizza i path da analizzare%s         ║\n"
           "║ %s6%s ║ %sEsegui con i parametri attuali%s          ║\n"
           "║ %s7%s ║ %sEsegui un nuovo Main%s                    ║\n"
           "╠═══╬═════════════════════════════════════════╣\n"
           "║ %s0%s ║ %sEsci%s                                    ║\n"
           "╚═══╩═════════════════════════════════════════╝\n"
           "%s> ",
           CYAN, BOLD_CYAN, CYAN, BOLD_NC, CYAN, BOLD_NC, parc - 2, CYAN,
           BOLD_NC, CYAN, BOLD_NC, parv[1], CYAN, BOLD_NC, CYAN, BOLD_NC,
           parv[2], CYAN, BOLD_CYAN, CYAN, BOLD_CYAN, CYAN, BOLD_NC, CYAN,
           BOLD_CYAN, CYAN, BOLD_NC, CYAN, BOLD_CYAN, CYAN, BOLD_NC, CYAN,
           BOLD_CYAN, CYAN, BOLD_NC, CYAN, BOLD_CYAN, CYAN, BOLD_NC, CYAN,
           BOLD_CYAN, CYAN, BOLD_NC, CYAN, BOLD_CYAN,CYAN, BOLD_NC,CYAN,BOLD_CYAN, CYAN, BOLD_NC, CYAN, NC);

    if (fgets(input, sizeof input, stdin)) {
      input[strcspn(input, "\n")] = '\0';

      // 0: Termina il programma
      if (!strcmp(input, "0")) {
        break;
      }
      // 1: Modifica il numero di processi P
      else if (!strcmp(input, "1")) {
        char newInput[MAXINPUT];
        printf("%s"
               "╔═════════════════════════════════════════════╗\n"
               "║ %sInserisci il  nuovo numero (n) di%s           ║\n"
               "║ %sprocessi P desiderati:                n > 0%s ║\n"
               "╚═════════════════════════════════════════════╝\n"
               "%s> ",
               CYAN, BOLD_NC, CYAN, BOLD_NC, CYAN, NC);
        do {
          fgets(newInput, sizeof(newInput), stdin);
          newInput[strcspn(newInput, "\n")] = '\0';
          len = strlen(newInput);
          if (!isValidNumber(newInput, len)) {
            printf("%s"
                   "╔═════════════════════════════════════════════╗\n"
                   "║ %sValore non riconosciuto.%s                    ║\n"
                   "║ %sInserisci un nuovo numero:%s                  ║\n"
                   "╚═════════════════════════════════════════════╝\n"
                   "%s> ",
                   BOLD_RED, BOLD_NC, BOLD_RED, BOLD_NC, BOLD_RED, NC);
          } else {
            break;
          }
        } while (1);
        strcpy(parv[1], newInput);
      }
      // 2: Modifica il numero di processi Q
      else if (!strcmp(input, "2")) {
        char newInput[MAXINPUT];
        printf("%s╔═════════════════════════════════════════════╗\n"
               "║ %sInserisci il  nuovo numero (m) di%s           ║\n"
               "║ %sprocessi Q desiderati:                m > 0%s ║\n"
               "╚═════════════════════════════════════════════╝\n"
               "%s> ",
               CYAN, BOLD_NC, CYAN, BOLD_NC, CYAN, NC);
        do {
          fgets(newInput, sizeof(newInput), stdin);
          newInput[strcspn(newInput, "\n")] = '\0';
          len = strlen(newInput);
          if (!isValidNumber(newInput, len)) {
            printf("%s"
                   "╔═════════════════════════════════════════════╗\n"
                   "║ %sValore non riconosciuto.%s                    ║\n"
                   "║ %sInserisci un nuovo numero:%s                  ║\n"
                   "╚═════════════════════════════════════════════╝\n"
                   "%s> ",
                   BOLD_RED, BOLD_NC, BOLD_RED, BOLD_NC, BOLD_RED, NC);
          } else {
            break;
          }
        } while (1);
        strcpy(parv[2], newInput);
      }
      // 3: Aggiungi path da analizzare
      else if (!strcmp(input, "3")) {
        printf("\n%s"
               "╔═════════════════════════════════════════════╗\n"
               "║ %sInserisci i path dei file e delle cartelle%s  ║\n"
               "║ %sda analizzare.%s                              ║\n"
               "║ %sVai a capo dopo ogni path.%s                  ║\n"
               "║ %sDigita 'end' per terminare.%s                 ║\n"
               "║ %sDigita 'help' per un esempio.%s               ║\n"
               "╚═════════════════════════════════════════════╝\n"
               "%s> ",
               CYAN, BOLD_NC, CYAN, BOLD_NC, CYAN, BOLD_NC, CYAN, BOLD_NC, CYAN,
               BOLD_NC, CYAN, NC);
        int i = 0;
        do {
          fgets(file, sizeof(file), stdin);
          file[strcspn(file, "\n")] = '\0';
          if (!strcmp(file, "end")) {
            if (i == 0) {
              printf("%s"
                     "╔═════════════════════════════════════════════╗\n"
                     "║ %sInserisci almeno un path.%s                   ║\n"
                     "╚═════════════════════════════════════════════╝\n"
                     "%s> ",
                     BOLD_RED, BOLD_NC, BOLD_RED, NC);
            } else {
              break;
            }
          } else if (!strcmp(file, "help")) {
            printf("\n%s"
                   "╔═════════════════════════════════════════════╗\n"
                   "║ %s> filename%s                                  ║\n"
                   "║ %s> filename.txt%s                              ║\n"
                   "║ %s> path/to/filename.txt%s                      ║\n"
                   "║ %s> \"file name with spaces.txt\"%s               ║\n"
                   "║                                             ║\n"
                   "║ %s> foldername%s                                ║\n"
                   "║ %s> path/to/foldername%s                        ║\n"
                   "║                                             ║\n"
                   "║ %s> end%s                                       ║\n"
                   "╠═════════════════════════════════════════════╣\n"
                   "║ %sInserisci i path dei file da analizzare.%s    ║\n"
                   "╚═════════════════════════════════════════════╝\n"
                   "%s> ",
                   CYAN, BOLD_NC, CYAN, BOLD_NC, CYAN, BOLD_NC, CYAN, BOLD_NC,
                   CYAN, BOLD_NC, CYAN, BOLD_NC, CYAN, BOLD_NC, CYAN, BOLD_NC,
                   CYAN, NC);
          } else {
            files[i] = malloc(strlen(file) + 1);
            if(files[i]==NULL){
              printf("Errore allocazione memoria\n");
              return 2;
            }
            strcpy(files[i], file);
            i++;
            printf("> ");
          }
        } while (1);

        for (j = parc + 1; j <= parc + i; j++) {
          parv[j] = malloc(strlen(files[j - parc - 1]) + 1);
          if(parv[j]==NULL){
            printf("Errore allocazione memoria\n");
            return 2;
          }
          strcpy(parv[j], files[j - parc - 1]);
          free(files[j - parc - 1]);
        }

        parc += i;
        // 4: Rimuovi i path da analizzare
      }else if (!strcmp(input, "4")) {
        if(parc >=3 ){
          int index;
          do{
            printf("%s"
                  "╔═════════════════════════════════════════════╗\n"
                  "║ %sI path dei file sono:%s                       ║\n"
                  "╠═════════╦═══════════════════════════════════╝%s\n",
                  CYAN, BOLD_NC, CYAN, NC);
                  for (j = 3; j <= parc; j++) {
                    printf("%s║ %s%7d%s ║ %s%s\n", CYAN, BOLD_NC, j - 3, CYAN, NC,
                    parv[j]);
                  }
                  printf("%s╚═════════╝%s\n", CYAN, NC);
                  printf("\n%s"
                         "╔═════════════════════════════════════════════╗\n"
                         "║ %sDigita il numero del path e premi invio    %s ║\n"
                         "║ %sper rimuoverlo.                            %s ║\n"
                         "║ %sDigita 'end' per tornare alle              %s ║\n"
                         "║ %smodifiche \"on-the-fly\".                    %s ║\n"
                         "╚═════════════════════════════════════════════╝%s\n> ",
                         CYAN, BOLD_NC, CYAN, BOLD_NC, CYAN, BOLD_NC, CYAN, BOLD_NC, CYAN, NC);
                  fgets(file, sizeof(file), stdin);
                  file[strcspn(file, "\n")] = '\0';
                  if (!strcmp(file, "end")) {
                    break;
                  } else {
                    if(isValidNumber(file,strlen(file))||!strcmp(file, "0")){
                      index = atoi(file);
                      int k;
                      index = index + 3;
                      if(index > parc){ //indice non riconosciuto
                        printf("%s"
                               "╔═════════════════════════════════════════════╗\n"
                               "║ %sInserisci un numero compreso               %s ║\n"
                               "║ %stra 0 e %-20d               %s ║\n"
                               "╚═════════════════════════════════════════════╝%s\n",
                               BOLD_RED, BOLD_NC, BOLD_RED, BOLD_NC, parc-3, BOLD_RED,
                               NC);
                      }
                      else{ //caso accettato
                        parc--;
                        for(k=index; k<=parc; k++){
                          parv[k] = malloc(strlen(parv[k+1]) + 1);
                          if(parv[k]==NULL){
                            printf("Errore allocazione memoria\n");
                            return 2;
                          }
                          strcpy(parv[k], parv[k+1]);
                        }
                      }
                    }else{
                      printf("%s"
                            "╔═════════════════════════════════════════════╗\n"
                            "║ %sInput non riconosciuto%s                      ║\n"
                            "╚═════════════════════════════════════════════╝%s\n",
                            BOLD_RED, BOLD_NC, BOLD_RED, NC);
                    }
            }
          } while (parc >= 3);
        } else{
          printf("%s"
                 "╔═════════════════════════════════════════════╗\n"
                 "║ %sNon sono presenti path da rimuovere        %s ║\n"
                 "╚═════════════════════════════════════════════╝%s\n",
                 BOLD_RED, BOLD_NC, BOLD_RED, NC);
        }
    }
      // 5: Visualizza i path da analizzare
      else if (!strcmp(input, "5")) {
        if(parc >= 3){
          printf("%s"
                 "╔═════════════════════════════════════════════╗\n"
                 "║ %sI path dei file da analizzare sono:%s         ║\n"
                 "╠═════════╦═══════════════════════════════════╝%s\n",
                 CYAN, BOLD_NC, CYAN, NC);
          for (j = 3; j <= parc; j++) {
            printf("%s║ %s%7d%s ║ %s%s\n", CYAN, BOLD_NC, j - 3, CYAN, NC,
                   parv[j]);
          }
          printf("%s╚═════════╝%s\n", CYAN, NC);
        } else {
          printf("%s"
                 "╔═════════════════════════════════════════════╗\n"
                 "║ %sNon sono presenti path da analizzare       %s ║\n"
                 "╚═════════════════════════════════════════════╝%s\n",
                 CYAN, BOLD_NC, CYAN, NC);
        }
      }
      // 6: Esegui con i parametri attuali
      else if (!strcmp(input, "6")) {
        if(parc >= 3){
          mainFunction(parc, parv);
        } else {
          printf("%s"
                "╔═════════════════════════════════════════════╗\n"
                "║ %sAggiungi almeno un path da analizzare%s       ║\n"
                "╚═════════════════════════════════════════════╝%s\n",
                BOLD_RED, BOLD_NC, BOLD_RED, NC);
        }
      }
      // 7: Esegui un nuovo Main
      else if (!strcmp(input, "7")) {
        system("bin/main");
      }
      // comando non riconosciuto
      else {
        printf("%s"
               "╔═════════════════════════════════════════════╗\n"
               "║ %sComando non riconosciuto.%s                   ║\n"
               "║ %sInserisci un nuovo comando.%s                 ║\n"
               "╚═════════════════════════════════════════════╝%s",
               BOLD_RED, BOLD_NC, BOLD_RED, BOLD_NC, BOLD_RED, NC);
      }
    }
  } while (1);

  return 0;
}

// funzione che dato in input il numero di elementi 'parc' dell'array di
// stringhe 'pargv' procede a creare 2 sottoprocessi che eseguiranno
// parallelamente l'analyzer e il report
// al termine della loro esecuzione il main riprendere il controllo
void mainFunction(int parc, string parv[]) {
  parv[parc + 1] = NULL;

  pid_t a = fork();
  if (a == 0) {
    parv[0] = "bin/analyzer";
    execv("bin/analyzer", parv);
    printf("\nImpossibile eseguire l'analyzer");
    _exit(1);
  } else if (a > 0) {
    pid_t r = fork();
    if (r == 0) {
      string parv[] = {"bin/report", NULL};
      execv("bin/report", parv);
      printf("\nImpossibile eseguire il report");
      _exit(2);
    } else if (r > 0) {
      waitpid(a, 0, 0);
      waitpid(r, 0, 0);
    }
  } else {
    perror("fork fallito");
    _exit(3);
  }
}
