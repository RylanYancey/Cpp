
#include <iostream>

#include "BinaryTree.h"

using namespace std;

void BinaryTree::insert(int key, Person value) {
    if (root == nullptr) {
        root = new Node {
            .left = nullptr,
            .right = nullptr,
            .value = value,
            .key = key,  
        };
    }
    insertRec(key, value, root);
}

void BinaryTree::insertRec(int key, Person value, Node* root) {
    if (key > root -> key) {
        if (root -> left == nullptr)
            root -> left = new Node {
                .left = nullptr,
                .right = nullptr,
                .value = value,
                .key = key,  
            };
        else
            insertRec(key, value, root -> left);
    }
    else {
        if (root -> right == nullptr) 
            root -> right = new Node {
                .left = nullptr,
                .right = nullptr,
                .value = value,
                .key = key,  
            };
        else
            insertRec(key, value, root -> right);
    }
}

Person BinaryTree::search(int key) {
    if (root == nullptr)
        throw std::invalid_argument("Attempted to search an empty binary tree");
    return searchRec(key, root);
}

Person BinaryTree::searchRec(int key, Node* root) {
    if (key == root -> key) {
        return root -> value;
    }
    if (key > root -> key) {
        if (root -> left == nullptr)
            throw std::invalid_argument("Key does not exist in binary tree!"); 
        return searchRec(key, root -> left);
    }
    else {
        if (root -> right == nullptr)
            throw std::invalid_argument("Key does not exist in binary tree!");
        return searchRec(key, root -> right);
    }
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
