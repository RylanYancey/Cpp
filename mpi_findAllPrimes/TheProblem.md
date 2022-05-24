
# What this program does

## PRIMARY

Primary is the "Parent" of all other tasks.

It manages all "Secondary" tasks. 

Primary is designed to do this in a Non-Blocking fashion, using MPI_Irecv and MPI_Isend. 

Primary will create an Isend and Irecv for every task, and store its request in an unordered_map until it is finished. 

When Primary recieves data, it writes every non-zero value into primes.txt. 

## SECONDARY

Secondary is the "Child" of Primary. 

Secondary using the Blocking "MPI_Send" and "MPI_Recv" to recieve and send input. 

Secondary will calculate all primes and write them to a buffer according to the instruction sent by Primary, and then send them back to Primary. 

# The Problem

Sometimes, the buffer of primes sent to Primary is empty. You can see this in primes.txt. After every recieve, a \n is pushed to the file. Where there is extra empty space in primes.txt, there is an empty buffer. 

I've verified that the buffer is not empty Secondary-side for every time, but it does not seem to make it to Primary.

This is possibly becuase of the way I'm storing the data in the unordered_map requests?