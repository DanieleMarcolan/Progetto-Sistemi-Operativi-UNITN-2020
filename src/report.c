#include "report.h"

int main() {
  int fd;
  int i, f; // variabili per cicli for
  char *myfifo = "/tmp/myfifo";
  mkfifo(myfifo, 0666);
  fd = open(myfifo, O_RDONLY);
  int x = 0; // numero file passati in input ad analyzer

  read(fd, &x, sizeof(int)); // x viene popolato

  int files[x][SIZE];             // statistiche file in posizione data
  read(fd, files, sizeof(files)); // files[x][SIZE] popolato
  int total[SIZE];                // statistiche totali dei file in input
  read(fd, total, sizeof(total)); // total[SIZE] popolato
  char filesName[x][MAXFILENAME]; // nome dei file in input
  read(fd, filesName, sizeof(filesName)); // filesName[x][MAXLEN] popolato

  int len = 0, j = 0, c;

  printf("\n%s"
         "╔═════════════════════════════════════════════╗\n"
         "║ %sBenvenuto nel Report%s                        ║\n"
         "╚═════════════════════════════════════════════╝%s",
         GREEN, BOLD_GREEN, GREEN, NC);

  char input[MAXINPUT];
  do {
    if (x > 0) {
      printf("\n%s"
             "╔═════════════════════════════════════════════╗\n"
             "║ %sDigita%s                                      ║\n"
             "╠═══╦═════════════════════════════════════════╣\n"
             "║ %s1%s ║ %sResoconto totale%s                        ║\n"
             "║ %s2%s ║ %sResoconto totale dettagliato%s            ║\n"
             "╠═══╬═════════════════════════════════════════╣\n"
             "║ %s3%s ║ %sResoconto di ogni file%s                  ║\n"
             "║ %s4%s ║ %sResoconto di ogni file dettagliato%s      ║\n"
             "║ %s5%s ║ %sResoconto di un file specifico%s          ║\n"
             "╠═══╬═════════════════════════════════════════╣\n"
             "║ %s0%s ║ %sModifiche on-the-fly (modalità 'Main')%s  ║\n"
             "║   ║ %sEsci (modalità 'Analyzer e Report')%s     ║\n"
             "╚═══╩═════════════════════════════════════════╝\n"
             "%s> ",
             GREEN, BOLD_GREEN, GREEN, BOLD_GREEN, GREEN, BOLD_NC, GREEN,
             BOLD_GREEN, GREEN, BOLD_NC, GREEN, BOLD_GREEN, GREEN, BOLD_NC,
             GREEN, BOLD_GREEN, GREEN, BOLD_NC, GREEN, BOLD_GREEN, GREEN,
             BOLD_NC, GREEN, BOLD_GREEN, GREEN, BOLD_NC, GREEN, BOLD_NC, GREEN,
             NC);
    } else {
      printf("\n%s"
             "╔═════════════════════════════════════════════╗\n"
             "║ %sI path analizzati non contengono file%s       ║\n"
             "║ %soppure non esistono.%s                        ║\n"
             "╠═════════════════════════════════════════════╣\n"
             "║ %sDigita%s                                      ║\n"
             "╠═══╦═════════════════════════════════════════╣\n"
             "║ %s0%s ║ %sModifiche on-the-fly (modalità 'Main')%s  ║\n"
             "║   ║ %sEsci (modalità 'Analyzer e Report')%s     ║\n"
             "╚═══╩═════════════════════════════════════════╝\n"
             "%s> ",
             GREEN, BOLD_NC, GREEN, BOLD_NC, GREEN, BOLD_GREEN, GREEN,
             BOLD_GREEN, GREEN, BOLD_NC, GREEN, BOLD_NC, GREEN, NC);
    }

    if (fgets(input, sizeof input, stdin)) {
      input[strcspn(input, "\n")] = '\0';

      if (!strcmp(input, "0")) {
        break;
      } else if (x > 0 && !strcmp(input, "1")) {
        resoconto(total, "", 0, 0);
      } else if (x > 0 && !strcmp(input, "2")) {
        resoconto(total, "", 0, 1);
      } else if (x > 0 && !strcmp(input, "3")) {
        for (f = 0; f < x; f++) {
          resoconto(files[f], filesName[f], 1, 0);
        }
      } else if (x > 0 && !strcmp(input, "4")) {
        for (f = 0; f < x; f++) {
          resoconto(files[f], filesName[f], 1, 1);
        }
      } else if (x > 0 && !strcmp(input, "5")) {

        printf("%s"
               "╔═════════════════════════════════════════════╗\n"
               "║ %sScegli il file                             %s ║\n"
               "╠═════════╦═══════════════════════════════════╝%s\n",
               GREEN, BOLD_NC, GREEN, NC);
        for (f = 0; f < x; f++) {
          printf("%s║ %s%7d%s ║ %s%s\n", GREEN, BOLD_NC, f, GREEN, NC,
                 filesName[f]);
        }
        printf("%s╚═════════╝%s\n", GREEN, NC);

        char chooseFile[MAXINPUT];
        do {
          printf("\n%s"
                 "╔═════════════════════════════════════════════╗\n"
                 "║ %sDigita il numero del file e premi invio.%s    ║\n"
                 "║ %sDigita 'list' per vedere la lista dei file.%s ║\n"
                 "║ %sDigita 'end' per tornare al Report.%s         ║\n"
                 "╚═════════════════════════════════════════════╝%s\n> ",
                 GREEN, BOLD_NC, GREEN, BOLD_NC, GREEN, BOLD_NC, GREEN, NC);
          if (fgets(chooseFile, sizeof chooseFile, stdin)) {
            chooseFile[strcspn(chooseFile, "\n")] = '\0';
            if ((isValidNumber(chooseFile, strlen(chooseFile)) ||
                 !strcmp(chooseFile, "0")) &&
                atoi(chooseFile) < x) {
              resoconto(files[atoi(chooseFile)], filesName[atoi(chooseFile)], 1,
                        1);
            } else {
              if (!strcmp(chooseFile, "list")) {
                printf("%s"
                       "╔═════════════════════════════════════════════╗\n"
                       "║ %sScegli il file                             %s ║\n"
                       "╠═════════╦═══════════════════════════════════╝%s\n",
                       GREEN, BOLD_NC, GREEN, NC);
                for (f = 0; f < x; f++) {
                  printf("%s║ %s%7d%s ║ %s%s\n", GREEN, BOLD_NC, f, GREEN, NC,
                         filesName[f]);
                }
                printf("%s╚═════════╝%s\n", GREEN, NC);
              } else if (!strcmp(chooseFile, "end")) {
                break;
              } else {
                printf("%s"
                       "╔═════════════════════════════════════════════╗\n"
                       "║ %sInserisci un numero compreso               %s ║\n"
                       "║ %stra 0 e %-20d               %s ║\n"
                       "╚═════════════════════════════════════════════╝%s\n ",
                       BOLD_RED, BOLD_NC, BOLD_RED, BOLD_NC, f - 1, BOLD_RED,
                       NC);
              }
            }
          }
        } while (1);
      } else {
        printf("%s"
               "╔═════════════════════════════════════════════╗\n"
               "║ %sComando non riconosciuto.%s                   ║\n"
               "║ %sInserisci un nuovo comando.%s                 ║\n"
               "╚═════════════════════════════════════════════╝%s",
               BOLD_RED, BOLD_NC, BOLD_RED, BOLD_NC, BOLD_RED, NC);
      }
    }

  } while (1);

  close(fd);

  return 0;
}

