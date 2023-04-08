#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../../lib/headers/generator.h"

int main(int argc, char const *argv[])
{
    int *v = (int *)malloc(SIZE * sizeof(int));
    gen_vector_int(v, 1, 100000);

    // Serial

    double average_serial = 0;

    double t_start = omp_get_wtime();

    for (int i = 0; i < SIZE; i++)
        average_serial += v[i];

    average_serial /= SIZE;

    double t_diff_s = omp_get_wtime() - t_start;

    printf("t_serial:\t%.6fs\n", t_diff_s);
    printf("avg_serial:\t%0.5f\n", average_serial);
    printf("---\n");

    // Parallel

    double average_parallel = 0;

    int NTHREADS = omp_get_num_procs() / 2;

    t_start = omp_get_wtime();

#pragma omp parallel num_threads(NTHREADS)
    {
#pragma omp for reduction(+ \
                          : average_parallel)
        for (int i = 0; i < SIZE; i++)
        {
            average_parallel += v[i];
        }
    }

    average_parallel /= SIZE;

    double t_diff_p = omp_get_wtime() - t_start;

    double speedup = t_diff_s / t_diff_p;
    double efficiency = speedup / NTHREADS;

    printf("t_parallel:\t%.6fs\n", t_diff_p);
    printf("avg_parallel:\t%0.5f\n", average_parallel);
    printf("---\n");

    printf("speedup:\t%.4f\n", speedup);
    printf("efficiency:\t%.2f%%\n", efficiency*100);

    return 0;
}
