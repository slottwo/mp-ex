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

- Quais variáveis são compartilhadas entre as threads, e quais são privadas ?

*/

int main(int argc, char const *argv[])
{
    gen_init();

    int NTHREADS = omp_get_num_procs() / 2;

    double t_start, t_serial, t_critical, t_static, t_dynamic;

    unsigned long long int sum = 0;
    unsigned long long int num = gen_int(MIN, __INT_MAX__);

    // Serial

    t_start = omp_get_wtime();

    t_serial = omp_get_wtime() - t_start;

    // Critical

    t_start = omp_get_wtime();

#pragma omp parallel num_threads(NTHREADS)
    {
    }

    t_critical = omp_get_wtime() - t_start;

    // Static

    t_start = omp_get_wtime();

#pragma omp parallel num_threads(NTHREADS)
    {
    }

    t_static = omp_get_wtime() - t_start;

    // Dynamic

    t_start = omp_get_wtime();

#pragma omp parallel num_threads(NTHREADS)
    {
    }

    t_dynamic = omp_get_wtime() - t_start;

    double bonus = (t_serial / t_dynamic - 1) * 100;

    printf("\nlog:\n");
    printf("num_thread : %d\n", NTHREADS);
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