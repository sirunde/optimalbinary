#include "bst.h"

BST::BST(string key)
{
    root = new BSTNode(key);
}

BST::BST(string key, int freq)
{
    root = new BSTNode(key, freq);
}

BST::~BST()
{
    delete root;
}

void BST::print()
{
    cout << root->key << endl;
}
