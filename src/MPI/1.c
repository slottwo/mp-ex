/**
 * @file 1.c
 * @author slottwo (41028091+slottwo@users.noreply.github.com)
 * @brief 
 * @version 0.1
 * @date 2024-02-22
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define N 1000000

int main()
{
    // Iniciando MPI.h
    int nprocs, rank;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;

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
        printf("Δt = %.3f ms", (MPI_Wtime() - t_init) * 1000);

    MPI_Finalize();
    return 0;
}
