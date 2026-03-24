#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000

int main(int argc, char *argv[])
{
    int rank, size;
    int data[N];
    int local_max, global_max;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int chunk = N / size;

    if (rank == 0)
    {
        srand(time(NULL));
        for (int i = 0; i < N; i++)
            data[i] = rand() % 1000;  

        printf("Generated 1000 random numbers.\n");
    }

    int *sub_data = (int *)malloc(chunk * sizeof(int));

    MPI_Scatter(data, chunk, MPI_INT,
                sub_data, chunk, MPI_INT,
                0, MPI_COMM_WORLD);

    local_max = sub_data[0];
    for (int i = 1; i < chunk; i++)
    {
        if (sub_data[i] > local_max)
            local_max = sub_data[i];
    }

    printf("Process %d local max = %d\n", rank, local_max);

    MPI_Reduce(&local_max, &global_max, 1, MPI_INT,
               MPI_MAX, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        printf("\nMaximum number = %d\n", global_max);
    }

    free(sub_data);
    MPI_Finalize();

    return 0;
}
