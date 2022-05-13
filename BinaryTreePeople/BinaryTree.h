
#include "Person.h"

    struct Node {
        Node* left;
        Node* right;
        Person value;
        int key;
    };

class BinaryTree {
public:
    // Constructors / operator overloads
    BinaryTree() {}
    BinaryTree(const BinaryTree &bt) {}
    ~BinaryTree() {}
    BinaryTree & operator=(const BinaryTree &rhs);

    // public methods
    void insert(int key, Person value);
    Person search(int key);
    void display();

private:
    // instance variables
    Node* root;

    // Private methods for recursion
    void insertRec(int key, Person value, Node* root);
    Person searchRec(int key, Node* root);
    void displayRec(Node* root);

};
