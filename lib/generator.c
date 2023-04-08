#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "headers/generator.h"

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
