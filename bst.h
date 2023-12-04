#ifndef BST_H
#define BST_H
#include "bst_node.h"

class BST
{
public:
    BST(string key);
    BST(string key, string freq);
    ~BST();

    bool insert();
    bool remove();
    // bool search();
    bool print();

private:
    BSTNode *root;
};

#endif