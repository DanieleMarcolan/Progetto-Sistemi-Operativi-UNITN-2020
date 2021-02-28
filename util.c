#include "util.h"

// funzione che stampa un "\n"
void nl() { printf("\n"); }

// funzione che dato in input una stringa `n` di lunghezza `len` ritorna `1` se
// la stringa è un numero valido > 0, `0` altrimenti
int isValidNumber(string n, int len) {
  int valid = 0, i = 0;

  while (len > 0 &&
         isspace(n[len - 1])) // rimuovo gli spazi terminanti se presenti
    len--;

  if (len > 0) // controllo che sia stato passato almeno un carattere
  {
    valid = 1;
    for (i = 0; i < len;
         ++i) // se ogni carattere della stringa è un 'digit' rimane valido
    {
      if (!isdigit(n[i])) {
        valid = 0;
        break;
      }
    }
  }

  if (valid & atoi(n) == 0) { // se è valido ma è 0 lo segno come non valido
    valid = 0;
  }

  return valid;
}

// funzione che dato come input una stringa 'path' stampa a schermo la parte
// terminante della stringa contenente il nome del file
// esempio:
// path/to/file.txt stampa file.1.txt
void printFilenameFromPath(string path) {
  int len = 0, j = 0, c = -1;
  len = strlen(path);
  for (j = len; j >= 0; j--) {
    if (path[len - j] == '\\' || path[len - j] == '/') {
      c = len - j;
    }
  }
  if (c != -1) {
    printf(
        "%s ",
        path + c +
            1); // stampo a partile dal carattere path+c+1 della stringa passata
  } else {
    printf("%s ", path);
  }
}
