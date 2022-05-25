
// stl
#include <stack>
#include <iostream>
#include <fstream>

// libraries
#include "mpi.h"

// local
#include "primary.h"
#include "secondary.h"

int main(int argc, char* argv[]) {

    MPI_Init(&argc, &argv);
    MPI_Status status;

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    cout << rank << endl;

    // split between primary and secondary. 
    if (rank == 0)
        Primary primary = Primary(size);
    else
        Secondary secondary = Secondary(rank, size);

    MPI_Finalize();

}