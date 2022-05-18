
#pragma once

#include <string>

using namespace std;

class Person {
private:
    string name;
    int age;
public:
    Person();
    Person(string name, int age);
    string getName();
    int getAge();
    void setName(string name);
    void setAge(int age);
    void introduce();
};