#include "BST.h"

BST::BST(string key)
{
    root = new BSTNode(key);
}

BST::BST(string key, string freq)
{
    root = new BSTNode(key, freq);
}

BST::~BST()
{
    delete root;
}
