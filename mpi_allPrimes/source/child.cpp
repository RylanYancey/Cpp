
#include "child.h"

Child::Child(int size, int rank) {
    this -> rank = rank;
    this -> size = size;

    // clear garbage data.
    for (int i = 0; i < buf_size; i++)
        buffer[i] = 0;

    task_loop();
}

void Child::task_loop() {

    while(true) {

        // recieve data from Primary
        int data[2];
        MPI_Recv(&data, 2, MPI_INT, 0, 99, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // exit code 0
        if (data[2] == 0)
            break;

        // calculate all primes.
        find_primes(data[0], data[0] + step);

        // Send data back to primary. 
        MPI_Send(&buffer, buf_size, MPI_INT, 0, 99, MPI_COMM_WORLD);

        // clear the buffer
        for (int i = 0; i < buf_size; i++)
            buffer[i] = 0;

    }

    return;

}

// Verified working. 
void Child::find_primes(int start, int end) {
    int index = 0;
    if (start == 0) {
        buffer[0] = 1;
        buffer[1] = 2;
        start = 3;
        index = 2;
    }
    else if (start % 2 == 0)
        start += 1;

    while (start < end) {
        if (isPrime(start)) {
            buffer[index] = start;
            index++;
        }
        start += 2;
    }

}

bool Child::isPrime(int n) {
    for (int i = 3; i < n; i += 2)
        if (n % i == 0) return false;

    return true;
}
