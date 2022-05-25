
#include <iostream>
using namespace std;

#include "mpi.h"

#include "parent.h"
#include "child.h"

int main(int argc, char* argv[]) {

    MPI_Init(&argc, &argv);
    MPI_Status status;

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
        Parent parent(size);
    else
        Child child(size, rank);

    MPI_Finalize();

}