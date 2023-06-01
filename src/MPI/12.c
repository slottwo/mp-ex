#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 20

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
        printf("N: %d; n: %d\n", N, n); // return 0;
    }
    int *v = (int *)malloc(n * sizeof(int));
    double mean = 0;
    double mean_ = 0;
    double s², s;

    if (rank == 0)
    {
        printf("V: ");
        V = gera_vetor(MAX);
    }

    MPI_Scatter(V, n, MPI_INT, v, n, MPI_INT, 0, MPI_COMM_WORLD);

    int x = N - n * rank;
    for (int j = 0; j < n; j++)
    {
        if (x - j > 0)
        {
            mean_ += v[j];
            printf(" %d", v[j]);
        }
        else
            break;
    }

    MPI_Reduce(&mean_, &mean, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        mean /= N;
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
