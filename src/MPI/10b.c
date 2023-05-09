#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10

float *gera_vetor(int n);

int main()
{
    // Iniciando MPI.h
    int nprocs, rank;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;

    // Iniciando Time.h
    // time_t t;
    // srand(time(NULL) * rank);

    /*
    INICIO
    */

    double t_start = MPI_Wtime();

    if (nprocs < 3)
        return 1;

    float *v = (float *)malloc(MAX * sizeof(float));
    float sum = 0;

    if (rank == 0)
    {
        v = gera_vetor(MAX);
        MPI_Bcast(v, MAX, MPI_FLOAT, 0, MPI_COMM_WORLD);
        MPI_Recv(&sum, 1, MPI_FLOAT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("sum_1: %0.5f\n", sum);
        MPI_Recv(&sum, 1, MPI_FLOAT, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf((sum < 10) ? "sum_2: %0.5f\n" : "sum_2: %0.4f\n", sum);
        printf("time: %.5fs\n", MPI_Wtime() - t_start);
    }
    else
    {
        MPI_Bcast(v, MAX, MPI_FLOAT, 0, MPI_COMM_WORLD);
        for (int i = 0; i < MAX; i++)
        {
            sum += v[i];
        }
        sum *= rank;
        MPI_Send(&sum, 1, MPI_FLOAT, 0, 0, MPI_COMM_WORLD);
    }
    /*
    FIM
    */

    MPI_Finalize();
    return 0;
}

float *gera_vetor(int n)
{
    time_t t;
    srand((unsigned)time(&t));

    float *vetor;
    int i;
    vetor = (float *)malloc(sizeof(float) * n);
    for (i = 0; i < n; i++)
    {
        vetor[i] = (rand() / (float)RAND_MAX);
        printf("%f\n", vetor[i]);
    }
    return vetor;
}
