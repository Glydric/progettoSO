#include <stdio.h>
#include <string.h>
#include "util/inputs.c"
#include "util/getReadable.c"

/*
La classe che implementa il progetto di un cifratore, decifratore e brute force del cifrario di Cesare
solo i caratteri minuscoli e quelli maiuscoli sono inficiati, tutti gli altri caratteri rimangono uguali
*/

char sourceFileName[100];
char outFileName[100];

// checkRangeElseRemove(char begin, char letter, char end, int substract)
// {
//     if (begin <= letter && letter <= end)
//     { // se il risultato eccede i caratteri minuscoli ricalcola il valore
//         if (result > 0x5A)
//             return result - 0x1A;
//         else
//             return result;
//     }
// }
char slide(char letter, int slideValue)
{
    throwsIf("Il numero di slide non può essere maggiore di 25.\n", slideValue > 24);
    throwsIf("Il numero di spostamenti non può essere negativo.\n", slideValue < 0);

    printf("\n char %c => ", letter);
    int result = letter + slideValue;

    // checkRangeElseRemove(0x41, letter, 0x5A, 0x1A);
    // un carattere maiuscolo [0x41; 0x5A] differenza 0x19
    if (0x41 <= letter && letter <= 0x5A)
    { // se il risultato eccede i caratteri minuscoli ricalcola il valore
        if (result > 0x5A)
            return result - 0x1A;
        else
            return result;
    }

    // oppure un carattere minuscolo [0x61; 0x7A] differenza 0x19
    if (0x61 <= letter && letter <= 0x7A)
    { // se il risultato eccede i caratteri maiuscoli ricalcola il valore
        if (result > 0x7A)
        {
            printf("Dentro condizione verificata");
            return result - 0x1A;
        }
        else
        {
            printf("Dentro condizione NON verificata");
            return result;
        }
    }
    return letter;
}

void crypt(FILE *sourceFile)
{
    int slideValue = intInput("Inserire il numero di spostamenti in avanti: ");

    printf(" Risultato:\n");

    FILE *writeFile = getWriteableFile(outFileName);

    char c;

    while ((c = slide(getc(sourceFile), slideValue)) != EOF)
    {
        printf("%c", c);
        putc(c, writeFile);
    }

    fclose(sourceFile);
    fclose(writeFile);
}

char slideBack(char letter, int slideValue)
{
    throwsIf("Il numero di slide non può essere maggiore di 25.\n", slideValue > 24);
    throwsIf("Il numero di spostamenti non può essere negativo.\n", slideValue < 0);

    // printf("\nletter %c => ", letter);
    int result = letter - slideValue;

    // un carattere maiuscolo [0x41; 0x5A]
    if (0x41 <= letter && letter <= 0x5A)
    {
        // se è al limite dei maiuscoli ritorna il primo di essi
        if (result < 0x41)
            return result + 0x1A;
        else
            return result;
    }
    // oppure un carattere minuscolo [0x61; 0x7A]
    if (0x61 <= letter && letter <= 0x7A)
    {
        // se è al limite dei minuscoli ritorna il primo di essi
        if (result < 0x61)
            return result + 0x1A;
        else
            return result;
    }
    return letter;
}

void decrypt(FILE *sourceFile)
{
    int slideValue = intInput("Inserire il numero di spostamenti indietro: ");

    printf(" Risultato:\n");

    FILE *writeFile = getWriteableFile(outFileName);

    char c;

    while ((c = slideBack(getc(sourceFile), slideValue)) != EOF)
    {
        printf("%c", c);
        putc(c, writeFile);
    }

    fclose(sourceFile);
    fclose(writeFile);
}

int main()
{
    char choose = charInput("[C]rypt or [D]ecrypt? ");

    printf("Nome file sorgente: ");
    scanf("%s", sourceFileName);
    strcpy(outFileName, sourceFileName);

    if (choose == 'C' || choose == 'c')
    {
        strcat(outFileName, ".caesarCrypt");
        crypt(getReadableFile(sourceFileName));
    }
    else if (choose == 'D' || choose == 'd')
    {
        *outFileName = strtok(outFileName, ".")[0];
        strcat(outFileName, ".decrypted");
        decrypt(getReadableFile(sourceFileName));
    }
    else
        perror("Scelta non valida");
    printf("\nRisultato salvato nel file %s", outFileName);

    printf("\n");
}