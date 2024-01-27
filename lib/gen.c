#include <omp.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "gen.h"

int __GEN_INITIALIZED__ = 0;

/**
 * @brief Init random seed (should be called only once)
 *
 */
void gen_init()
{
    if (__GEN_INITIALIZED__ == 0)
    {
        time_t t;
        srand((unsigned)time(&t));
        __GEN_INITIALIZED__ = 1;
    }
    else
    {
        printf("GEN_C Error: srand is already initalized\n");
    }
}

/**
 * @brief Fill a vector with random floating point values
 *
 * @param v Allocated vector
 * @param size Vector length
 * @param min Minimum value
 * @param max Maximum value
 */
void gen_vector(double *v, int size, double min, double max)
{
    int NTHREADS = omp_get_num_procs();

#pragma omp parallel num_threads(NTHREADS)
    {
#pragma omp for
        for (int i = 0; i < size; i++)
            v[i] = min + (max - min) * (rand() / (double)RAND_MAX);
    }
}

/**
 * @brief Fill a vector with random floating point values ​​between `0` and `1`
 *
 * @param v Allocated vector
 * @param size Vector length
 */
void gen_vector_zto(double *v, int size)
{
    int NTHREADS = omp_get_num_procs();

#pragma omp parallel num_threads(NTHREADS)
    {
#pragma omp for
        for (int i = 0; i < size; i++)
            v[i] = (rand() / (double)RAND_MAX);
    }
}

/**
 * @brief Fill a vector with random integer values
 *
 * @param v Allocated vector
 * @param size Vector length
 * @param min Minimum value
 * @param max Maximum value
 */
void gen_vector_int(int *v, int size, int min, int max)
{
    int NTHREADS = omp_get_num_procs();

#pragma omp parallel num_threads(NTHREADS)
    {
#pragma omp for
        for (int i = 0; i < size; i++)
            v[i] = rand() % (max - (min - 1)) + min;
    }
}

/**
 * @brief Gen a random integer value
 *
 * @param min Minimum value
 * @param max Maximum value
 * @return `int` – Generated value
 */
int gen_int(int min, int max)
{
    return rand() % (max - (min - 1)) + min; // don't modify parentheses
}

/**
 * @brief Gen a random floating point between `0` and `max`
 *
 * @param max Maximum value
 * @return `double` – Generated value
 */
double gen_rand(double max)
{
    return (rand() / (double)RAND_MAX) * max;
}

void statistic_log(double t_serial, double t_parallel, int nthreads)
{
    double bonus = (t_serial / t_parallel - 1) * 100;

    printf("\nlog:\n");
    printf("  t_serial : %.4f\n", t_serial);
    printf("t_parallel : %.4f\n", t_parallel);
    printf("num_thread : %d\n", nthreads);
    printf("   speedup : %.4f\n", t_serial / t_parallel);
    printf("      diff : %.2f %%\n", bonus);
    printf("efficiency : %.3f %%\n", 100.0 * (t_serial / t_parallel) / (double)nthreads);
}
