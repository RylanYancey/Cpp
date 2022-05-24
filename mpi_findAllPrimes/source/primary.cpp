
#include "primary.h"

Primary::Primary(int size) {
    this -> size = size;

    // open the text file that will
    // contain the primes.
    file.open("primes.txt");

    // Launch the tasks
    task_loop();
}

// Contains the loop.
void Primary::task_loop() {

    // Loop will continue running until
    // both update_sends() and update_requests() return
    // false. They will return false only when the target is reached. 
    while (true) {
        // Note: update_sends will always finish BEFORE update_requests.
        // update_sends may return false more than once, but update_requests will
        // return only once. 
        if (!update_sends() && !update_requests()) break; 
    }

    // by the time we get here, we know all secondaries have completed and are
    // currently waiting for input. 

    exit_protocol();

}

// Actions to be performed when the target is reached. 
void Primary::exit_protocol() {

    file.close();

    // For all of primarys' requests and sends,
    // Free all MPI_Requests.
    // Erase all data. 
    for (int i = 1; i < size; i++) {
        req_it = requests.find(i);
        MPI_Request_free(&req_it -> second.req);
        requests.erase(i);

        send_it = sends.find(i);
        MPI_Request_free(&send_it -> second);
        sends.erase(i);
    }

    // at this point, all of the secondaries are waiting to
    // recieve, so we send them '0' in data[2] to let them know to complete. 
    for (int i = 1; i < size; i++) {
        int data[3] {0, 0, 0};
        MPI_Send(&data, 3, MPI_INT, i, 99, MPI_COMM_WORLD);
    }

}

// Primary will always try to have an open request for every
// task available in the world. 
bool Primary::update_requests() {
    int isRecieved = false;
    
    // for every rank...
    for (int i = 1; i < size; i++) {

        // set the iterator to the rank index..
        req_it = requests.find(i);

        // if the index does not exist as a key,
        // it points to end...
        if (req_it == requests.end()) 
        {
            // ...so we create a new recieve request and store it
            // in requests, then continue the loop. 
            MPI_Request request;
            Data data = Data(request);
            MPI_Irecv(&data.primes, buf_size, MPI_INT, i, 99, MPI_COMM_WORLD, &data.req);
            requests.insert({i, data});
            continue;
        }

        // else, we get the data from requests and check
        // if the recieve has completed...
        Data & dat = req_it -> second;
        MPI_Test(&dat.req, &isRecieved, MPI_STATUS_IGNORE);

        // ...if it has, then write all the primes to the text file. 
        if (isRecieved) {
            for (int i = 0; i < buf_size; i++) {
                // Since the amount of primes is unknown, the buffer may be larger than
                // the amount of primes. If we reach a zero, we know we're at the end
                // of the buffer and can break. 
                if (dat.primes[i] == 0) break;
                // once the primes are greater than target,
                // we know we've reached the end. 
                if (dat.primes[i] > target) {
                    return false;
                    requests.erase(i);
                }
                file << dat.primes[i] << endl;
            }
            requests.erase(i);
            file << endl;
        }

    }

    // Everything completed without reaching
    // the target. 
    return true;
}

// Primary will always try to have an open send for every
// task available in the world. 
bool Primary::update_sends() {
    int isSent = false;

    // for every rank...
    for (int i = 1; i < size; i++) {

        // ...if we reach the target, return false. 
        if (progress >= target)
            return false;

        // point the iterator to the target rank.
        send_it = sends.find(i);

        // if the index does not exist as a key,
        // it points to end...
        if (send_it == sends.end()) {
            // ...then create an Isend and store its request in sends. 
            MPI_Request request;
            int data[] = {progress, step, 1};
            MPI_Isend(&data, 3, MPI_INT, i, 99, MPI_COMM_WORLD, &request);
            sends.insert({i, request});
            // add step to progress to keep moving upward. 
            progress += step;
            continue;
        }

        // ...else, retrieve our request from sends and 
        // test if it was recieved by the task. 
        MPI_Request & req = send_it -> second;
        MPI_Test(&req, &isSent, MPI_STATUS_IGNORE);

        // ..if it was, erase it from the list. 
        if (isSent) {
            sends.erase(i);
        }

    }

    // The process completed without reaching
    // the target. 
    return true;
}