void resoconto(int array[SIZE], string filesName, int fileFlag,
               int detailsFlag) {
  // fileFlag 0 = resoconto totale
  // fileFlag 1 = resoconto di un file

  // detailsFlag 0 = solo resoconto
  // detailsFlag 1 = resoconto dettagliato

  int i;
  nl();
  if (fileFlag) {
    printf("%s File %d: ", BOLD_GREEN, array[0]);
    printFilenameFromPath(filesName);
    printf("%s\n", NC);
  } else {
    printf("%s┌─────────────────────────────────────────────┐\n"
           "│ %sResoconto%s                                   │\n"
           "├───────────────────┬─────────────────────────┤\n"
           "│ %s%-17s%s │ %s%-23d%s │%s\n",
           GREEN, BOLD_GREEN, GREEN, BOLD_NC, "File analizzati", GREEN, BOLD_NC,
           array[0], GREEN, NC);
  }

  if (array[1] > 0) {
    for (i = 1; i < ASCIIOFFSET; i++) {
      if (array[i] > 0) {
        if (i == 1) {
          if (fileFlag) {
            printf("%s┌───────────────────┬────────────────┬────────┐%s\n",
                   GREEN, NC);
          } else {
            printf("%s├───────────────────┼────────────────┬────────┤%s\n",
                   GREEN, NC);
          }
          printf("%s│ %s%-17s%s │ %s%-14d%s │ %s%6s%s │%s\n", GREEN, BOLD_NC,
                 "Caratteri", GREEN, BOLD_NC, array[i], GREEN, BOLD_NC, "%",
                 GREEN, NC);
          printf("%s├───────────────────┼────────────────┼────────┤%s\n", GREEN,
                 NC);
        } else {
          printf("%s│ %s%-17s%s │ %s%-14d%s │ %s%5.1f%%%s │%s\n", GREEN,
                 BOLD_NC, aliasArray[i - 1], GREEN, BOLD_NC, array[i], GREEN,
                 BOLD_NC, (array[i] * 100.0) / array[1], GREEN, NC);
        }
      }
    }
    printf("%s└───────────────────┴────────────────┴────────┘%s\n", GREEN, NC);

    if (detailsFlag) {
      resocontoDettagliato(array, filesName, fileFlag);
    }
  } else {
    if (!fileFlag) {
      printf("%s└───────────────────┴─────────────────────────┘%s\n", GREEN,
             NC);
    }
    printf("%s┌─────────────────────────────────────────────┐\n"
           "│  %s0 caratteri trovati.%s                       │\n"
           "└─────────────────────────────────────────────┘%s\n",
           GREEN, BOLD_NC, GREEN, NC);
  }
}

