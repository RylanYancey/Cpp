
#include <iostream>
#include <vector>

using namespace std;

class PrimeSeq {
public:
    PrimeSeq(unsigned int n);
    PrimeSeq();
    unsigned int next();
    void allPrimesBetween(unsigned int primes[], unsigned int start, unsigned int end);
private:
    unsigned int n;
    bool isPrime(unsigned int n);
};