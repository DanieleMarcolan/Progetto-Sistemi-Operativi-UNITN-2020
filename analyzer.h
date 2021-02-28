#include "util.h"

// costanti per le pipe
#define READ 0
#define WRITE 1

typedef struct{
  string filename;
  int fileNumber;
  int numOfChars;
  int firstChar;
  int lastChar;
} SPLIT;

typedef struct FilePaths
{
  int size;
  int next;
  char **path;
}FilePaths;

// per DEBUGGING
// string aliasArray[8] = {"caratteri", "cifre", "lettere", "minuscole", "maisucole", "punteggiatura", "spazi", "altro"};

void constructor(FilePaths *f);
void addPath(FilePaths *f, char *path);
void scanPath(FilePaths *f, char *path);
string copyString(char *str, int size);
string concat3(const char *a, const char *b, const char *c);

off_t fsize(string filename);
void stats(SPLIT split, int *array);
