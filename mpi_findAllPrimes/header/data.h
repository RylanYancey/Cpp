
#pragma once

#include <iostream>
using namespace std;

#include "mpi.h"

const int step = 10000;
const int target = 1000000;

/*
    Each `Data` in existence corresponods to a Child
    Rank. Contains the Request and the methods to work
    with it. By default, the parent will always try to
    have an open send request. 
*/
class Data {
public:
    
    Data(int size, int rank);

    // Update all open send requests.
    bool update(int & progress);

    // Send an exit code to each child process. 
    void kill();

    int rank;

private:

    // This request is NULL when there is no open
    // send request. 
    MPI_Request send;

    int size;

};