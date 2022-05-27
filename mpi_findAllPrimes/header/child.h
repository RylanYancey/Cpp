
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

    void task_loop();

    void find_primes(int start, int end);

    bool isPrime(int n);

// Instance Variables

    ofstream file;

    int input[2] = {0, 0};
    int success[1] = {1};

    int rank;
    int size;

};