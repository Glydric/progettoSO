#include <stdio.h>
#include "throwsIf.c"

FILE *getReadableFile(char sourceFileName[])
{
    FILE *file = fopen(sourceFileName, "rb");
    throwsIf("Errore nell'apertura del file.\n", file == NULL);
    return file;
}

FILE *getWriteableFile(char outFileName[])
{
    FILE *file = fopen(outFileName, "w");
    throwsIf("File non creato correttamente.\n", file == NULL);
    return file;
}
