#include <iostream>

#include "../header/Person.h"

Person::Person() {
    name = "invalid";
    age = -1;
}

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

void Person::setName(string name) {
    this -> name = name;
}

void Person::setAge(int age) {
    this -> age = age;
}

void Person::introduce() {
    cout << "Hello my name is " << name << 
    " and I am " << age << " years old." << endl;
}