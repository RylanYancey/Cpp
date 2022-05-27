
#include "data.h"

Data::Data(int size, int rank) {
    this -> size = size;
    this -> rank = rank;

    send = NULL;
}

bool Data::update(int & progress) {

    if (send == NULL) {
        MPI_Request sr;
        send = sr;
        int buf[] = {progress, 1};
        MPI_Isend(&buf, 2, MPI_INT, rank, 99, MPI_COMM_WORLD, &send);
        progress += step;
        return progress >= target;
    }

    int isSent = false;
    MPI_Test(&send, &isSent, MPI_STATUS_IGNORE);

    if (isSent) {
        send = NULL;
    }

    return false;

}

void Data::kill() {

    int exit_code[] = {0, 0};
    MPI_Send(&exit_code, 2, MPI_INT, rank, 99, MPI_COMM_WORLD);

}