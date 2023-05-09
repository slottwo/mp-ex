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

    double t_start = MPI_Wtime();

    for (i = rank; i < n_step; i += nprocs)
    {
        x = (i + 0.5) * dx;
        sum += 4.0 / (1.0 + x * x);
    }

    pi = sum * dx;

    double t_proc = MPI_Wtime() - t_start;
    printf("t_%d: %.5fs\n", rank, t_proc);

    double PI, t;
    MPI_Reduce(&pi, &PI, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    // MPI_Reduce(&t_proc, &t_total, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        t = MPI_Wtime() - t_start;
        printf("\nt: %.7fs\n", t);
        printf("pi: %0.7f\n", PI);

        // Serial

        sum = 0;

        t_start = MPI_Wtime();

        for (i = 0; i < n_step; i++)
        {
            x = (i + 0.5) * dx;
            sum += 4.0 / (1.0 + x * x);
        }

        pi = sum * dx;

        double t_serial = MPI_Wtime() - t_start;
        printf("\nt_s: %.5fs\n", t);
        printf("pi: %0.7f\n", pi);
        printf("speedup: %0.2f\n", t_serial / t);
        printf("eff.: %.5f\n", t_serial / t / nprocs);
    }

    /*
    FIM
    */

    MPI_Finalize();
    return 0;
}
