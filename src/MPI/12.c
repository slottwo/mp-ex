#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

int *gera_vetor(int n);

int main()
{
    // Iniciando MPI.h
    int nprocs, rank;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;

    if (nprocs > 2 && rank == 0)
    {
        printf("The number of processes needs to be 2\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    // Iniciando Time.h
    time_t t;
    srand(time(NULL) * rank);

    /*
    INICIO
    */

    int *vector;
    int *sub_vector = (int *)malloc(nprocs * sizeof(int));
    int sub_n = MAX / nprocs;
    float media, var, desvio;

    if (rank == 0)
    {
        vector = gera_vetor(MAX);
    }


    MPI_Scatter(vector, sub_n, MPI_INT, sub_vector, sub_n,
                MPI_INT, 0, MPI_COMM_WORLD);
    


    /*
    FIM
    */

    MPI_Finalize();
    return 0;
}

int *gera_vetor(int n)
{
    int *vetor;
    int i;
    vetor = (int *)malloc(sizeof(int) * n);
    for (i = 0; i < n; i++)
    {
        int num = (rand() % (MAX + 1));
        vetor[i] = num;
        printf("%d ", num);
    }
    printf("\n\n");
    return vetor;
}
