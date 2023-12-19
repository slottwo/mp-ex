#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../../lib/headers/generators.h"

#define N 10000000

int main(int argc, char const *argv[])
{
    int NTHREADS = omp_get_num_procs() / 2;

    double t_start, t_serial, t_parallel, x, dx, pi, sum = 0;

    // Serial

    t_start = omp_get_wtime();

    dx = 1.0 / N;

    for (int i = 0; i < N; i++)
    {
        x = (i + 0.5) * dx;
        sum += 4.0 / (1.0 + x * x);
    }

    pi = sum * dx;

    t_serial = omp_get_wtime() - t_start;

    printf("PI: 3.14159265358979323846264338327950288\n");
    printf("pi: %.35f\n", pi);

    // Parallel

    t_start = omp_get_wtime();

#pragma omp parallel num_threads(NTHREADS)

    t_parallel = omp_get_wtime() - t_start;

    statistic_log(t_serial, t_parallel, NTHREADS);

    return 0;
}