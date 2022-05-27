
#pragma once

#define step100k 8686
#define step1m 72382
#define step10k 1086
#define step1k 145

#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

#include "mpi.h"

// Constants to dictate how the child works. 
const int step = 100000;
const int target = 10000000;

// equal to step / ln(step) - can't be known at compile time.
const int buf_size = step100k;
/*
    A Workspace / Container for Receive Requests. 
*/
class Data {
public:

    Data(int size, int rank);

    // Update Send & Receive Requests.
    bool update(int & progress);

    /*  Kill the children by sending 
        an exit code to them, telling them
        to stop working. */
    void kill();

    // counts how many times this rank was called. 
    int work_done;

    // our "ID". 
    int rank;

private:

    /*  If there is no open Recieve Request (receive is null), 
        Create a new one. Else, test if any data has been sent. */
    bool update_receive();

    /* If there is no open Send Request (send in NULL),
        Create a new one. Else, test if the data was received. */
    void update_send(int & progress);

    // If a request is NULL, there is no open request. 

    MPI_Request receive;
    MPI_Request send;

    // Writes prime numbers to primes.txt.
    ofstream writer;

    // Receives primes from child process. 
    int buffer[buf_size];

    int size;

};