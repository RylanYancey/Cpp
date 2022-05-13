
#include <string>

using namespace std;

class Person {
private:
    string name;
    int age;
public:
    Person(string name, int age);
    string getName();
    int getAge();
    void introduce();
};
