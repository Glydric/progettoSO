#include <stdio.h>
#include <stdlib.h>

FILE *getReadableFile(char sourceFileName[]) {
    FILE *file = fopen(sourceFileName, "rb");
    if (file == NULL) {
        perror("Errore nell'apertura del file.\n");
        exit(EXIT_FAILURE);
    }
    return file;
}

FILE *getWriteableFile(char outFileName[]) {
    FILE *file = fopen(outFileName, "w");
    if (file == NULL) {
        perror("File non creato correttamente.\n");
        exit(EXIT_FAILURE);
    }
    return file;
}
