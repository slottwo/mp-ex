#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "headers/generator.h"

void gen_vector(float *v)
{
    time_t t;
    srand((unsigned)time(&t));
    
#pragma omp parallel num_threads(6)
    {
        #pragma omp for
        for (int i = 0; i < SIZE; i++)
        {
            v[i] = (rand() / (float)RAND_MAX);
        }
    }
}
