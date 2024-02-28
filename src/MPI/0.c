/**
 * @file 0.c
 * @author slottwo (41028091+slottwo@users.noreply.github.com)
 * @brief Source code model for parallel computing programs using MPI
 * @version 0.3
 * @date 2024-02-27
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000000

/**
 * @brief It fills a array with random values between 0 and 1
 *
 * @param array
 * @param size
 */
void gen(double *array, int size);

int main()
{
    // Iniciando MPI.h
    int nprocs, rank;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;

    // Iniciando Time.h
    srand(time(NULL) * rank);

    double *v = (double *)malloc(sizeof(double) * N);
    if (rank == 0)
        gen(v, N);

    double t_init;
    if (rank == 0)
        t_init = MPI_Wtime();

    /*
    INICIO
    */

    /*
    FIM
    */

    if (rank == 0)
        printf("Δt: %f\n", MPI_Wtime() - t_init);

    free(v);

    MPI_Finalize();
    return 0;
}

void gen(double *array, int size)
{
    for (int i = 0; i < size; i++)
        array[i] = (rand() / (double)RAND_MAX);
}
