
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

    // Open and close the file to remove all
    // previously generated primes.
    ofstream file;
    file.open("primes.txt");
    file.close();

    MPI_Init(&argc, &argv);
    MPI_Status status;

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Get the time before work
    if (rank == 0)
        t1 = MPI_Wtime();

    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
        // Parent Manages the work of the Children
        Parent parent(size);
    else
        // Each child does work. 
        Child child(size, rank); 

    // get the time after work
    if (rank == 0) {
        t2 = MPI_Wtime();
    }

    MPI_Finalize();

    // print the amount of time it took
    // for the program to end. 
    if (rank == 0) 
        printf("Runtime = %f\n", t2 - t1);

}