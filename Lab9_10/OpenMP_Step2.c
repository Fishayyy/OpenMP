#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_LETTERS 26
#define ASCII_A 65
#define ASCII_a 97

int main()
{
    double time = omp_get_wtime();
    int *charCount = calloc(NUM_LETTERS, sizeof(int));
    FILE *book = fopen("0.txt\0", "r");
    char currChar;

    do
    {
        currChar = fgetc(book);
        switch(currChar)
        {
            case 'A'...'Z':
                ++charCount[currChar - ASCII_A];
                break;
            case 'a'...'z':
                ++charCount[currChar - ASCII_a];
                break;
        }
    } while(currChar != EOF);

    fclose(book);
    printf("Completed in %lf seconds\n", (omp_get_wtime() - time));
    printf("The letter frequencies are:\n");

    for(int i = 0; i < NUM_LETTERS; ++i)
        printf("%c's: %d\n", i + ASCII_A, charCount[i]);
}