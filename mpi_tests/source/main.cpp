
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <chrono>
#include <thread>
using namespace std;

#include "mpi.h"

int main(int argc, char* argv[]) {

    MPI_Init(&argc, &argv);
    MPI_Status status;

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    ofstream file;
    #pragma ompi master
    {
        file.open("hi.txt", fstream::app);
        file << rank << endl;
        file << rank << endl;
        file << rank << endl;
        file << rank << endl;
        file << rank << endl;
        file.close();
    }

    MPI_Finalize();

}

