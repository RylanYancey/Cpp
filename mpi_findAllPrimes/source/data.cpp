
#include "data.h"

Data::Data(int size, int rank) {
    this -> size = size;
    this -> rank = rank;

    send = NULL;
}

/*
    returns FALSE until progress >= target. 
    if this function returns TRUE, all work has been done
    and the process can now exit. 
*/
bool Data::update(int & progress) {

    // if the request is NULL, there is no 
    // Active send request. Create a new one and..
    if (send == NULL) {
        MPI_Request sr;
        send = sr;
        int buf[] = {progress, 1};
        MPI_Isend(&buf, 2, MPI_INT, rank, 99, MPI_COMM_WORLD, &send);
        // ..be sure to update the progress.
        progress += step;
        // If progress is >= target, we have reached
        // our goal and can exit the process. 
        return progress >= target;
    }

    // if send != NULL, we know there is an open send request, and we
    // test if it has been fulfilled..
    int isSent = false;
    MPI_Test(&send, &isSent, MPI_STATUS_IGNORE);

    // .. if it has, we set send to NULL to signify
    // job completion. 
    if (isSent) {
        send = NULL;
    }

    return false;

}

void Data::kill() {
    
    // Let each Child know the goal has been reached. 
    int exit_code[] = {0, 0};
    MPI_Send(&exit_code, 2, MPI_INT, rank, 99, MPI_COMM_WORLD);

}