#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main()
{
    int comm_size, myRank;
    int *x;
    int *y;
    int *z;
    int *total;
    int n;

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
        total = (int *)malloc(n * sizeof(int));

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
    if (myRank != 0)
    {
        x = (int *)malloc(n * sizeof(int));
        y = (int *)malloc(n * sizeof(int));
    }
    MPI_Bcast(x, n, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(y, n, MPI_INT, 0, MPI_COMM_WORLD);

    z = (int *)malloc(n * sizeof(int));
    memset(z, 0, n * sizeof(int));
    for (int j = 0; j < n; j++)
    {
        if (j % 3 + 1 == myRank)
        {
            z[j] = x[j] + y[j];
            // printf("2. rank: %d\tz%d: %d\n", myRank, j, z[j]);
        }
    }

    if (myRank != 0)
        MPI_Reduce(z, NULL, n, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    else
        MPI_Reduce(z, total, n, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (myRank == 0)
    {
        for (int i = 0; i < n; i++)
            printf("rank: %d\ttotal: %d\n", myRank, total[i]);
    }
    MPI_Finalize();
    return 0;
}