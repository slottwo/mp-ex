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

void statistic_log(char title[], double t, double t_serial, int nthreads)
{
    printf("================\n");

    int i = 0;
    while (title[i] != '\0')
        i++;

    i = 8 - i / 2;

    while (i)
    {
        printf(" ");
        i--;
    }
    

    printf("%s\n", title);

    printf("time: %.7fs\n", t);

    double bonus = (t_serial / t - 1) * 100;
    printf("speedup: %s%.2f%%\n", bonus > 0 ? "+" : "", bonus);

    // printf("speedup: %.2f\n", t_serial / t);

    printf("efficiency: %.2f\n", t_serial / t / nthreads);
    printf("================\n");
}
