
// stl
#include <iostream>
#include <fstream>
#include <chrono>
using namespace std;

// libraries
#include "mpi.h"

// local
#include "child.h"
#include "parent.h"

double t1;
double t2;

int main(int argc, char* argv[]) {

    ofstream file;
    file.open("primes.txt");
    file.close();

    MPI_Init(&argc, &argv);
    MPI_Status status;

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
        t1 = MPI_Wtime();

    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
        Parent parent(size);
    else
        Child child(size, rank); 

    if (rank == 0) {
        t2 = MPI_Wtime();
    }

    MPI_Finalize();

    if (rank == 0) 
        printf("Runtime = %f\n", t2 - t1);

}