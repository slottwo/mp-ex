#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../lib/gen.h"

#define SIZE 10

int main(int argc, char const *argv[])
{
    gen_init();

    int NTHREADS = omp_get_num_procs() / 2;

    double t_start, t_serial, t_parallel;

    double *v1 = (double *)malloc(sizeof(double) * SIZE);
    double *v2 = (double *)malloc(sizeof(double) * SIZE);

    double sum;

    gen_vector(v1, SIZE, -99, 99);
    gen_vector(v2, SIZE, -99, 99);

    // Serial

    sum = 0;

    t_start = omp_get_wtime();

    for (int i = 0; i < SIZE; i++)
        sum += v1[i] * v2[i];

    t_serial = omp_get_wtime() - t_start;

    printf("Sum: %.2lf\n", sum);

    // Parallel

    sum = 0;

    t_start = omp_get_wtime();

#pragma omp parallel num_threads(NTHREADS)
    {
#pragma omp for
        for (int i = 0; i < SIZE; i++)
            sum += v1[i] * v2[i];
    }

    t_parallel = omp_get_wtime() - t_start;

    printf("Sum: %.2lf\n", sum);

    // End

    free(v1);
    free(v2);

    statistic_log(t_serial, t_parallel, NTHREADS);

    return 0;
}