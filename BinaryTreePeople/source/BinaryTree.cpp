#include <iostream>

#include "BinaryTree.h"

using namespace std;

// Initializes root as nullptr, instructing the
// compiler to allocate the memory. 
BinaryTree::BinaryTree() { 
    root = nullptr; 
}

// Copy assignment operator overload.
BinaryTree & BinaryTree::operator=(BinaryTree &rhs) {
    // if the binary tree is empty, do nothing
    if (rhs.root != nullptr) {
        // initialize root
        this -> root = new Node(rhs.root -> value, rhs.root -> key);

        // launch for left and right
        if (rhs.root -> left != nullptr) 
            this -> copyAllRec(rhs.root -> left);
        if (rhs.root -> right != nullptr)
            this -> copyAllRec(rhs.root -> right);
    }

    return *this;
}

// Destructor, which calls deleteAllRec to delete every node in the tree. 
BinaryTree::~BinaryTree() {
    deleteAllRec(root);
}

// helper function for deleteAllRec
void BinaryTree::deleteAllRec(Node* root) {
    // end-of-tree or empty tree. 
    if (root == nullptr)
        return;
 
    // delete left and right subtree first
    deleteAllRec(root -> left);
    deleteAllRec(root -> right);
 
    cout << "deleting " << root -> value.getName() << endl; 

    // Delete the current node
    delete root;
    root = nullptr;
}

// copy constructor
BinaryTree::BinaryTree(const BinaryTree &bt) {
    // if the binary tree is empty, do nothing
    if (bt.root == nullptr)
        return;

    // initialize root
    this -> root = new Node(bt.root -> value, bt.root -> key);

    // launch for left and right
    if (bt.root -> left != nullptr) 
        this -> copyAllRec(bt.root -> left);
    if (bt.root -> right != nullptr)
        this -> copyAllRec(bt.root -> right);
}

// helper method for copying a binary tree into another.
void BinaryTree::copyAllRec(Node* root) {
    // copy the node to the new binary tree. 
    this -> insertRec (root -> key, root -> value, this -> root);
    if (root -> left != nullptr)
        copyAllRec(root -> left);
    if (root -> right != nullptr)
        copyAllRec(root -> right);
}

int BinaryTree::length() {
    return len;
}

void BinaryTree::insert(int key, Person value) {
    if (root == nullptr) {
        root = new Node(value, key);
        len++;
        return;
    }
    insertRec(key, value, root);
}

void BinaryTree::insertRec(int key, Person value, Node* root) {
    // if keys match, we need to replace current node value.
    if (key == root -> key) {
        root -> value = value;
        return;
    }
    // if key is less than this key..
    if (key < root -> key) {
        // ..if left is null, make left a new node..
        if (root -> left == nullptr) {
            root -> left = new Node(value, key);
            len++;
            return;
        }
        // ..else, recur left. 
        else
            insertRec(key, value, root -> left);
    }
    // if key is greater than the key..
    else {
        // .. if right is null, make right a new node..
        if (root -> right == nullptr) {
            root -> right = new Node(value, key);
            len++;
            return;
        }
        // .. else, recur right. 
        else
            insertRec(key, value, root -> right);
    }
}

bool BinaryTree::contains(int key) {
    // try to search the key
    try {
        search(key);
    }
    // if therer is an error, the key does not exist. 
    catch (std::invalid_argument e) {
        return false;
    }
    return true;
}

Person BinaryTree::search(int key) {
    // if root is null, throw an error
    if (root == nullptr)
        throw std::invalid_argument("Attempted to search an empty binary tree");
    // else start the recursion
    return searchRec(key, root);
}

Person BinaryTree::searchRec(int key, Node* root) {
    // if keys match, we have found our root. return value. 
    if (key == root -> key) {
        return root -> value;
    }
    // if key is less than root key..
    if (key < root -> key) {
        // .. if left node is null, we throw an error since we reached the end of the tree without finding anything.
        if (root -> left == nullptr) {
            cout << endl << "error key: " << key << endl;
            throw std::invalid_argument("Key does not exist in binary tree!"); 
        }
        // else, recur right. 
        return searchRec(key, root -> left);
    }
    // else if key is greater than root key..
    else {
        // ..if right node is null, we throw an error since we reached the end of the tree without finding anything.
        if (root -> right == nullptr) {
            cout << endl << "error key: " << key << endl;
            throw std::invalid_argument("Key does not exist in binary tree!");
        }
        // else, recur right. 
        return searchRec(key, root -> right);
    }
}

void BinaryTree::map(function < Person(Person, int) > lambda) {
    // if root is null, then there is nothing to map.  
    if (root == nullptr)
        throw std::invalid_argument("Attempted to search an empty binary tree");
    mapRec(lambda, root);
}

void BinaryTree::mapRec(function < Person(Person, int) > lambda, Node* root) {
    // run the lambda and assign the value accordingly. 
    root -> value = lambda(root -> value, root -> key);
    // recur left if possible. 
    if (root -> left != nullptr)
        mapRec(lambda, root -> left);
    // recur right if possible. 
    if (root -> right != nullptr)
        mapRec(lambda, root -> right);
}

void BinaryTree::display() {
    displayRec(root);
}

void BinaryTree::displayRec(Node* root) {
    if (root == nullptr)
        return;
    cout << "[ " << root -> value.getName() << " , " << root -> key << " ]" << endl;
    displayRec(root -> left);
    displayRec(root -> right);
}