#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000000

/**
 * @brief Returns a array of random values between 0 and 1
 * 
 * @param size 
 * @return double* 
 */
double *gen(int size);

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

    /*
    FIM
    */

    if (rank == 0)
        printf("Δt = %.3f ms", (MPI_Wtime() - t_init) * 1000);

    MPI_Finalize();
    return 0;
}

double *gen(int size)
{
    double *v;
    v = (double *)malloc(sizeof(double) * size);

    for (int i = 0; i < size; i++)
    {
        double num = (rand() / (double)RAND_MAX);
        v[i] = num;
    }

    return v;
}
