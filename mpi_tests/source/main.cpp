
#include <iostream>
using namespace std;

#include "mpi.h"

int main(int argc, char* argv[]) {

    MPI_Init(&argc, &argv);
    MPI_Status status;

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        int message[] {1, 1};
        MPI_Send(&message, 2, MPI_INT, 1, 99, MPI_COMM_WORLD);
    }
    else
    {
        int message[] {0, 0};
        MPI_Recv(&message, 2, MPI_INT, 0, 99, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    MPI_Finalize();

}

