/**
 * @file 1.c
 * @author slottwo (41028091+slottwo@users.noreply.github.com)
 * @brief Program that calculates an approximation of π through a Riemamn sum with N installments
 * @version 0.1
 * @date 2024-02-22
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define N 1000000000

int main()
{
    // Iniciando MPI.h
    int nprocs, rank;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;

    double partial_π = 0, π, i, x, dx = 1.0 / N;

    double t_init;
    if (rank == 0)
        t_init = MPI_Wtime();

    /*
    INICIO
    */

    for (i = rank; i < N; i += nprocs)
    {
        x = (i + 0.5) * dx;
        partial_π += 4 / (1 + x * x);
    }

    partial_π *= dx;

    MPI_Reduce(&partial_π, &π, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    /*
    FIM
    */

    if (rank == 0)
    {
        double t_end = MPI_Wtime();
        printf(" π = %.10f...\n", π);
        printf("Δt = %.10f s\n", t_end - t_init);
    }

    MPI_Finalize();
    return 0;
}
