
#pragma once

#include <iostream>
using namespace std;

#include "mpi.h"

#include "data.h"

class Child {
public:

    Child(int size, int rank);

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