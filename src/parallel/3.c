#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../../lib/headers/generator.h"


int main(int argc, char const *argv[])
{
    double *v = (double *)malloc(SIZE * sizeof(double));
    gen_vector(v);

    double average = 0;

    int NTHREADS = omp_get_num_procs() / 2;

    double t_start = omp_get_wtime();

#pragma omp parallel num_threads(NTHREADS)
    {
#pragma omp for reduction(+:average)
        for (int i = 0; i < SIZE; i++)
        {
            average += v[i];
        }
    }

    average /= SIZE;

    printf("t: %.6fs\n", omp_get_wtime() - t_start);

    printf("avg: %0.5f\n", average);

    return 0;
}
