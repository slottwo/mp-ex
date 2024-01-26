#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../lib/gen.h"

#define SIZE 1000000000
#define MIN 1
#define MAX 1000000

/*

Atividade 4.

2) Escreva um programa serial e paralelo em C, com OpenMP, que dado um vetor de
inteiros e um valor x, encontrar quantas vezes x ocorre no vetor. Calcular as
métricas de desempenho.

*/

int main(int argc, char const *argv[])
{
    gen_init();

    int count, target = gen_int(MIN, MAX);

    printf("target : %d\n", target);

    int *vector = (int *)malloc(sizeof(int) * SIZE);
    gen_vector_int(vector, SIZE, MIN, MAX);

    int NTHREADS = omp_get_num_procs() / 2;

    double t_start, t_serial, t_parallel;

    // Serial

    count = 0;

    t_start = omp_get_wtime();

    for (int i = 0; i < SIZE; i++)
        if (vector[i] == target)
            count++;

    t_serial = omp_get_wtime() - t_start;

    printf("count: %d\n", count);

    // Parallel

    count = 0;

    t_start = omp_get_wtime();

#pragma omp parallel num_threads(NTHREADS)
    {
#pragma omp for reduction(+ : count)
        for (int i = 0; i < SIZE; i++)
            if (vector[i] == target)
                count++;
    }

    t_parallel = omp_get_wtime() - t_start;

    printf("count: %d\n", count);

    statistic_log(t_serial, t_parallel, NTHREADS);

    free(vector);

    return 0;
}