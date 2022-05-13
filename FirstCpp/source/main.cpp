
#include <iostream>
#include <string>
#include <vector>

#include "Person.h"

using namespace std;

int main() {

    vector<Person> people;

    people.push_back(Person("Rylan", 21));
    people.push_back(Person("Jared", 30));
    people.push_back(Person("Ned", 20));
    people.push_back(Person("Will", 20));

    for (auto p : people) {
        p.introduce();
    }
    
}
