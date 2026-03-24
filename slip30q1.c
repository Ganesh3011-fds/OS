#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000

int main(int argc, char *argv[])
{
    int rank, size;
    int data[N];
    int local_min, global_min;

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

    local_min = sub_data[0];
    for (int i = 1; i < chunk; i++)
    {
        if (sub_data[i] < local_min)
            local_min = sub_data[i];
    }

    printf("Process %d local min = %d\n", rank, local_min);

    MPI_Reduce(&local_min, &global_min, 1, MPI_INT,
               MPI_MIN, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        printf("\nMinimum number = %d\n", global_min);
    }

    free(sub_data);
    MPI_Finalize();

    return 0;
}
