#include <omp.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../lib/gen.h"

#define MAX 9999
#define SIZE 500000

int main(int argc, char const *argv[])
{
    int NTHREADS = omp_get_num_procs() / 2;

    int *v = (int *)malloc(SIZE * sizeof(int));
    gen_vector_int(v, 0, MAX, SIZE);

    int target = gen_int(0, MAX);
    printf("target: %d\n", target);

    double t_start, t_serial, t_parallel;

    int count = 0;

    // Serial

    t_start = omp_get_wtime();

    for (int i = 0; i < SIZE; i++)
    {
        if (v[i] == target)
            count++;
    }

    t_serial = omp_get_wtime() - t_start;

    // End

    printf("count: %d\n", count);

    count = 0;

    // Parallel

    t_start = omp_get_wtime();

#pragma omp parallel num_threads(NTHREADS)
    {
#pragma omp for reduction(+ : count)
        for (int i = 0; i < SIZE; i++)
        {
            if (v[i] == target)
                count++;
        }
    }

    t_parallel = omp_get_wtime() - t_start;

    // End

    printf("count: %d\n", count);

    statistic_log(t_serial, t_parallel, NTHREADS);

    return 0;
}