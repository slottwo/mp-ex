#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../../lib/headers/generators.h"

int main(int argc, char const *argv[])
{
    int NTHREADS = omp_get_num_procs() / 2;

    int n = gen_int(1, 100000000);
    printf("%d\n");

    // Serial

    long int sum = 0;
    long int sum_aux = 0;
    double t_start = omp_get_wtime();

    for (int i = 1; i <= n; i++)
    {
        if (n % i == 0)
        {
            printf("%d ", i);
            sum += i;
        }
    }

    double t_serial = omp_get_wtime() - t_start;
    printf("sum: %d\n", sum);

    // Critical

    sum = 0;
    t_start = omp_get_wtime();

#pragma omp parallel for num_threads(NTHREADS) private(sum)
    for (int i = 1; i <= n; i++)
    {
        if (n % i == 0)
        {
            printf("%d ", i);
            sum += i;
        }
    }
    double t_critical = omp_get_wtime() - t_critical;
    printf("sum_critical: %d\n", sum);

    printf("\nt_serial: %.6fs\n", t_serial);
    printf("\nt_critical: %.6fs\n", t_critical);

    return 0;
}
