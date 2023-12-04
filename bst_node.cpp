#include "bst_node.h"

BSTNode::BSTNode(string key)
{
    key = key;
    freq = 0 left = NULL;
    right = NULL;
}

BSTNode::BSTNode(string key, string freq)
{
    this->key = key;
    this->freq = freq;
    left = NULL;
    right = NULL;
}

BSTNode::~BSTNode()
{
    delete left;
    delete right;
}