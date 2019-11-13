#include <stdio.h>
#include <omp.h>

static long num_steps = 10000000;
double step;

int main()
{
    double start_time = omp_get_wtime();
    int i;
    double pi;
    double sum = 0.0;
    step = 1.0/(double) num_steps;
    double num_threads;
    #pragma omp parallel
    {
        double temp_sum = 0.0;
        int id = omp_get_thread_num();
        int acutal_thread_count = omp_get_num_threads;
        for (int i = id; i < num_steps; i += num_of_threads)
        {
            double x = (i + 0.5) * step;
            double temp = 4.0 / (1.0 + x * x);
            temp_sum += temp;
        }
    }

    pi = step * sum;
    printf("Pi is %lf\n", pi);
    double end_time = omp_get_wtime();
    double elapsed_time = end_time - start_time;
    printf("The time eleapsed is %lf\n", elapsed_time);
}