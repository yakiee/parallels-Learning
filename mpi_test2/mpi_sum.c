#include <stdio.h>
#include <mpi.h>

int main()
{
    int sum = 0;
    int comm_size, my_rank;
    int msg[][5] = {{1, 10}, {2, 20}, {3, 30}};
    int num, count;

    MPI_Init(0, 0);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    for (int i = 1; i <= 3; i++)
    {
        if (my_rank == i)
        {
            num = msg[i - 1][0];
            count = msg[i - 1][1];
        }
    }

    if (my_rank != 0)
    {
        MPI_Send(&num, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        MPI_Send(&count, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
    }
    else
    {
        for (int i = 1; i < comm_size; i++)
        {
            MPI_Recv(&num, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(&count, 1, MPI_INT, i, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            sum += count;
        }
    }

    printf("rank: %d\tnum: %d\tsum: %d\n", my_rank, num, sum);
    MPI_Finalize();

    return 0;
}
