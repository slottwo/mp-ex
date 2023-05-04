#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

float *gerar_vetor(int n);

int main()
{
    // Iniciando MPI.h
    int nprocs, rank;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;

    // Iniciando Time.h
    time_t t;
    srand(time(NULL) * rank);

    /*
    INICIO
    */

    /*
    FIM
    */

    MPI_Finalize();
    return 0;
}

float *gerar_vetor(int n)
{
    float *vetor;
    int i;
    vetor = (float *)malloc(sizeof(float) * n);
    for (i = 0; i < n; i++)
    {
        float num = (rand() / (float)RAND_MAX);
        vetor[i] = num;
    }
    return vetor;
}
