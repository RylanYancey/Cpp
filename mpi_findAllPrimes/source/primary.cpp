
#include "primary.h"

Primary::Primary(int size) {
    this -> size = size;
    file.open("primes.txt");
}

void Primary::task_loop() {

    while (true) {
        if (!update_sends() && !update_requests()) break; 
    }

    for (int i = 1; i < size; i++) {
        req_it = requests.find(i);
        MPI_Request_free(&req_it -> second.req);
        requests.erase(i);
        send_it = sends.find(i);
        MPI_Request_free(&send_it -> second);
        sends.erase(i);
    }

    for (int i = 1; i < size; i++) {
        int data[3] {0, 0, 0};
        MPI_Send(&data, 3, MPI_INT, i, 99, MPI_COMM_WORLD);
    }

    file.close();

}

bool Primary::update_requests() {
    int isRecieved = false;
    for (int i = 1; i < size; i++) {

        req_it = requests.find(i);

        if (req_it == requests.end()) 
        {
            MPI_Request request;
            Data data = Data(request);
            MPI_Irecv(&data.primes, buf_size, MPI_INT, i, 99, MPI_COMM_WORLD, &data.req);
            requests.insert({i, data});
            continue;
        }

        Data & dat = req_it -> second;
        MPI_Test(&dat.req, &isRecieved, MPI_STATUS_IGNORE);

        if (isRecieved) {
            for (int i = 0; i < buf_size; i++) {
                if (dat.primes[i] == 0) break;
                if (dat.primes[i] > target) {
                    return false;
                    requests.erase(i);
                }
                file << dat.primes[i] << endl;
            }
            requests.erase(i);
        }

    }

    return true;
}

bool Primary::update_sends() {
    int isSent = false;
    for (int i = 1; i < size; i++) {

        if (progress >= target)
            return false;

        send_it = sends.find(i);

        if (send_it == sends.end()) {
            MPI_Request request;
            int data[] = {progress, step, 1};
            MPI_Isend(&data, 3, MPI_INT, i, 99, MPI_COMM_WORLD, &request);
            sends.insert({i, request});
            progress += step;
            continue;
        }

        MPI_Request & req = send_it -> second;
        MPI_Test(&req, &isSent, MPI_STATUS_IGNORE);

        if (isSent) {
            sends.erase(i);
        }

    }

    return true;
}
