#include <omp.h>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int NTHREADS = omp_get_num_procs() / 2;

    int N = 50000;
    int v[N];
    int v_sum = N * (N - 1) / 2;
    double d, S, E = v_sum / N;

    for (int i = 0; i < N; i++)
    {
        v[i] = i;
    }

    // Serial

    S = 0; // standard deviation

    double t_start = omp_get_wtime();

    for (int i = 0; i < N; i++)
    {
        d = i - E;
        S += d * d;
    }

    S /= N;

    double s = sqrt(S); // variance

    double t_serial = omp_get_wtime() - t_start;

    printf("serial:\t%f\n", s);

    // Parallel

    t_start = omp_get_wtime();

    S = 0;

#pragma omp parallel for num_threads(NTHREADS) private(d) reduction(+:S)
    for (int i = 0; i < N; i++)
    {
        d = i - E;
        S += d * d;
    }

    S /= N;

    s = sqrt(S);

    double t_parallel = omp_get_wtime() - t_start;

    printf("parallel:\t%f\n", s);
}