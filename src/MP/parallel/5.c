#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../../../lib/headers/generators.h"

int main(int argc, char const *argv[])
{
    int *v = (int *)malloc(SIZE * sizeof(int));
    gen_vector_int(v, 0, 1000);

    int count_of_target = 0;
    int target = 555;

    double t_start = omp_get_wtime();

    for (int i = 0; i < SIZE; i++)
    {
        if (v[i] == target)
        {
            count_of_target++;
        }
    }

    double t_serial = omp_get_wtime() - t_start;
    printf("serial time:\t%.5fs\n", t_serial);

    printf("amount:\t\t%d\n", count_of_target);

    count_of_target = 0;

    int NTHREADS = omp_get_num_threads() / 2;

    t_start = omp_get_wtime();

#pragma omp parallel for num_threads(NTHREADS)
    for (int i = 0; i < SIZE; i++)
    {
        if (v[i] == target)
        {
            count_of_target++;
        }
    }
    double t_parallel = omp_get_wtime() - t_start;
    printf("parallel time:\t%.5fs\n", t_parallel);

    printf("amount:\t\t%d\n", count_of_target);

    printf("speedup:\t%.4f\n", t_serial / t_parallel);
    printf("efficiency:\t+%.2f%%\n", (t_serial / t_parallel - 1) * 100);
    return 0;
}