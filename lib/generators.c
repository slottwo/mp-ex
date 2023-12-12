#include <omp.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "headers/generators.h"

void gen_vector_zto(double *v)
{
    time_t t;
    srand((unsigned)time(&t));

#pragma omp parallel num_threads(3)
    {
#pragma omp for
        for (int i = 0; i < SIZE; i++)
        {
            v[i] = (rand() / (double)RAND_MAX);
        }
    }
}

void gen_vector_int(int *v, int min, int max)
{
    time_t t;
    srand((unsigned)time(&t));

#pragma omp parallel num_threads(3)
    {
#pragma omp for
        for (int i = 0; i < SIZE; i++)
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
    printf("serial:    %.3fµs\n", t_serial * 1000000);
    printf("parallel:  %.3fµs\n", t * 1000000);

    double bonus = (t_serial / t - 1) * 100;
    printf("speedup:   %s%.2f%%\n", bonus > 0 ? "+" : "", bonus);

    // printf("speedup: %.2f\n", t_serial / t);

    printf("efficiency:  %.3f\n", t_serial / t / nthreads);
}
