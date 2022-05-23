
// stl
#include <stack>
#include <iostream>
#include <fstream>

// libraries
#include "mpi.h"

// local
#include "prime_seq.h"
#include "primary.h"
#include "secondary.h"

int main(int argc, char* argv[]) {

    MPI_Init(&argc, &argv);
    MPI_Status status;

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
        Primary primary = Primary(size);
    else
        Secondary secondary = Secondary(rank, size);

    MPI_Finalize();

}

/*
// stl
#include <stack>
#include <iostream>
#include <fstream>

// libraries
#include "mpi.h"

// local
#include "prime_seq.h"

int main(int argc, char* argv[]) {
    // - vars - //

    unsigned int step = 100;
    unsigned int const target = 1000;
    unsigned int const buf_size = step / 4;


    MPI_Init(&argc, &argv);
    MPI_Status status;

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    cout << "rank: " << rank << " size: " << size << endl;

    if (rank == 0) 
    {
        unsigned int current = 0;

        bool avail[size];
        for (int i = 1; i < size; i++)
            avail[i] = true;

        ofstream primes;
        primes.open("primes.txt");

        unsigned int temp[buf_size];
        for (int i = 0; i < buf_size; i++)
            temp[i] = 0;

        while (true) {
            for (int i = 1; i < size; i++) {

                // If the rank is not currently doing any work..
                if (avail[i] == true) {

                    // if we have gone over our target..
                    if (current + step >= target) 
                        // check if we have any leftovers..
                        if (current >= target) 
                            // if we do, we only need to check for recieves. 
                            continue;
                        else 
                            // if not, we only have the final task be the leftovers. 
                            step = target - current;

                    unsigned int data[3] = { current, step, 1 };
                    // Tell it to do work. 
                    MPI_Send(&data, 3, MPI_UNSIGNED, i, 99, MPI_COMM_WORLD);
                    // update avail and our task completion. 
                    avail[i] = false;
                    current += step;
                }
                // If the rank is currently doing work..
                else {
                    MPI_Request request;
                    
                    // receive either nothing or something. 
                    MPI_Irecv(&temp, buf_size, MPI_UNSIGNED, i, i, MPI_COMM_WORLD, &request);

                    // Figure out if our Irecv was successful..
                    int isDone;
                    MPI_Test(&request, &isDone, MPI_STATUS_IGNORE);

                    // if Irecv was successful..
                    if (isDone == 1) {

                        for (int k = 0; k < buf_size; k++) {
                            if (temp[k] != 0)
                                primes << temp[k] << endl;
                            else 
                                break;
                            temp[k] = 0;
                        }
                        avail[i] = true;
                    }
                    
                    MPI_Request_free(&request);
                    
                }
            }

            // check if everything is done
            if (current >= target) {
                bool allDone = true;
                for (int i = 0; i < size; i++)
                    if (avail[i] == false) {
                        allDone = false;
                        break;
                    }

                if (allDone == true)
                    break;
            }
        }

        primes.close();

        unsigned int data[3] = { 0, 0, 0 };
        for (int i = 1; i < size; i++) 
            MPI_Send(&data, 3, MPI_UNSIGNED, i, 99, MPI_COMM_WORLD);

    }
    else 
    {
        unsigned int primes[buf_size];
        for (int i = 0; i < buf_size; i++)
            primes[i] = 0;

        // current, step, exit_process?
        unsigned int data[3] = { 0, 0, 0 };

        PrimeSeq seq = PrimeSeq();

        while (true) {
            MPI_Recv(&data, 3, MPI_UNSIGNED, 0, 99, MPI_COMM_WORLD, &status);
            
            if (data[2] == 0) break;

            unsigned int end = data[0] + data[1];
            seq.allPrimesBetween(primes, data[0], end);

            MPI_Send(&primes, buf_size, MPI_UNSIGNED, 0, rank, MPI_COMM_WORLD);

            for (int i = 0; i < buf_size; i++)
                if (primes[i] == 0) break;
                else primes[i] = 0;
        }
    }

    MPI_Finalize();

    return EXIT_SUCCESS;
}

*/