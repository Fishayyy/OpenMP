#include <omp.h>
#include <stdio.h>

int main()
{
    printf("SERIAL\n");
    omp_set_num_threads(4);
    printf("I JUST SET THE THREADS\n");
    #pragma omp parallel
    {
        printf("FIRST %d\n", omp_get_thread_num());
    }
    omp_set_num_threads(3);
    #pragma omp parallel
    {
        printf("SECOND %d\n", omp_get_thread_num());
    }
}
