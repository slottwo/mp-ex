#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10000

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
    int *sub_vector = (int *)malloc(sizeof(int) * MAX / 2);
    int *sums_vector = (int *)malloc(sizeof(int) * 2);

    if (rank == 0)
    {
        vector = gera_vetor(MAX);
    }

    MPI_Scatter(vector, MAX / 2, MPI_INT, sub_vector, MAX / 2,
                MPI_INT, 0, MPI_COMM_WORLD);

    int sum = 0;
    for (int i = 0; i < (MAX / 2); i++)
    {
        sum += sub_vector[i];
    }

    if (rank < 2)
        printf("Sum[%d]: %d\n", rank, sum);

    MPI_Gather(&sum, 1, MPI_INT, sums_vector, 1,
               MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        int sum = sums_vector[0] + sums_vector[1];
        printf("Sum: %d\n", sum);
    }

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
