/**
 * @file 0.c
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
#include <time.h>

#define N 1000

/**
 * @brief Returns a array of random values between 0 and 1
 *
 * @param v Double vector
 * @param size Size of v
 */
void gen(double *v, int size);

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

    double t_init;
    if (rank == 0)
        t_init = MPI_Wtime();

    /*
    INICIO
    */

    double *v = (double *)malloc(sizeof(double) * N), s = 0;

    if (rank == 0)
        gen(v, N);

    MPI_Bcast(v, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    switch (rank)
    {
    case 0:
        MPI_Recv(&s, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("1: %f\n", s);

        MPI_Recv(&s, 1, MPI_DOUBLE, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("2: %f\n", s);

        break;

    case 1:
        for (int i = 0; i < N; i++)
            s += v[i];

        MPI_Send(&s, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
        break;

    case 2:
        for (int i = 0; i < N; i++)
            s += v[i];

        s *= 2;
        MPI_Send(&s, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
        break;

    default:
        break;
    }

    /*
    FIM
    */

    if (rank == 0)
    {
        printf("\nΔt: %f\n", MPI_Wtime() - t_init);
    }

    free(v);

    MPI_Finalize();
    return 0;
}

void gen(double *v, int size)
{
    for (int i = 0; i < size; i++)
    {
        double num = (rand() / (double)RAND_MAX);
        v[i] = num;
    }
}
