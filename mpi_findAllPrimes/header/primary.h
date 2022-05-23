
#include <iostream>
#include <fstream>
#include <unordered_map>
using namespace std;

#include "mpi.h"

#include "data.h"

struct Data {
    MPI_Request req;
    int primes[buf_size];
    Data(MPI_Request request) {
        this -> req = request;
        for (int i = 0; i < buf_size; i++)
            primes[i] = 0;
    }
};

class Primary {
public:
    Primary(int size);
private:

// Functions

    void task_loop();

    bool update_requests();

    bool update_sends();

// Instance variables

    ofstream file;

    unordered_map<int, Data> requests;
    unordered_map<int, Data>::iterator req_it = requests.begin();

    unordered_map<int, MPI_Request> sends;
    unordered_map<int, MPI_Request>::iterator send_it = sends.begin();

    int rank = 0;
    int size;

    int progress = 0;

};