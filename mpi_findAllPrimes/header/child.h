
#pragma once

#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

#include "mpi.h"

#include "data.h"

class Child {
public:

    Child(int size, int rank);

private:

// Instance Functions

    // Contains a loop that only stops
    // when an exit code is received. 
    void task_loop();

    // Finds and writes all indicated primes to 
    // the file specified in the task loop. 
    void find_primes(int start, int end);

    // Returns true if n is prime. 
    bool isPrime(int n);

// Instance Variables

    // the file we want to write to.
    ofstream file;

    // The work we have to do, received from
    // the parent. 
    int input[2] = {0, 0};

    int rank;
    int size;

};