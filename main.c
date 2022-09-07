#include <stdio.h>
#include <string.h>
#include "util/inputs.c"
#include "util/crypter.c"

/*
La classe che implementa il progetto di un cifratore, decifratore e brute force del cifrario di Cesare
solo i caratteri minuscoli e quelli maiuscoli sono inficiati, tutti gli altri caratteri rimangono uguali
*/

int main() {
    char choose = charInput("[C]rypt, [D]ecrypt or [B]rute force? ");
    char sourceFileName[500];
    char outFileName[500];

    printf("Nome file sorgente: ");
    scanf("%s", sourceFileName);
    strcpy(outFileName, sourceFileName);

    switch (choose) {
        case 'C':
        case 'c': {
            int slideValue = intInput("Inserire il numero di spostamenti in avanti: ");
            strcat(outFileName, ".caesarCrypt");
            cryptFile(getReadableFile(sourceFileName), getWriteableFile(outFileName), slideValue);
            break;
        }
        case 'D':
        case 'd': {
            int slideValue = intInput("Inserire il numero di spostamenti indietro: ");
            *outFileName = strtok(outFileName, ".")[0];
            strcat(outFileName, ".decrypted");
            decryptFile(getReadableFile(sourceFileName), getWriteableFile(outFileName), slideValue);
            break;
        }
        case 'B':
        case 'b': {
            *outFileName = strtok(outFileName, ".")[0];
            strcat(outFileName, ".cracked");
            crackFile(getReadableFile(sourceFileName), getWriteableFile(outFileName));

            int scelta;
            printf("\n\nScegliere il risultato corretto da salvare nel file: ");
            scanf("%i", &scelta);
            decryptFile(getReadableFile(sourceFileName), getWriteableFile(outFileName), scelta);

            break;
        }
        default:
            perror("Scelta non valida");
    }
    printf("\nRisultato salvato nel file %s", outFileName);
}