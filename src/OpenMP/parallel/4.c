#include <omp.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../lib/headers/generators.h"

int main(int argc, char const *argv[])
{
    int NTHREADS = omp_get_num_procs() / 2;

    int n = gen_int(1, 100000000);
    printf("number: %d\n");

    // Serial

    long int sum = 0;
    double t_start = omp_get_wtime();

    for (int i = 1; i <= n; i++)
    {
        if (n % i == 0)
        {
            sum += i;
        }
    }

    double t_serial = omp_get_wtime() - t_start;
    printf("sum_serial: %d\n", sum);

    // Critical

    long int sum_aux = 0;

    sum = 0;
    t_start = omp_get_wtime();

#pragma omp parallel num_threads(NTHREADS) private(sum)
    {
#pragma omp for
        for (int i = 1; i <= n; i++)
        {
            if (n % i == 0)
            {
                sum_aux += i;
            }
        }
#pragma omp critical
        sum += sum_aux;
    }

    double t_critical = omp_get_wtime() - t_start;
    printf("sum_critical: %d\n", sum);

    // Reduction Static

    sum = 0;
    t_start = omp_get_wtime();

#pragma omp parallel num_threads(NTHREADS)
#pragma omp for reduction(+ \
                          : sum) schedule(static)
    for (int i = 1; i <= n; i++)
    {
        if (n % i == 0)
        {
            sum += i;
        }
    }

    double t_static = omp_get_wtime() - t_start;
    printf("sum_static: %d\n", sum);

    // Reduction Dynamic

    sum = 0;
    t_start = omp_get_wtime();

#pragma omp parallel num_threads(NTHREADS)
    {
#pragma omp for reduction(+ \
                          : sum) schedule(dynamic)
        for (int i = 1; i <= n; i++)
        {
            if (n % i == 0)
            {
                sum += i;
            }
        }
    }

    double t_dynamic = omp_get_wtime() - t_start;
    printf("sum_dynamic: %d\n", sum);

    printf("\nserial time: %.6fs\n", t_serial);
    printf("\n----------------\n\n");
    statistic_log("critical", 8, t_critical, t_serial, NTHREADS);
    printf("\n----------------\n\n");
    statistic_log("static", 6, t_static, t_serial, NTHREADS);
    printf("\n----------------\n\n");
    statistic_log("dynamic", 7, t_dynamic, t_serial, NTHREADS);

    return 0;
}
