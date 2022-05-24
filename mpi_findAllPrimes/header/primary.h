
#pragma once

#include <iostream>
#include <fstream>
#include <unordered_map>
using namespace std;

#include "mpi.h"

#include "data.h"

// Contains the data for a recieve request.
struct Data {
    MPI_Request req;
    int primes[buf_size];
    // the constructor instantiates primes[] and
    // overrides the garbage data with zeroes. 
    Data() {
        for (int i = 0; i < buf_size; i++)
            primes[i] = 0;
    }
};

class Primary {
public:
    Primary(int size);
private:

// Functions

    /*  Contains the loop that only stops
        when the target is reached */
    void task_loop();

    /*  Contains the process for wrapping up 
        the program when the target is reached. */
    void exit_protocol();

    // Recieves incoming data from secondary tasks. 
    bool update_requests();

    // Sends outgoing data to secondary tasks. 
    bool update_sends();

// Instance variables

    // The file we will write all the primes to. 
    ofstream file;

    // Stores all MPI_Requests associated with an int (rank) 
    // the requests are for all incoming recieves. 
    unordered_map<int, Data> requests;
    unordered_map<int, Data>::iterator req_it = requests.begin();

    // Stores all MPI_Requests associated with an int (rank)
    // These requests are for all the outgoing sends. 
    unordered_map<int, MPI_Request> sends;
    unordered_map<int, MPI_Request>::iterator send_it = sends.begin();

    // rank and size of the 
    // MPI_COMM_WORLD
    int rank = 0;
    int size;

    // represents how many primes have been generated. 
    int progress = 0;

};