
#include "secondary.h"

Secondary::Secondary(int rank, int size) {
    this -> rank = rank;
    this -> size = size;

    for (int i = 0; i < buf_size; i++)
        buffer[i] = 0;

    task_loop();
}

void Secondary::task_loop() {

    while(true) {

        int data[3];
        MPI_Recv(&data, 3, MPI_INT, 0, 99, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        if (data[2] == 0)
            break;

        find_primes(data[0], data[0] + data[1]);

        MPI_Send(buffer, buf_size, MPI_INT, 0, 99, MPI_COMM_WORLD);

        for (int i = 0; i < buf_size; i++)
            buffer[i] = 0;

    }

}

void Secondary::find_primes(int start, int end) {
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

bool Secondary::isPrime(int n) {
    for (int i = 3; i < n; i += 2)
        if (n % i == 0) return false;

    return true;
}
