
#include <iostream>

#include "BinaryTree.h"

using namespace std;

int main() {
    
    BinaryTree bint = BinaryTree();
    bint.insert(20, Person("Rylan", 21));
    bint.insert(10, Person("Jared", 42));
    bint.insert(30, Person("Ammar", 20));
    bint.insert(40, Person("Will", 19));
    bint.insert(35, Person("Ned", 25));

    bint.display();

    return 0;
}
