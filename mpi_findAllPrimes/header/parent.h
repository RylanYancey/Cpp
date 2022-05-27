
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

    // Task Loop only stops executing when Data::update() returns true. 
    void task_loop();

    // Wrap it up, people. 
    void exit_protocol();

    // One Data for every rank. 
    vector<Data> requests;

    // The starting point for every child. Iterated by
    // step in Data::update();
    int progress = 0;

    int size;

};