
#include "parent.h"

Parent::Parent(int size) {
    this -> size = size;

    for (int i = 1; i < size; i++)
        requests.push_back(std::move(Data(size, i)));

    task_loop();
}

void Parent::task_loop() {

    while (true) {
        for (int i = 0; i < requests.size(); i++) {
            auto & temp = requests[i];
            if (temp.update(progress))
                goto label;
        }
    }
    label:

    exit_protocol();

}

void Parent::exit_protocol() {

    for (int i = 0; i < requests.size(); i++) {
        auto & temp = requests[i];
        temp.kill();
    }
}