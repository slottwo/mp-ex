/**
 * @file 0.c
 * @author slottwo (41028091+slottwo@users.noreply.github.com)
 * @brief Standart Deviation
 * @version 0.1
 * @date 2024-02-27
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <mpi.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000000000

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

    // Iniciando Time.h
    srand(time(NULL) * rank);

    double *X = (double *)malloc(sizeof(double) * N);
    if (rank == 0)
        gen(X, N);

    double t_init;
    if (rank == 0)
        t_init = MPI_Wtime();

    /*
    INICIO
    */

    MPI_Bcast(X, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    double Σ, μ, σ², σ;

    Σ = 0;
    for (double *i = X + rank; i < X + N; i += nprocs)
        Σ += *i;
    Σ /= N;

    MPI_Allreduce(&Σ, &μ, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

    Σ = 0;
    for (double *i = X + rank; i < X + N; i += nprocs)
        Σ += pow(*i - μ, 2);
    Σ /= N;

    MPI_Reduce(&Σ, &σ², 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
        σ = sqrt(σ²);

    /*
    FIM
    */

    if (rank == 0)
    {
        printf("σ: %.10f\n", σ);
        printf("Δt: %.9f\n", MPI_Wtime() - t_init);
    }

    free(X);

    MPI_Finalize();
    return 0;
}

void gen(double *array, int size)
{
    for (int i = 0; i < size; i++)
        array[i] = (rand() / (double)RAND_MAX);
}
