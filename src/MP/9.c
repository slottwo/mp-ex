#include <omp.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../lib/gen.h"

#define SIZE 1000000000

int main(int argc, char const *argv[])
{
    gen_init();

    double *vector = (double *)malloc(SIZE * sizeof(double));
    gen_vector_zto(vector, SIZE);

    long double sum, σ, μ, _;

    int NTHREADS = omp_get_num_procs() / 2;

    double t_start, t_serial, t_parallel;

    // Serial

    t_start = omp_get_wtime();

    sum = 0;
    for (int i = 0; i < SIZE; i++)
        sum += vector[i];

    μ = sum / SIZE;

    sum = 0;
    for (int i = 0; i < SIZE; i++)
    {
        _ = (vector[i] - μ);
        sum += _ * _;
    }
    σ = sqrt(_ / SIZE);

    t_serial = omp_get_wtime() - t_start;

    printf("  σ_serial : %Lf\n", σ);

    // Parallel

    t_start = omp_get_wtime();

    sum = 0;

#pragma omp parallel num_threads(NTHREADS)
#pragma omp for reduction(+ : sum)
    for (int i = 0; i < SIZE; i++)
        sum += vector[i];

    μ = sum / SIZE;

    sum = 0;

#pragma omp parallel num_threads(NTHREADS) private(_)
#pragma omp for reduction(+ : sum)
    for (int i = 0; i < SIZE; i++)
    {
        _ = (vector[i] - μ);
        sum += _ * _;
    }

    σ = sqrt(_ / SIZE);

    t_parallel = omp_get_wtime() - t_start;

    printf("σ_parallel : %Lf\n", σ);

    free(vector);

    statistic_log(t_serial, t_parallel, NTHREADS);

    return 0;
}