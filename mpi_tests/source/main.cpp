
#include <iostream>
using namespace std;

#include "mpi.h"

const int step = 100;
const int target = 1050;
const int buf_size = step / 4;

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

int main(int argc, char* argv[]) {

    MPI_Init(&argc, &argv);
    MPI_Status status;

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    cout << rank << endl;

    if (rank == 0)
    {
        int send[2] = {0, 0};
        MPI_Request send_req;
        MPI_Isend(&send, 2, MPI_INT, 1, 99, MPI_COMM_WORLD, &send_req);

        Data dat = Data();
        MPI_Irecv(&dat.primes, buf_size, MPI_INT, 1, 99, MPI_COMM_WORLD, &dat.req);

        while (true) {
            int isTrue = false;
            MPI_Test(&send_req, &isTrue, MPI_STATUS_IGNORE);

            if (isTrue) {
                cout << "Sent" << endl;
                break;
            }
        }

        cout << "transition" << endl;

        while(true) {
            int isTrue2 = false;
            MPI_Test(&dat.req, &isTrue2, MPI_STATUS_IGNORE);

            if (isTrue2) {
                cout << dat.primes[0] << endl;
                break;
            }
        }

    }
    else
    {
        int recv[2];
        MPI_Recv(&recv, 2, MPI_INT, 0, 99, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        int send[buf_size];
        for (int i = 0; i < buf_size; i++)
            send[i] = 500;

        MPI_Send(&send, buf_size, MPI_INT, 0, 99, MPI_COMM_WORLD);
        
        cout << "Finished Secondary Job" << endl;
    }

    cout << "Finalizing" << endl;

    MPI_Finalize();

}

