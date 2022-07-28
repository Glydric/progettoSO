#include <stdbool.h>
#include <stdlib.h>

void throwsIf(char text[], bool condition)
{
    if (condition)
    {
        perror(text);
        exit(EXIT_FAILURE);
    }
}