
#include <functional>

#include "Person.h"

// Node struct for containing the data. 
struct Node {
    // The node to the left of this node. 
    Node* left;
    // the node to the right of this node. 
    Node* right;
    // The value this node contains. 
    Person value;
    int key;
    Node(Person p, int key) {
        value = p;
        this -> key = key;

        left = nullptr;
        right = nullptr;
    }
};

class BinaryTree {
public:
    // - Constructors & Operator Overloads / Rule of 3 - //

    // constructor
    BinaryTree();
    // copy constructor
    BinaryTree(const BinaryTree &bt);
    // destructor
    ~BinaryTree();
    // copy assignment operator
    BinaryTree & operator=(BinaryTree &rhs);

    // - Public methods for interfacing with the tree - //

    // Inserts a Node into the tree
    void insert(int key, Person value);
    // Searches the tree for a node and returns its value
    Person search(int key);
    // displays every value in the tree on the command line.
    void display();
    // How many nodes the tree has. 
    int length();
    // Checks if a key exists within the tree.
    bool contains(int key);
    // Maps the function by value. 
    void map(function < Person(Person, int) > lambda);

private:
    // - Instance Variables - // 

    Node* root;
    int len;

    // - Private methods for internal use or recursion - //

    void insertRec(int key, Person value, Node* root);
    Person searchRec(int key, Node* root);
    void displayRec(Node* root);
    void deleteAllRec(Node* root);
    void copyAllRec(Node* root);
    void mapRec(function < Person(Person, int) > lambda, Node* root);

};