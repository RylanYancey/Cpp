
#include "parent.h"

Parent::Parent(int size) {
    
    ofstream file;
    file.open("primes.txt");
    file.close();

    this -> size = size;

    for (int i = 1; i < size; i++) 
        requests.push_back(std::move(Data(size, i)));

    task_loop();

}

void Parent::task_loop() {
    while (true) {
        for (int i = 0; i < requests.size(); i++) {
            if (requests.at(i).update(progress)) 
                goto label;
        }
    }
    label:
    exit_protocol();
}

void Parent::exit_protocol() {
    cout << "Begin Exit Protocol" << endl;

    for (int i = 0; i < requests.size(); i++)
        requests.at(i).kill();

    for (int i = 0; i < requests.size(); i++)
        cout << "Rank " << requests.at(i).rank << " solved " 
            << requests.at(i).work_done << " steps." << endl;

    return;

}
