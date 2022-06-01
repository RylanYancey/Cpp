
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

// Program to find all the primes between 0 and target, (in data.h), where each thread is give step (also in data.h)
// amount of numbers to search every work cycle. 
// This program can brute force find find all the primes between 0 and 1,000,000 in 1.76 
// seconds when running on 50 cores with a step of 10000 on the Firefly cluster.
// To put that in perspective, a serial Rust program (is_prime folder), can
// find all those numbers in 152.46 seconds, an 86x speedup. 

int main(int argc, char* argv[]) {

    double t1;
    double t2;

    // Open and close the file to remove all
    // previously generated primes.
    ofstream file;
    file.open("primes.txt");
    file.close();

    MPI_Init(&argc, &argv);
    MPI_Status status;

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Barrier(MPI_COMM_WORLD);

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

    MPI_Barrier(MPI_COMM_WORLD);

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