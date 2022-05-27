
#include "parent.h"

Parent::Parent(int size) {
    this -> size = size;

    // Declare one Data for every rank. 
    for (int i = 1; i < size; i++)
        requests.push_back(std::move(Data(size, i)));

    task_loop();
}

void Parent::task_loop() {

    // While we have not reached the target...
    while (true) {
        // ...Iterate through every Data...
        for (int i = 0; i < requests.size(); i++) {
            auto & temp = requests[i];
            // ...Update its send request...
            if (temp.update(progress))
                // ...if we have reached the target, exit the loop. 
                goto label;
        }
    }
    label:

    exit_protocol();

}

void Parent::exit_protocol() {

    // For every Data...
    for (int i = 0; i < requests.size(); i++) {
        auto & temp = requests[i];
        // ...kill the process by sending an exit code. 
        temp.kill();
    }
}