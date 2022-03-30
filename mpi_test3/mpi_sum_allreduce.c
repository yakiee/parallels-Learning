#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int comm_size, my_rank;
    int sum = 0, total = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    for (int i = 1; i <= atoi(argv[1]); i++)
    {
        if (i % 3 + 1 == my_rank)
        {
            sum += i;
        }
    }

    MPI_Allreduce(&sum, &total, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    // if (my_rank == 0)
    // {
        printf("rank: %d\ttotal: %d\n", my_rank, total);
    // }
    MPI_Finalize();

    return 0;
}