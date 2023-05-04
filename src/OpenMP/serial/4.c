#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../../lib/headers/generators.h"

int main(int argc, char const *argv[])
{
    int n = gen_int(1, 100000000);
    printf("%d\n");

    long int sum = 0;

    double t_start = omp_get_wtime();

    for (int i = 1; i <= n; i++)
    {
        if (n % i == 0)
        {
            printf("%d ", i);
            sum += i;
        }
    }

    printf("\nt: %.6fs\n", omp_get_wtime() - t_start);

    printf("sum: %d\n", sum);

    return 0;
}
