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

void statistic_log(char type[], int length, double t, double t_serial, int nthreads)
{
    for (int i = 0; i < (16 - length) / 2; i++)
    {
        printf(" ");
    }

    printf("%s\n", type);
    printf("time: %.7fs\n", t);
    double bonus_speed = (t_serial / t - 1) * 100;
    if (bonus_speed < 0)
    {
        printf("speedup: %.2f%%\n", bonus_speed);
    }
    else
    {
        printf("speedup: +%.2f%%\n", bonus_speed);
    }
    // printf("speedup: %.2f\n", t_serial / t);
    printf("efficiency: %.2f\n\n", t_serial / t / nthreads);
}
