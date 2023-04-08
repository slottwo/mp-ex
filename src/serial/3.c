#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../../lib/headers/generator.h"

int main(int argc, char const *argv[])
{
    int *v = (int *)malloc(SIZE * sizeof(int));
    gen_vector_int(v, 1, 100000);

    double average = 0;

    double t_start = omp_get_wtime();

    for (int i = 0; i < SIZE; i++)
    {
        average += v[i];
    }
    
    average /= SIZE;

    printf("t: %.6fs\n", omp_get_wtime() - t_start);

    printf("avg: %0.5f\n", average);

    return 0;
}
