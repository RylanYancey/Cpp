# Questions for Dr. Skjellum - Part 1

## Questions from "Parallel And High Performance Computing" book.

1. Is it true to say "Computers are much faster at computation than managing memory?"

2. When do memory-intensive applications benefit from parallelism?

3. Page xxix - "If you load one value, you get eight or sixteen." - This seems to indicate mamory is allocated 512 bits at a time. What does this mean for performance optomization?

4. Page 7 - "Thus, a 256 bit-wide vector unit can execute ... " What is a Vector Unit?

## MPI Questions

1. In my code mpi_isprime, are there any inefficiencies?

2. In the code, MPI_Send and MPI_Recv is Blocking, correct? (when MPI_Recv is called, it will wait for the corresponding MPI_Send)
