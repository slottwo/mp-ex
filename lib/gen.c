#include <omp.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "gen.h"

void gen_init()
{
    time_t t;
    srand((unsigned)time(&t));
}

void gen_vector(double *v, double min, double max, int size)
{
    int NTHREADS = omp_get_num_procs() / 2;

#pragma omp parallel num_threads(NTHREADS)
    {
#pragma omp for
        for (int i = 0; i < size; i++)
        {
            v[i] = min + (max - min) * (rand() / (double)RAND_MAX);
        }
    }
}

void gen_vector_zto(double *v, int size)
{
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
    max -= min;
    return rand() % max + min;
}

double gen_rand(double max)
{
    return (rand() / (double)RAND_MAX) * max;
}

void statistic_log(double t_serial, double t_parallel, int nthreads)
{
    double bonus = (t_serial / t_parallel - 1) * 100;

    printf("\nlog:\n");
    printf("  t_serial : %.4f\n", t_serial);
    printf("t_parallel : %.4f\n", t_parallel);
    printf("num_thread : %d\n", nthreads);
    printf("   speedup : %.4f\n", t_serial / t_parallel);
    printf("      diff : %.2f %%\n", bonus);
    printf("efficiency : %.3f %%\n", 100.0 * (t_serial / t_parallel) / (double)nthreads);
}
