
#include "prime_seq.h"

PrimeSeq::PrimeSeq(unsigned int n) {
    if (n == 0 || n == 1 || n == 2 || n == 3) this -> n = 2;
    else if (n % 2 == 0) this -> n = n - 1;
    else this -> n = n - 2;
}

PrimeSeq::PrimeSeq() {
    n = 2;
}

unsigned int PrimeSeq::next() {
    if (n == 2) {
        n == 1;
        return 2;
    }

    do { n += 2; } while (!isPrime(n));
    return n;
}

bool PrimeSeq::isPrime(unsigned int n) {
    for (int i = 3; i < n; i++)
        if (n % i == 0) return false;

    return true;
}

void PrimeSeq::allPrimesBetween(unsigned int primes[], unsigned int start, unsigned int end) {

    int index = 0;

    if (start == 0) {
        primes[0] = (unsigned int) 1;
        primes[1] = (unsigned int) 2;
        index = 2; 
        n = 3;
    }
    else if (start % 2 == 0)
        n = start + 1;
    else n = start;

    while (n < end) {
        if (isPrime(n)) {
            primes[index] = n;
            index++;
        } 
        n += 2;
    }
}