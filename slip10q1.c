#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000

int main(int argc, char *argv[])
{
    int rank, size;
    int data[N];
    int local_sum = 0, total_sum = 0;
    float average;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int chunk = N / size;

    if (rank == 0)
    {
        srand(time(NULL));
        for (int i = 0; i < N; i++)
            data[i] = rand() % 100;

        printf("Generated 1000 random numbers.\n");
    }

    int *sub_data = (int *)malloc(chunk * sizeof(int));

    MPI_Scatter(data, chunk, MPI_INT,
                sub_data, chunk, MPI_INT,
                0, MPI_COMM_WORLD);

    for (int i = 0; i < chunk; i++)
        local_sum += sub_data[i];

    printf("Process %d local sum = %d\n", rank, local_sum);

    MPI_Reduce(&local_sum, &total_sum, 1, MPI_INT,
               MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        average = (float)total_sum / N;

        printf("\nTotal Sum = %d\n", total_sum);
        printf("Average = %.2f\n", average);
    }

    free(sub_data);
    MPI_Finalize();

    return 0;
}
