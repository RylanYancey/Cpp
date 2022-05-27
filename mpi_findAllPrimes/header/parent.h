
#pragma once

#include <iostream>
#include <vector>
using namespace std;

#include "mpi.h"

#include "data.h"
#include "child.h"

class Parent {
public:
    Parent(int size);

private:

    void task_loop();
    void exit_protocol();

    vector<Data> requests;

    int progress = 0;

    int size;

};