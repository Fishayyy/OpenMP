#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_LETTERS 26
#define NUM_OF_BOOKS 10

int main()
{
    double time = omp_get_wtime();
    int *charCount = calloc(NUM_LETTERS, sizeof(int));
    int i;
    omp_lock_t lock[NUM_LETTERS];
    
    for(int i = 0; i < NUM_LETTERS; ++i)
        omp_init_lock(&lock[i]);

    #pragma omp parallel for
    for(i = 0; i < NUM_OF_BOOKS; ++i)
    {
        char name[6] = "0.txt\0";
        name[0] += i;
        FILE *book = fopen(name, "r");
        char currChar;
        do
        {
            currChar = fgetc(book);
            switch(currChar)
            {
                case 'A'...'Z':
                    omp_set_lock(&lock[currChar - 'A']);
                    ++charCount[currChar - 'A'];
                    omp_unset_lock(&lock[currChar - 'A']);
                    break;
                case 'a'...'z':
                    omp_set_lock(&lock[currChar - 'a']);
                    ++charCount[currChar - 'a'];
                    omp_unset_lock(&lock[currChar - 'a']);
                    break;
            }
        } while(currChar != EOF);
        fclose(book);
    }
    
    printf("Completed in %lf seconds\n", (omp_get_wtime() - time));
    printf("The letter frequencies are:\n");

    for(int i = 0; i < NUM_LETTERS; ++i)
    {
        printf("%c's: %d\n", (i + 'A'), charCount[i]);
        omp_destroy_lock(&lock[i]);
    }
}