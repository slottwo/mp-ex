#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10

int *gera_vetor(int n);

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
    srand(time(NULL));

    /*
    INICIO
    */

    int *V;
    int N = MAX;
    int n = MAX % nprocs == 0 ? MAX / nprocs : MAX / nprocs + 1;
    if (rank == 0)
    {
        printf("n: %d\n", n); // return 0;
    }
    int *v = (int *)malloc(n * sizeof(int));
    float mean, s², s;

    if (rank == 0)
    {
        V = gera_vetor(MAX);
    }

    MPI_Scatter(V, n, MPI_INT, v, n, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < nprocs; i++)
    {
        if (rank == i)
        {
            printf("Rank %d:\n", i);
            for (int j = 0; j < n; j++)
            {
                if ((N - n * (i - 1)) - n - j > 0)
                {
                    printf(" %d", v[j]);
                }
            }
            printf("\n");
        }
        MPI_Barrier(MPI_COMM_WORLD);
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
