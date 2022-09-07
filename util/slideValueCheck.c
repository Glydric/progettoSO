#include <stdio.h>
#include <stdlib.h>

void slideValueCheck(int value) {
    if (value > 24) {
        perror("Il numero di crypt non può essere maggiore di 25.\n");
        exit(EXIT_FAILURE);
    }
    if (value < 0) {
        perror("Il numero di spostamenti non può essere negativo.\n");
        exit(EXIT_FAILURE);
    }

}
