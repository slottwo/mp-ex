#include <omp.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "headers/generators.h"

void gen_vector_zto(double *v, int size)
{
    time_t t;
    srand((unsigned)time(&t));

    int NTHREADS = omp_get_num_procs() / 2;

#pragma omp parallel num_threads(NTHREADS)
    {
#pragma omp for
        for (int i = 0; i < size; i++)
        {
            v[i] = (rand() / (double)RAND_MAX);
        }
    }
}

void gen_vector_int(int *v, int min, int max, int size)
{
    time_t t;
    srand((unsigned)time(&t));

    int NTHREADS = omp_get_num_procs() / 2;

#pragma omp parallel num_threads(NTHREADS)
    {
#pragma omp for
        for (int i = 0; i < size; i++)
        {
            v[i] = (rand() % max + min);
        }
    }
}

int gen_int(int min, int max)
{
    return rand() % max + min;
}

void statistic_log(double t, double t_serial, int nthreads)
{
    double bonus = (t_serial / t - 1) * 100;

    printf("\n");
    printf("    serial: %.3fµs\n", t_serial * 1000000);
    printf("  parallel: %.3fµs\n", t * 1000000);
    printf("   speedup: %s%.2f%%\n", bonus > 0 ? "+" : "", bonus);
    printf("efficiency: %.3f\n", t_serial / t / nthreads);
}
