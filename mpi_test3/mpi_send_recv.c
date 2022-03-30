#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int sum = 0, num = 0;
    int comm_size, my_rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    // printf("%s\t%s\t%s\t%d\n", argv[0], argv[1],argv[2], argc);
    for (int i = 1; i <= atoi(argv[1]); i++)
    {
        if (i % 3 + 1 == my_rank)
        {
            num += i;
        }
    }

    if (my_rank != 0)
    {
        MPI_Send(&num, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        //(传值， 大小， 类型， 目标地址， 标签， 通信子（指定通信范围）)
    }
    else
    {
        for (int i = 1; i < comm_size; i++)
        {
            MPI_Recv(&num, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            //(传值， 大小， 类型， 原地址， 标签， 通信子（指定通信范围），Ignore(一般情况))

            sum += num;
        }
    }

    printf("rank: %d\tsum: %d\n", my_rank, sum);
    MPI_Finalize();

    return 0;
}
