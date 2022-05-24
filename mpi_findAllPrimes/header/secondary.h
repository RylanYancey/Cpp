
#pragma once

#include <iostream>
using namespace std;

#include "data.h"

#include "mpi.h"

class Secondary {
public:
    Secondary(int rank, int size);
private:

// Instance Functions

    void task_loop();

    void find_primes(int start, int end);

    bool isPrime(int n);

// Instance Variables

    int buffer[buf_size];

    int rank;
    int size;
    
};