
#include "data.h"

Data::Data(int size, int rank) {
    this -> size = size;
    this -> rank = rank;

    receive = NULL;
    send = NULL;
    
    targetMet = false;

    for (int i = 0; i < buf_size; i++)
        buffer[i] = 0;

};

bool Data::update(int & progress) {

    update_send(progress);
    return update_receive();

}

void Data::update_send(int & progress) {

    if (progress > target)
        return;

    if (send == NULL) {
        MPI_Request sr;
        send = sr;
        int buf[] = {progress, 1};
        MPI_Isend(&buf, 2, MPI_INT, rank, 99, MPI_COMM_WORLD, &send);
        progress += step;
        return;
    }

    int isSent = false;
    MPI_Test(&send, &isSent, MPI_STATUS_IGNORE);

    if (isSent) {
        send = NULL;
    }

}

bool Data::update_receive() {

    if (receive == NULL) {
        MPI_Request rr;
        receive = rr;
        MPI_Irecv(&buffer, buf_size, MPI_INT, rank, 99, MPI_COMM_WORLD, &receive);
        return false;
    }

    int isRecv = false;
    MPI_Test(&receive, &isRecv, MPI_STATUS_IGNORE);

    if (isRecv) {
        receive = NULL;
        cout << buffer[0] << endl;
        writer.open("primes.txt", fstream::app);

        for (int i = 0; i < buf_size; i++) {
            if (buffer[i] == 0) break;
            if (buffer[i] > target) {
                writer.close();
                return true;
            }
            writer << buffer[i] << endl;
            buffer[i] = 0;
        }

        writer.close();
    }

    return false;
}

void Data::receive_noprocess() {
    MPI_Recv(&buffer, buf_size, MPI_INT, rank, 99, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    return;
}

void Data::kill() {

    if (receive != NULL)
        MPI_Request_free(&receive);

    if (send != NULL)
        MPI_Request_free(&send);

    int buf[] = {0, 0};
    MPI_Send(&buf, 2, MPI_INT, rank, 99, MPI_COMM_WORLD);

    cout << rank << endl;
}