void resocontoDettagliato(int array[SIZE], string filesName, int fileFlag) {
  const int cols = 2;
  int i, j = 0, k;

  printf("%s┌%s", GREEN, NC);
  for (i = 0; i < cols; i++) {
    printf("%s─────┬────────────────%s", GREEN, NC);
    if (i < cols - 1) {
      printf("%s┬%s", GREEN, NC);
    }
  }
  printf("%s┐%s\n", GREEN, NC);

  for (i = 0; i < ASCII; i++) {
    if (array[i + ASCIIOFFSET] > 0) {
      if (i == 10) { // new line
        printf("%s│ %s%s %s │ %s%-14d ", GREEN, BOLD_NC, "\\n", GREEN, NC,
               array[i + ASCIIOFFSET]);
      } else if (i == 32) {
        printf("%s│ %s%s%s │ %s%-14d ", GREEN, BOLD_NC, "\' \'", GREEN, NC,
               array[i + ASCIIOFFSET]);
      } else {
        printf("%s│ %s %c %s │ %s%-14d ", GREEN, BOLD_NC, i, GREEN, NC,
               array[i + ASCIIOFFSET]);
      }
      if (++j % cols == 0) {
        printf("%s│%s\n", GREEN, NC);
      }
    }
  }

  if (j % cols != 0) {
    for (i = 0; i < cols - (j % cols); i++) {
      printf("%s│     │                %s", GREEN, NC);
      if (i == cols - (j % cols) - 1) {
        printf("%s│%s\n", GREEN, NC);
      }
    }
  }

  printf("%s└%s", GREEN, NC);
  for (i = 0; i < cols; i++) {
    printf("%s─────┴────────────────%s", GREEN, NC);
    if (i < cols - 1) {
      printf("%s┴%s", GREEN, NC);
    }
  }
  printf("%s┘%s\n", GREEN, NC);
  nl();
}
