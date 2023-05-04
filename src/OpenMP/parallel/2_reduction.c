#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char const *argv[])
{
    static long n_step = 500000000;
    double dx = 1 / (double)n_step;

    int i;
    double x, pi, sum = 0.;

    int NTHREADS = omp_get_num_threads() / 2;

    double t_start = omp_get_wtime();

#pragma omp parallel private(x) num_threads(NTHREADS)
    {
#pragma omp for reduction(+:sum)
        for (i = 0; i < n_step; i++)
        {
            x = (i + 0.5) * dx;
            sum += 4.0 / (1.0 + x * x);
        }
    }

    pi = sum * dx;

    printf("t: %.5fs\n", omp_get_wtime() - t_start);

    printf("pi: %0.5f\n", pi);

    return 0;
}
