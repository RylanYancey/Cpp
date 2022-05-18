#include <iostream>

#include "BinaryTree.h"

using namespace std;

void test1() {
    BinaryTree* bint = new BinaryTree();

    bint -> insert(10, Person("Jared", 42));
    bint -> insert(30, Person("Ammar", 20));
    bint -> insert(20, Person("Rylan", 21));
    bint -> insert(40, Person("Will", 19));
    bint -> insert(35, Person("Ned", 25));

    cout << "after insert" << endl;
    bint -> display();

    BinaryTree bint2 = *bint; 

    bint -> map([=](Person p, int k) {
        p.setName("Bob");
        return p;
    });

    if (bint2.contains(20))
        cout << endl << "bint2 contains key 20" << endl;
    else
        cout << "bint2 doeos not contain key 20" << endl;

    if (bint2.contains(50)) 
        cout << "bint2 contains key 50" << endl;
    else
        cout << "bint2 does not contain key 50" << endl << endl;

    cout << "after map" << endl;
    bint -> display();

    cout << "copied bint" << endl;
    bint2.display();

    cout << endl << "deleting bint manually" << endl << endl;
    delete bint;

    cout << endl << "bint2 is stack allocated, so the destructor is implicitly called once it is out of scope: " << endl << endl;
}

int main() {
    test1();
    return 0;
}
