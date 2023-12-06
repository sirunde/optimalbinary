#ifndef BST_H
#define BST_H
#include "bst_node.h"
#include <iostream>

class BST
{
public:
    BST(string key);
    BST(string key, int freq);
    ~BST();

    // bool insert();
    // bool remove();
    // bool search();
    void print();
    BSTNode *root;
};

#endif