// inclusione delle librerie utilizzate
#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// definizione dei colori utilizzati nei printf
#define CYAN        "\033[0;36m"
#define BOLD_CYAN   "\033[1;36m"
#define GREEN       "\033[0;32m"
#define BOLD_GREEN  "\033[1;32m"
#define YELLOW      "\033[0;33m"
#define BOLD_YELLOW "\033[1;33m"
#define RED		      "\033[0;31m"
#define BOLD_RED 	  "\033[1;31m"
#define NC          "\033[0m"
#define BOLD_NC     "\033[1;39m"

#define MAXPATHS    1024        // il numero massimo di paths a file/cartelle che accetta
#define MAXFILENAME 1024        // il numero massimo di paths a file/cartelle che accetta
#define MAXINPUT    1024        // lunghezza massima di un comando di input da parte dell'utente

#define ASCII       127         // numero di caratteri ASCII che riconosciamo
#define COUNTERS    8           // numero di "contatori": caratteri, cifre, lettere, minuscole, maiuscole, punteggiatura, spazi, altro
#define ASCIIOFFSET (1 + COUNTERS)
#define SIZE        (ASCIIOFFSET + ASCII) // la dimensione di un array che conterrà le informazioni relative ad un file, il primo elemento rappresenta il numero del file, seguito dai contatori, e dai caratteri ASCII


typedef char* string;

// dichiarazione di funzioni utili
void nl();
int isValidNumber(string n, int len);
void printFilenameFromPath(string path);
