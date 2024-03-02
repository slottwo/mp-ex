/**
 * @file 0.c
 * @author slottwo (41028091+slottwo@users.noreply.github.com)
 * @brief Binary Parity
 * @version 0.3
 * @date 2024-02-29
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <mpi.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000000000

/**
 * @brief It fills a binary array randomly
 *
 * @param array
 * @param size
 */
void gen(bool *array, int size);

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

    bool *v = (bool *)malloc(sizeof(bool) * N);
    if (rank == 0)
        gen(v, N);

    double t_init;
    if (rank == 0)
        t_init = MPI_Wtime();

    /*
    INICIO
    */

    MPI_Bcast(v, N, MPI_C_BOOL, 0, MPI_COMM_WORLD);

    bool next_bit;
    int count = 0, file_ones;
    for (bool *i = v + rank; i < v + N; i += nprocs)
        count += *i;

    MPI_Reduce(&count, &file_ones, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
        next_bit = file_ones % 2;

    /*
    FIM
    */

    if (rank == 0)
    {
        printf("New bit: '%d'\n", next_bit);
        printf("Δt: %f\n", MPI_Wtime() - t_init);
    }

    free(v);

    MPI_Finalize();
    return 0;
}

void gen(bool *array, int size)
{
    for (bool *i = array; i < array + size; i++)
        *i = rand() % 2;
}
