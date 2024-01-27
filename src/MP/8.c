#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../lib/gen.h"

#define SIZE 1000000000

int main(int argc, char const *argv[])
{
    gen_init();

    int sub_max = -1, max = -1, sub_i, index;

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

    max = -1;
    index = -1;

    t_start = omp_get_wtime();

#pragma omp parallel private(sub_max, sub_i) num_threads(NTHREADS)
    {
#pragma omp for
        for (int i = 0; i < SIZE; i++)
            if (vector[i] > sub_max)
            {
                sub_max = vector[i];
                sub_i = i;
            }

#pragma omp critical
            if (max < sub_max)
            {
                max = sub_max;
                index = sub_i;
            }
    }

    t_parallel = omp_get_wtime() - t_start;

    free(vector);

    printf("\nm_critical : %d\n", max);
    printf("i_critical : %d\n", index);

    statistic_log(t_serial, t_parallel, NTHREADS);

    return 0;
}