#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

int main()
{
    // Iniciando MPI.h
    int nprocs, rank;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;

    /*
    INICIO
    */

    static long n_step = 500000000;
    double dx = 1.0 / (double)n_step;

    int i;
    double x, pi, sum = 0.;

    for (i = rank; i < n_step; i += nprocs)
    {
        x = (i + 0.5) * dx;
        sum += 4.0 / (1.0 + x * x);
    }

    pi = sum * dx;

    double PI;
    MPI_Reduce(&pi, &PI, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    // double t_start = MPI_Wtime();

    // printf("t: %.5fs\n", MPI_Wtime() - t_start);

    if (rank == 0)
    {
        printf("pi: %0.5f\n", PI);
    }

    /*
    FIM
    */

    MPI_Finalize();
    return 0;
}
