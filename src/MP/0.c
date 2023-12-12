#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../../lib/headers/generators.h"

int main(int argc, char const *argv[])
{
    int NTHREADS = omp_get_num_procs() / 2;
    
    double t_start, t_serial, t_parallel;

    // Serial

    t_start = omp_get_wtime();

    t_serial = omp_get_wtime() - t_start;

    // Parallel

    t_start = omp_get_wtime();

    t_parallel = omp_get_wtime() - t_start;

    statistic_log("PARALLEL", t_serial, t_parallel, 1);

    return 0;
}