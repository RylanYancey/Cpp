
#pragma once

#include <iostream>
#include <fstream>
using namespace std;

#include "mpi.h"

const int step = 1000;
const int target = 10050;
const int buf_size = step / 4;

class Data {
public:

    Data(int size, int rank);
    bool update(int & progress);
    void receive_noprocess();
    void kill();

    bool targetMet;

private:

    bool update_receive();
    void update_send(int & progress);

    MPI_Request receive;
    MPI_Request send;

    ofstream writer;

    int buffer[buf_size];

    int size;
    int rank;

};