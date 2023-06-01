#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100000

int *gen_bin(int n);

/*
Desenvolva um programa paralelo (com p processadores) para verificar a paridade
de um arquivo binário (considere um vetor binário).
Ou seja, verifique o numero de 0’s e 1’s existentes no arquivo e adicione um 0
ou um 1 ao arquivo de tal forma que o número de 1’s seja par.
*/

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

    int *b, ones = 0;

    if (!rank) {
        b = gen_bin(MAX);
    }
    
    MPI_Bcast(b, MAX, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < MAX; i++)
    {
        ones += b[i];
    }

    b = realloc(b, sizeof(int) * (MAX + 1));
    b[MAX] = ones % 2;

    /*
    FIM
    */

    MPI_Finalize();
    return 0;
}

int *gen_bin(int n)
{
    int *vetor = (int *)malloc(sizeof(int) * n);
    int i;
    for (i = 0; i < n; i++)
    {
        vetor[i] = rand() % 2;
    }
    return vetor;
}
