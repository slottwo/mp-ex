#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../lib/gen.h"

#define SIZE 100000000

int main(int argc, char const *argv[])
{
    gen_init();

    int Max = -1, max = -1, index, Index;

    int *vector = (int *)malloc(SIZE * sizeof(int));
    gen_vector_int(vector, SIZE, 0, RAND_MAX);

    int NTHREADS = omp_get_num_procs() / 2;

    double t_start, t_serial, t_parallel;

    // Serial

    t_start = omp_get_wtime();

    for (int i = 0; i < SIZE; i++)
        if (vector[i] > max)
        {
            max = vector[i];
            index = i;
        }

    t_serial = omp_get_wtime() - t_start;

    printf("  m_serial : %d\n", max);
    printf("  i_serial : %d\n", index);

    // Parallel

    max = -1; index = -1;

    t_start = omp_get_wtime();

#pragma omp parallel private(max, index) num_threads(NTHREADS)
    {
#pragma omp for
        for (int i = 0; i < SIZE; i++)
            if (vector[i] > max)
            {
                max = vector[i];
                index = i;
            }

#pragma omp critical
        {
            if (max > Max)
            {
                Max = max;
                Index = index;
            }
        }
    }

    t_parallel = omp_get_wtime() - t_start;

    printf("m_critical : %d\n", Max);
    printf("i_critical : %d\n", Index);

    statistic_log(t_serial, t_parallel, NTHREADS);

    return 0;
}