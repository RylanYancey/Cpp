
#include "parent.h"

#include <fstream>

Parent::Parent(int size) {
    
    ofstream file;
    file.open("primes.txt");
    file.close();

    this -> size = size;

    for (int i = 1; i < size; i++)
        requests.push_back(Data(size, i));

    task_loop();

}

void Parent::task_loop() {
    while (true) {
        for (int i = 0; i < requests.size(); i++) {
            if (requests.at(i).update(progress)) {
                for (int k = i; k < requests.size(); k++)
                    requests.at(k).receive_noprocess();
                goto label;
            }
        }
    }
    label:
    exit_protocol();
}

void Parent::exit_protocol() {
    cout << " Exit Protocol " << endl;

    for (int i = 0; i < requests.size(); i++)
        requests.at(i).kill();

    return;

}