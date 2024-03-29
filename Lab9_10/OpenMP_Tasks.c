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

    #pragma omp parallel
    {
        #pragma omp single
        {
            for(i = 0; i < NUM_OF_BOOKS; ++i)
            {
                char name[6] = "0.txt\0";
                name[0] += i;
                FILE *book = fopen(name, "r");
                char currChar;
                #pragma omp task
                {
                    do
                    {
                        currChar = fgetc(book);
                        switch(currChar)
                        {
                            case 'A'...'Z':
                                #pragma omp atomic
                                ++charCount[currChar - 'A'];
                                break;
                            case 'a'...'z':
                                #pragma omp atomic
                                ++charCount[currChar - 'a'];
                                break;
                        }
                    } while(currChar != EOF);
                    fclose(book);
                }
            }
        }
    }

    printf("Completed in %lf seconds\n",omp_get_wtime() - time);
    printf("The letter frequencies are:\n");

    for(int i = 0; i < NUM_LETTERS; ++i)
        printf("%c's: %d\n", (i + 'A'), charCount[i]);
}