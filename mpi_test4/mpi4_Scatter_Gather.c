#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int comm_size, myRank;
    int *x, *rec_x = NULL;
    int *y, *rec_y = NULL;
    int *z;
    int *total;
    int n, rec_n;
    int local_n;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

    if (myRank == 0)
    {
        printf("输入n: ");
        fflush(stdout);
        scanf("%d", &n);
        x = (int *)malloc(n * sizeof(int));
        y = (int *)malloc(n * sizeof(int));

        printf("输入X向量: ");
        fflush(stdout);
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &x[i]);
        }
        printf("输入Y向量: ");
        fflush(stdout);
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &y[i]);
        }
    }

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    //分发数据（指针），数据量，数据类型，源进程rank，comm
    local_n = n / comm_size;
    if (myRank != 0)
    {
        x = (int *)malloc(n * sizeof(int));
        y = (int *)malloc(n * sizeof(int));
    }
    rec_x = (int *)malloc(n * sizeof(int));
    rec_y = (int *)malloc(n * sizeof(int));
    MPI_Scatter(x, local_n, MPI_INT, rec_x, local_n, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(y, local_n, MPI_INT, rec_y, local_n, MPI_INT, 0, MPI_COMM_WORLD);
    //发送缓冲区数据（指针），数据量，数据类型，在缓冲区的接收指针，接收数据类型，资源进程rank，comm


    z = (int *)malloc(n * sizeof(int));
    total = (int *)malloc(n * sizeof(int));
    memset(z, 0, n * sizeof(int));
    for (int j = 0; j < n; j++)
    {
        z[j] = rec_x[j] + rec_y[j];
        printf("2. rank: %d\trec_x: %d\n", myRank, rec_x[j]);
    }

    MPI_Gather(z, local_n, MPI_INT, total, local_n, MPI_INT, 0, MPI_COMM_WORLD);
    //发送缓冲区数据（指针），数据量，数据类型，在缓冲区的接收指针，接收数据类型，目的进程rank，comm

    if (myRank == 0)
    {
        for (int i = 0; i < n; i++)
            printf("rank: %d\ttotal: %d\n", myRank, total[i]);
    }
    MPI_Finalize();
    return 0;
}