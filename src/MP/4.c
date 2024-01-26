#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../lib/gen.h"

#define MIN 1000000000

int main(int argc, char const *argv[])
{
    gen_init();

    int NTHREADS = omp_get_num_procs() / 2;

    double t_start, t_serial, t_parallel;

    unsigned long long int sum = 0;
    unsigned long long int num = gen_int(MIN, __INT_MAX__);

    // Serial

    t_start = omp_get_wtime();

    for (int i = 1; i <= num; i++)
        if (num % i == 0)
            sum += i;

    t_serial = omp_get_wtime() - t_start;

    printf("sum: %llu\n", sum);

    // Parallel

    sum = 0;

    t_start = omp_get_wtime();

#pragma omp parallel num_threads(NTHREADS)
    {
#pragma omp for
        for (int i = 1; i <= num; i++)
            if (num % i == 0)
            {
#pragma omp atomic
                sum += i;
            }
    }

    t_parallel = omp_get_wtime() - t_start;

    printf("sum: %llu\n", sum);

    statistic_log(t_serial, t_parallel, NTHREADS);

    return 0;
}