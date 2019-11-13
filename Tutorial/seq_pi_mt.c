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
    const int num_of_threads = 10;
    omp_set_num_threads(num_of_threads);
    double sums[num_of_threads] = {0};
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        for (int i = id; i < num_steps; i += num_of_threads)
        {
            double x = (i + 0.5) * step;
            sums[id] += 4.0 / (1.0 + x * x);
        }
    }

    for(int i = 0; i < num_of_threads; i++)
    {
        sum += sums[i];
    }

    pi = step * sum;
    printf("Pi is %lf\n", pi);
    double end_time = omp_get_wtime();
    double elapsed_time = end_time - start_time;
    printf("The time eleapsed is %lf\n", elapsed_time);
}