
#pragma once

#include <iostream>
using namespace std;

#include "mpi.h"

const int step = 10000;
const int target = 1000000;

class Data {
public:
    
    Data(int size, int rank);

    bool update(int & progress);

    void kill();

    int rank;

private:

    MPI_Request send;

    int buf[1];

    int size;

};