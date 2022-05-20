
#include <iostream>
#include <climits>

using namespace std;

#include "mpi.h"

int main( int argc, char *argv[]) {

    // unsigned long long target = 1000000000;
    unsigned long long target = 1000004249;
    unsigned long long step = 10000;
    unsigned long long times;
    
    // will update when a divisor is encountered. 
    int isPrime = 1;

    int rank;

    MPI_Status status;

    MPI_Init( &argc, &argv );
    MPI_Comm_rank( MPI_COMM_WORLD, &rank);

    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    /*
        if there are 4 ranks and step is 1000...

        rank 0 will run 0-999, 4000-4999, 9000-9999, so on.
        rank 1 will run 1000-1999, 5000-5999, 10000-10999, so on.
        rank 2 will run 2000-2999... you get the idea. 
        it runs in a cyclic, cyclic pattern. 
    */

    // "Times" is the number of times the loop is run * size
    times = (unsigned long long)rank;

    double t1 = MPI_Wtime();

    do {
        unsigned long long start = times * step;
        // 0 and 1 are not checked. 
        if (start == 0) start = 2;
        // start to start + step. 
        for (int i = start; i < start + step; i++) {
            // if divisible...
            if (target % i == 0) {
                // ...check if i is itself...
                if (i == target) continue;
                // ...print that we found a number and set isPrime to false. 
                cout << "Number is not prime! Divisible by: " << i <<  endl;
                isPrime = false;
            }
        }
        // increase times. 
        times += (unsigned long long)size;
    } while (!(times * step > target));

    double t2;

    // if rank 0..
    if (rank == 0) {
        // for every other process....
        for (int i = 1; i < size; i++) {
            int input;
            // recieve whether or not they found a prime...
            MPI_Recv(&input, 1, MPI_INT, i, 99, MPI_COMM_WORLD, &status);
            // if '0' then they encountered a divisor. Not prime. 
            if (input == 0) {
                isPrime = 0;
            }
        }
        // print result. 
        if (isPrime != 0) cout << target << " is prime!" << endl;
        else cout << target << " is not prime!" << endl;

        t2 = MPI_Wtime();
        cout << "Elapsed time is: " << t2 - t1 << endl;
    }
    else {
        MPI_Send(&isPrime, 1, MPI_INT, 0, 99, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}