
#include "child.h"

Child::Child(int size, int rank) {
    this -> rank = rank;
    this -> size = size;

    task_loop();
}

void Child::task_loop() {

    file.open("primes.txt", ios::app);

    // While we are not finished..
    while (true) {

        // ..receive work to do from master..
        MPI_Recv(&input, 2, MPI_INT, 0, 99, MPI_COMM_WORLD, MPI_STATUS_IGNORE);  

        // ..if received 0, exit operation..
        if (input[1] == 0)
            break;

        // ..fancy debugger..
        cout << input[0] << endl;

        // ..Generate primes.
        find_primes(input[0], input[0] + step);      

    }
 
    file.close();

}

void Child::find_primes(int start, int end) {

    // Special behavior for if the start is 0, or even.
    // Since we don't need to check evens, the counter goes
    // up 2 at a time, so we make sure the first one is 
    // odd. 
    if (start == 0) {
        file << 1 << endl << 2 << endl;
        start = 3;
    } else if (start % 2 == 0) {
        start = start + 1;
    }

    while (start < end) {
        if (isPrime(start)) {
            // Don't want to write any primes
            // greater than the target. 
            if (start > target)
                break;
            file << start << endl;
        }
        start += 2;
    }

}

bool Child::isPrime(int n) {
    for (int i = 3; i < n; i += 2)
        if (n % i == 0) return false;
    return true;
}