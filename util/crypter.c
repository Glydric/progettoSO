#include <stdio.h>
#include "getFiles.c"

void slideValueCheck(int slideValue) {
    if (slideValue > 24) {
        perror("\nIl numero di crypt non può essere maggiore di 25.\n");
        exit(EXIT_FAILURE);
    }
    if (slideValue < 0) {
        perror("\nIl numero di spostamenti non può essere negativo.\n");
        exit(EXIT_FAILURE);
    }
}

char decrypt(char letter, int slideValue) {
    slideValueCheck(slideValue);

    // printf("\nletter %c => ", letter);
    int result = letter - slideValue;

    // un carattere maiuscolo [0x41; 0x5A]
    if (0x41 <= letter && letter <= 0x5A) {
        // se è al limite dei maiuscoli ritorna il primo di essi
        if (result < 0x41)
            return result + 0x1A;
        else
            return result;
    }
    // oppure un carattere minuscolo [0x61; 0x7A]
    if (0x61 <= letter && letter <= 0x7A) {
        // se è al limite dei minuscoli ritorna il primo di essi
        if (result < 0x61)
            return result + 0x1A;
        else
            return result;
    }
    return letter;
}

void decryptFile(FILE *sourceFile, FILE *outFile, int slideValue) {
    printf("\n Risultato di %d spostamenti:\n", slideValue);

    char c;

    while ((c = decrypt(getc(sourceFile), slideValue)) != EOF) {
        printf("%c", c);
        putc(c, outFile);
    }

    fclose(sourceFile);
    fclose(outFile);
}

char crypt(char letter, int slideValue) {
    slideValueCheck(slideValue);

    // printf("\n char %c => ", letter);
    int result = letter + slideValue;

    // checkRangeElseRemove(0x41, letter, 0x5A, 0x1A);
    // un carattere maiuscolo [0x41; 0x5A] differenza 0x19
    if (0x41 <= letter && letter <= 0x5A) { // se il risultato eccede i caratteri minuscoli ricalcola il valore
        if (result > 0x5A)
            return result - 0x1A;
        else
            return result;
    }

    // oppure un carattere minuscolo [0x61; 0x7A] differenza 0x19
    if (0x61 <= letter && letter <= 0x7A) { // se il risultato eccede i caratteri maiuscoli ricalcola il valore
        if (result > 0x7A)
            return result - 0x1A;
        else
            return result;

    }
    return letter;
}

void cryptFile(FILE *sourceFile, FILE *outFile, int slideValue) {
    printf("\n Risultato di %d spostamenti:\n", slideValue);

    char c;

    while ((c = crypt(getc(sourceFile), slideValue)) != EOF) {
        printf("%c", c);
        putc(c, outFile);
    }

    fclose(sourceFile);
    fclose(outFile);
}

void crackFile(FILE *sourceFile, FILE *outFile) {
    for (int i = 1; i < 25; i++) {
        printf("\n\n Risultato di %d spostamenti\n", i);

        char c;

        while ((c = decrypt(getc(sourceFile), i)) != EOF) {
            printf("%c", c);
            putc(c, outFile);
        }

        putc('\n', outFile);

        rewind(sourceFile);

    }
    fclose(sourceFile);
    fclose(outFile);
}