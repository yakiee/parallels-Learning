// 2022.3.30
// 1 + 2 + 3 + ... + n（命令行参数）
//测试

#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

void main(int argc, char *argv[])
{
    int rank, size;
    int num = atoi(argv[1]);
    long long total = 0, sum = 0;
    double start, end;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    start = MPI_Wtime();
    for (int i = 1; i <= num; i++)
        if (i % 3 + 1 == rank)
            sum += i;

    printf("rank: %d\tsum: %lld\n", rank, sum);

    MPI_Reduce(&sum, &total, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
    end = MPI_Wtime();

    if (rank == 0)
        printf("rank: %d\ttotal: %lld\ttime: %f\n", rank, total, end - start);

    MPI_Finalize();
}