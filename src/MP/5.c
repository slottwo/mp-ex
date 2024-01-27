#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../lib/gen.h"

#define MIN 1000000000

/*

Atividade 4.

1. Escreva um programa em C, com OpenMP, que dado um número maior do que um
bilhão, calcular a soma de todos os seus divisores.

- Utilize os métodos:

  - Explicitando uma região crítica

  - Redução com for estático

  - Redução com for dinâmico

- Quais variáveis são compartilhadas entre as threads, e quais são privadas?

*/

int main(int argc, char const *argv[])
{
    gen_init();

    int NTHREADS = omp_get_num_procs() / 2;

    double t_start, t_serial, t_critical, t_static, t_dynamic;

    unsigned long long int sum = 0;
    unsigned long long int num = gen_int(MIN, __INT_MAX__);

    printf("       num : %llu\n\n", num);

    // Serial

    t_start = omp_get_wtime();

    for (int i = 1; i <= num; i++)
        if (num % i == 0)
            sum += i;

    t_serial = omp_get_wtime() - t_start;

    printf("  s_serial : %llu\n", sum);

    // Critical

    sum = 0;

    t_start = omp_get_wtime();

#pragma omp parallel num_threads(NTHREADS)
    {
        for (int i = omp_get_thread_num() + 1; i <= num; i += NTHREADS)
            if (num % i == 0)
            {
#pragma omp critical
                sum += i;
            }
    }

    t_critical = omp_get_wtime() - t_start;

    printf("s_critical : %llu\n", sum);

    // Static

    sum = 0;

    t_start = omp_get_wtime();

#pragma omp parallel num_threads(NTHREADS)
    {
#pragma omp for schedule(static) reduction(+ : sum)
        for (int i = 1; i <= num; i++)
            if (num % i == 0)
                sum += i;
    }

    t_static = omp_get_wtime() - t_start;

    printf("  s_static : %llu\n", sum);

    // Dynamic

    sum = 0;

    t_start = omp_get_wtime();

#pragma omp parallel num_threads(NTHREADS)
    {
#pragma omp for schedule(dynamic) reduction(+ : sum)
        for (int i = 1; i <= num; i++)
            if (num % i == 0)
                sum += i;
    }

    t_dynamic = omp_get_wtime() - t_start;

    printf(" s_dynamic : %llu\n", sum);

    double bonus = (t_serial / t_dynamic - 1) * 100;

    printf("\n\tmulti-log\n");
    printf("  n_thread : %d\n", NTHREADS);
    printf("  t_serial : %.4f\n", t_serial);

    printf("\nt_critical : %.4f\n", t_critical);
    printf("\t   speedup : %.4f\n", t_serial / t_critical);
    printf("\tefficiency : %.3f %%\n", 100.0 * (t_serial / t_critical) / (double)NTHREADS);

    printf("\nt_static : %.4f\n", t_static);
    printf("\t   speedup : %.4f\n", t_serial / t_static);
    printf("\tefficiency : %.3f %%\n", 100.0 * (t_serial / t_static) / (double)NTHREADS);

    printf("\nt_dynamic : %.4f\n", t_dynamic);
    printf("\t   speedup : %.4f\n", t_serial / t_dynamic);
    printf("\tefficiency : %.3f %%\n", 100.0 * (t_serial / t_dynamic) / (double)NTHREADS);

    return 0;
}