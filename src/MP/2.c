#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../../lib/headers/generators.h"

int main(int argc, char const *argv[])
{
    int NTHREADS = omp_get_num_procs() / 2;
    
    int *v = (int*)malloc(SIZE*sizeof(int));
    gen_vector_int(v, 0, MAX, SIZE);

    double t_start, t_serial, t_parallel;

    // Serial

    t_start = omp_get_wtime();

    t_serial = omp_get_wtime() - t_start;

    // Parallel

    t_start = omp_get_wtime();

    t_parallel = omp_get_wtime() - t_start;

    statistic_log(t_serial, t_parallel, NTHREADS);

    return 0;
}