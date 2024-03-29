#include <stdio.h>
#include <omp.h>

static long num_steps = 10000000;
double step;

int main()
{
    double start_time = omp_get_wtime();
    int i;
    double x, pi;
    double sum = 0.0;
    step = 1.0/(double) num_steps;
    for (int i = 0; i < num_steps; i++)
    {
        x = (i + 0.5) * step;
        sum = sum + 4.0 / (1.0 + x * x);
    }
    pi = step * sum;
    printf("Pi is %lf\n", pi);
    double end_time = omp_get_wtime();
    double elapsed_time = end_time - start_time;
    printf("The time eleapsed is %lf\n", elapsed_time);
}