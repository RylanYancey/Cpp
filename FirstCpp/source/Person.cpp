
#include <iostream>

#include "Person.h"

Person::Person(string name, int age) {
    this -> name = name;
    this -> age = age;
}

string Person::getName() {
    return name;
}

int Person::getAge() {
    return age;
}

void Person::introduce() {
    cout << "Hello my name is " << name << 
    " and I am " << age << " years old." << endl;
}
