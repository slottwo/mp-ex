#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../lib/gen.h"

#define MAX 9999
#define SIZE 100000000

int main(int argc, char const *argv[])
{
    gen_init();

    int NTHREADS = omp_get_num_procs() / 2;

    double *v = (double *)malloc(SIZE * sizeof(double));
    gen_vector(v, 0, MAX, SIZE);

    double t_start, t_serial, t_parallel, sum = 0;

    // Serial

    t_start = omp_get_wtime();

    for (int i = 0; i < SIZE; i++)
    {
        sum += v[i];
    }

    t_serial = omp_get_wtime() - t_start;

    printf("sum: %f\n", sum);

    // Parallel

    sum = 0;

    t_start = omp_get_wtime();

#pragma omp parallel num_threads(NTHREADS)
    {
#pragma omp for reduction(+ : sum)
        for (int i = 0; i < SIZE; i++)
        {
            sum += v[i];
        }
    }

    t_parallel = omp_get_wtime() - t_start;

    free(v);

    printf("sum: %f\n", sum);

    statistic_log(t_serial, t_parallel, NTHREADS);

    return 0;
}