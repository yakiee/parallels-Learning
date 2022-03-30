#include <stdio.h>
#include <mpi.h>

int main()
{
    int num;
    int comm_size, my_rank;
    int count = 0;
    MPI_Status status_p;

    MPI_Init(0, 0);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    for (int i = 1; i < comm_size; i++)
    {
        if (my_rank == i)
        {
            num = i;
            // printf(">>rank: %d\tnum: %d\n", my_rank, num);
        }
    }

    if (my_rank != 0)
    {
        MPI_Send(&num, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    else
    {
        MPI_Recv(&num, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status_p);
        MPI_Get_count(&status_p, MPI_INT, &count);
    }
    printf("rank: %d\tnum: %d\ttag: %d\n", my_rank, num, count);

    MPI_Finalize();

    return 0;
}
