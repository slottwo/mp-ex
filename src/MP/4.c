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

    t_serial = omp_get_wtime() - t_start;

    // Parallel

    t_start = omp_get_wtime();

#pragma omp parallel num_threads(NTHREADS)
    {
    }

    t_parallel = omp_get_wtime() - t_start;

    statistic_log(t_serial, t_parallel, NTHREADS);

    return 0;
}